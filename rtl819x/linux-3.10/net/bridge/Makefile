#
# Makefile for the IEEE 802.1d ethernet bridging layer.
#

ifeq ($(CONFIG_RTL_A4_STA_SUPPORT),y)
        EXTRA_CFLAGS += -DA4_STA
endif		


ifeq ($(CONFIG_RTL_MESH_SUPPORT),y)
        EXTRA_CFLAGS += -DCONFIG_RTK_MESH
endif

ifeq ($(CONFIG_RTL_MULTI_REPEATER_MODE_SUPPORT),y)
        EXTRA_CFLAGS += -DCONFIG_RTK_GUEST_ZONE
endif		
obj-$(CONFIG_BRIDGE) += bridge.o

bridge-y	:= br.o br_device.o br_fdb.o br_forward.o br_if.o br_input.o \
			br_ioctl.o br_notify.o br_stp.o br_stp_bpdu.o \
			br_stp_if.o br_stp_timer.o br_netlink.o

bridge-$(CONFIG_SYSFS) += br_sysfs_if.o br_sysfs_br.o

bridge-$(CONFIG_BRIDGE_NETFILTER) += br_netfilter.o

bridge-$(CONFIG_BRIDGE_IGMP_SNOOPING) += br_multicast.o br_mdb.o

bridge-$(CONFIG_BRIDGE_VLAN_FILTERING) += br_vlan.o

obj-$(CONFIG_BRIDGE_NF_EBTABLES) += netfilter/

bridge-$(CONFIG_RTL_DNS_TRAP) += rtl_dnstrap.o

bridge-$(CONFIG_RTL_HTTP_REDIRECT) += rtl_http_redirect.o
