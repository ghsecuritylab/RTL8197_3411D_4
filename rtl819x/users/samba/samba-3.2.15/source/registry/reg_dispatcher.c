/*
 *  Unix SMB/CIFS implementation.
 *  Virtual Windows Registry Layer
 *  Copyright (C) Gerald Carter                     2002-2005
 *  Copyright (C) Michael Adam                      2006-2008
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Implementation of registry frontend view functions.
 * Functions moved from reg_frontend.c to minimize linker deps.
 */

#include "includes.h"

#undef DBGC_CLASS
#define DBGC_CLASS DBGC_REGISTRY

static const struct generic_mapping reg_generic_map =
	{ REG_KEY_READ, REG_KEY_WRITE, REG_KEY_EXECUTE, REG_KEY_ALL };

/********************************************************************
********************************************************************/

static WERROR construct_registry_sd(TALLOC_CTX *ctx, SEC_DESC **psd)
{
	SEC_ACE ace[3];
	SEC_ACCESS mask;
	size_t i = 0;
	SEC_DESC *sd;
	SEC_ACL *acl;
	size_t sd_size;

	/* basic access for Everyone */

	init_sec_access(&mask, REG_KEY_READ);
	init_sec_ace(&ace[i++], &global_sid_World, SEC_ACE_TYPE_ACCESS_ALLOWED,
		     mask, 0);

	/* Full Access 'BUILTIN\Administrators' */

	init_sec_access(&mask, REG_KEY_ALL);
	init_sec_ace(&ace[i++], &global_sid_Builtin_Administrators,
		     SEC_ACE_TYPE_ACCESS_ALLOWED, mask, 0);

	/* Full Access 'NT Authority\System' */

	init_sec_access(&mask, REG_KEY_ALL );
	init_sec_ace(&ace[i++], &global_sid_System, SEC_ACE_TYPE_ACCESS_ALLOWED,
		     mask, 0);

	/* create the security descriptor */

	acl = make_sec_acl(ctx, NT4_ACL_REVISION, i, ace);
	if (acl == NULL) {
		return WERR_NOMEM;
	}

	sd = make_sec_desc(ctx, SEC_DESC_REVISION, SEC_DESC_SELF_RELATIVE,
			   &global_sid_Builtin_Administrators,
			   &global_sid_System, NULL, acl,
			   &sd_size);
	if (sd == NULL) {
		return WERR_NOMEM;
	}

	*psd = sd;
	return WERR_OK;
}

/***********************************************************************
 High level wrapper function for storing registry subkeys
 ***********************************************************************/

bool store_reg_keys( REGISTRY_KEY *key, REGSUBKEY_CTR *subkeys )
{
	if (key->ops && key->ops->store_subkeys)
		return key->ops->store_subkeys(key->name, subkeys);

	return false;
}

/***********************************************************************
 High level wrapper function for storing registry values
 ***********************************************************************/

bool store_reg_values( REGISTRY_KEY *key, REGVAL_CTR *val )
{
	if (key->ops && key->ops->store_values)
		return key->ops->store_values(key->name, val);

	return false;
}

/***********************************************************************
 High level wrapper function for enumerating registry subkeys
 Initialize the TALLOC_CTX if necessary
 ***********************************************************************/

int fetch_reg_keys( REGISTRY_KEY *key, REGSUBKEY_CTR *subkey_ctr )
{
	int result = -1;

	if (key->ops && key->ops->fetch_subkeys)
		result = key->ops->fetch_subkeys(key->name, subkey_ctr);

	return result;
}

/***********************************************************************
 High level wrapper function for enumerating registry values
 ***********************************************************************/

int fetch_reg_values( REGISTRY_KEY *key, REGVAL_CTR *val )
{
	int result = -1;

	DEBUG(10, ("fetch_reg_values called for key '%s' (ops %p)\n", key->name,
		   (key->ops) ? (void *)key->ops : NULL));

	if (key->ops && key->ops->fetch_values)
		result = key->ops->fetch_values(key->name, val);

	return result;
}

/***********************************************************************
 High level access check for passing the required access mask to the
 underlying registry backend
 ***********************************************************************/

bool regkey_access_check( REGISTRY_KEY *key, uint32 requested, uint32 *granted,
			  const struct nt_user_token *token )
{
	SEC_DESC *sec_desc;
	NTSTATUS status;
	WERROR err;
	TALLOC_CTX *mem_ctx;

	/* use the default security check if the backend has not defined its
	 * own */

	if (key->ops && key->ops->reg_access_check) {
		return key->ops->reg_access_check(key->name, requested,
						  granted, token);
	}

	/*
	 * The secdesc routines can't yet cope with a NULL talloc ctx sanely.
	 */

	if (!(mem_ctx = talloc_init("regkey_access_check"))) {
		return false;
	}

	err = regkey_get_secdesc(mem_ctx, key, &sec_desc);

	if (!W_ERROR_IS_OK(err)) {
		TALLOC_FREE(mem_ctx);
		return false;
	}

	se_map_generic( &requested, &reg_generic_map );

	if (!se_access_check(sec_desc, token, requested, granted, &status)) {
		TALLOC_FREE(mem_ctx);
		return false;
	}

	TALLOC_FREE(mem_ctx);
	return NT_STATUS_IS_OK(status);
}

WERROR regkey_get_secdesc(TALLOC_CTX *mem_ctx, REGISTRY_KEY *key,
			  struct security_descriptor **psecdesc)
{
	struct security_descriptor *secdesc;
	WERROR werr;

	if (key->ops && key->ops->get_secdesc) {
		werr = key->ops->get_secdesc(mem_ctx, key->name, psecdesc);
		if (W_ERROR_IS_OK(werr)) {
			return WERR_OK;
		}
	}

	werr = construct_registry_sd(mem_ctx, &secdesc);
	if (!W_ERROR_IS_OK(werr)) {
		return werr;
	}

	*psecdesc = secdesc;
	return WERR_OK;
}

WERROR regkey_set_secdesc(REGISTRY_KEY *key,
			  struct security_descriptor *psecdesc)
{
	if (key->ops && key->ops->set_secdesc) {
		return key->ops->set_secdesc(key->name, psecdesc);
	}

	return WERR_ACCESS_DENIED;
}

/**
 * Check whether the in-memory version of the subkyes of a
 * registry key needs update from disk.
 */
bool reg_subkeys_need_update(REGISTRY_KEY *key, REGSUBKEY_CTR *subkeys)
{
	if (key->ops && key->ops->subkeys_need_update)
	{
		return key->ops->subkeys_need_update(subkeys);
	}

	return false;
}

/**
 * Check whether the in-memory version of the values of a
 * registry key needs update from disk.
 */
bool reg_values_need_update(REGISTRY_KEY *key, REGVAL_CTR *values)
{
	if (key->ops && key->ops->values_need_update)
	{
		return key->ops->values_need_update(values);
	}

	return false;
}

