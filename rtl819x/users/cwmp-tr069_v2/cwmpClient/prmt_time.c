#include "prmt_time.h"

#ifdef TIME_ZONE

/*ping_zhang:20081217 START:patch from telefonica branch to support WT-107*/
#if 1 //def _PRMT_WT107_
enum eTStatus
{
	eTStatusDisabled,
	eTStatusUnsynchronized,
	eTStatusSynchronized,
	eTStatusErrorFailed,/*Error_FailedToSynchronize*/
	eTStatusError
};
#endif
/*ping_zhang:20081217 END*/

struct CWMP_OP tTimeLeafOP = { getTime,	setTime };
struct CWMP_PRMT tTimeLeafInfo[] =
{
/*(name,			type,		flag,			op)*/
{"Enable",			eCWMP_tBOOLEAN,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP}, /*_PRMT_WT107_*/
{"Status",			eCWMP_tSTRING,	CWMP_READ,	&tTimeLeafOP},
{"NTPServer1",			eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
/*
{"NTPServer2",		eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"NTPServer3",			eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"NTPServer4",		eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"NTPServer5",			eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
*/
{"CurrentLocalTime",		eCWMP_tDATETIME,CWMP_READ|CWMP_DENY_ACT,&tTimeLeafOP},
{"LocalTimeZoneName",		eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
#if 0 //This parameter is OBSOLETED because the information that it represents is fully covered by LocalTimeZoneName.
{"LocalTimeZone",		eCWMP_tSTRING,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"DaylightSavingsUsed", 	eCWMP_tBOOLEAN, CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"DaylightSavingsStart",		eCWMP_tDATETIME,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
{"DaylightSavingsEnd",		eCWMP_tDATETIME,	CWMP_WRITE|CWMP_READ,	&tTimeLeafOP},
#endif
};
enum eTimeLeaf
{
	eEnable, /*_PRMT_WT107_*/
	eTStatus,
	eTNTPServer1,
/*
	eTNTPServer2,
	eTNTPServer3,
	eTNTPServer4,
	eTNTPServer5,
*/
	eTCurrentLocalTime,
	eTLocalTimeZoneName,
#if 0 //This parameter is OBSOLETED because the information that it represents is fully covered by LocalTimeZoneName.	
	eTLocalTimeZone,
	eTDaylightSavingsUsed,
	eTDaylightSavingsStart,
	eTDaylightSavingsEnd,	
#endif	
};
struct CWMP_LEAF tTimeLeaf[] =
{
{ &tTimeLeafInfo[eEnable] }, /*_PRMT_WT107_*/
{ &tTimeLeafInfo[eTStatus] },
{ &tTimeLeafInfo[eTNTPServer1] },
/*
{ &tTimeLeafInfo[eTNTPServer2] },
{ &tTimeLeafInfo[eTNTPServer3] },
{ &tTimeLeafInfo[eTNTPServer4] },
{ &tTimeLeafInfo[eTNTPServer5] },
*/
{ &tTimeLeafInfo[eTCurrentLocalTime] },
{ &tTimeLeafInfo[eTLocalTimeZoneName] },
#if 0 //This parameter is OBSOLETED because the information that it represents is fully covered by LocalTimeZoneName.
{ &tTimeLeafInfo[eTLocalTimeZone] },
{ &tTimeLeafInfo[eTDaylightSavingsUsed] },
{ &tTimeLeafInfo[eTDaylightSavingsStart] },
{ &tTimeLeafInfo[eTDaylightSavingsEnd] },
#endif
{ NULL }
};
/*ping_zhang:20081217 START:patch from telefonica branch to support WT-107*/
//"+0 0",
static const unsigned char *TimeZoneVal[] = {
	"12 1", "11 1", "10 1", "9 1", "8 1", "7 1", "7 2", "6 1", "6 2", "6 3",
	"5 1",  "5 2",  "5 3",  "4 1", "4 2", "4 3", "3 1", "3 2", "3 3", "2 1",
	"1 1",  "0 1",  "0 2",  "-1 1", "-1 2", "-1 3", "-1 4", "-1 5", "-1 6", "-2 1",
	"-2 2",  "-2 3",  "-2 4",  "-2 5", "-2 6", "-3 1", "-3 2", "-3 3", "-3 4", "-4 1",
	"-4 2",  "-4 3",  "-5 1",  "-5 2", "-5 3", "-6 1", "-6 2", "-7 1", "-8 1", "-8 2",
	"-8 3",  "-8 4",  "-9 1",  "-9 2", "-9 3", "-9 4", "-9 5", "-10 1","-10 2","-10 3",
	"-10 4", "-10 5", "-11 1", "-12 1","-12 2"};
static const unsigned char *TimeZoneName[] = {
	"ENK-12",		/*(GMT-12:00)Eniwetok, Kwajalein*/
	"MIS-11",		/*(GMT-11:00)Midway Island, Samoa*/
	"HAW-10",		/*(GMT-10:00)Hawaii*/
	"ALA-9,M4.1.0/2,M10.5.0/2",		/*(GMT-09:00)Alaska*/
	"PTT-8,M4.1.0/2,M10.5.0/2",		/*(GMT-08:00)Pacific Time (US & Canada), Tijuana*/
	"ARI-7",		/*(GMT-07:00)Arizona*/
	"MOT-7,M4.1.0/2,M10.5.0/2",		/*(GMT-07:00)Mountain Time (US & Canada)*/
	"CET-6,M4.1.0/2,M10.5.0/2",		/*(GMT-06:00)Central Time (US & Canada)*/
	"MCT-6,M4.1.0/2,M10.5.0/2",		/*(GMT-06:00)Mexico City, Tegucigalpa*/
	"SAS-6",		/*(GMT-06:00)Saskatchewan*/
	"BLQ-5",		/*(GMT-05:00)Bogota, Lima, Quito*/
	"EAT-5,M4.1.0/2,M10.5.0/2",		/*(GMT-05:00)Eastern Time (US & Canada)*/
	"IND-5,M4.1.0/2,M10.5.0/2",		/*(GMT-05:00)Indiana (East)*/
	"ATT-4",		/*(GMT-04:00)Atlantic Time (Canada)*/
	"CLP-4",		/*(GMT-04:00)Caracas, La Paz*/
	"SAN-4,M10.2.0/0,M3.2.0/0",		/*(GMT-04:00)Santiago*/
	"NFL-3,M4.1.0/0,M10.5.0/0",		/*(GMT-03:30)Newfoundland*/
	"BRA-3,M2.2.0/0,M10.2.0/0",		/*(GMT-03:00)Brasilia*/
	"BAG-3",		/*(GMT-03:00)Buenos Aires, Georgetown*/
	"MIA-2",		/*(GMT-02:00)Mid-Atlantic*/
	"ACV-1,M3.5.0/0,M10.5.0/1",		/*(GMT-01:00)Azores, Cape Verde Is.*/
	"CAM0",		/*(GMT)Casablanca, Monrovia*/
	"GMT0,M3.5.0/1,M10.5.0/2",		/*(GMT)Greenwich Mean Time: Dublin, Edinburgh, Lisbon, London*/
	"ABB1",		/*(GMT+01:00)Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna*/
	"BBB1",		/*(GMT+01:00)Belgrade, Bratislava, Budapest, Ljubljana, Prague*/
	"BAM1",		/*(GMT+01:00)Barcelona, Madrid*/
	"BCM1",		/*(GMT+01:00)Brussels, Copenhagen, Madrid, Paris, Vilnius*/
	"PAR1",		/*(GMT+01:00)Paris*/
	"SSS1",		/*(GMT+01:00)Sarajevo, Skopje, Sofija, Warsaw, Zagreb*/
	"AIM2",		/*(GMT+02:00)Athens, Istanbul, Minsk*/
	"BUC2,M3.5.0/3,M10.5.0/4",		/*(GMT+02:00)Bucharest*/
	"CAI2,M4.5.5/0,M9.5.5/0",		/*(GMT+02:00)Cairo*/
	"HAP2",		/*(GMT+02:00)Harare, Pretoria*/
	"HRT2,M3.5.0/3,M10.5.5/4",		/*(GMT+02:00)Helsinki, Riga, Tallinn*/
	"JER2,M3.5.5/2,M10.1.0/2",		/*(GMT+02:00)Jerusalem*/
	"BKR3",		/*(GMT+03:00)Baghdad, Kuwait, Riyadh*/
	"MPV3,M3.5.0/2,M10.5.0/3",		/*(GMT+03:00)Moscow, St. Petersburg, Volgograd*/
	"MAI3",		/*(GMT+03:00)Mairobi*/
	"TEH3",		/*(GMT+03:30)Tehran*/
	"ADM3",		/*(GMT+04:00)Abu Dhabi, Muscat*/
	"BAT4",		/*(GMT+04:00)Baku, Tbilisi*/
	"KAB4,M3.5.0/4,M10.5.0/5",		/*(GMT+04:30)Kabul*/
	"EKA5",		/*(GMT+05:00)Ekaterinburg*/
	"IKT5",		/*(GMT+05:00)Islamabad, Karachi, Tashkent*/
	"BCM5",		/*(GMT+05:30)Bombay, Calcutta, Madras, New Delhi*/
	"AAD6",		/*(GMT+06:00)Astana, Almaty, Dhaka*/
	"COL6",		/*(GMT+06:00)Colombo*/
	"BHJ7",		/*(GMT+07:00)Bangkok, Hanoi, Jakarta*/
	"BCH8",		/*(GMT+08:00)Beijing, Chongqing, Hong Kong, Urumqi*/
	"PER8",		/*(GMT+08:00)Perth*/
	"SIN8",		/*(GMT+08:00)Singapore*/
	"TAI8",		/*(GMT+08:00)Taipei*/
	"OST9",		/*(GMT+09:00)Osaka, Sapporo, Tokyo*/
	"SEO9",		/*(GMT+09:00)Seoul*/
	"YAK9",		/*(GMT+09:00)Yakutsk*/
	"ADE9,M10.5.0/2,M4.1.0/3",		/*(GMT+09:30)Adelaide*/
	"DAR9",		/*(GMT+09:30)Darwin*/
	"BRI10",		/*(GMT+10:00)Brisbane*/
	"CMS10,M10.5.0/2,M4.1.0/3",		/*(GMT+10:00)Canberra, Melbourne, Sydney*/
	"GPM10",		/*(GMT+10:00)Guam, Port Moresby*/
	"HOB10,M10.1.0/2,M4.1.0/3",		/*(GMT+10:00)Hobart*/
	"VLA10,M3.5.0/2,M10.5.0/3",		/*(GMT+10:00)Vladivostok*/
	"MSN11",		/*(GMT+11:00)Magadan, Solomon Is., New Caledonia*/
	"AUW12,M3.2.0/3,M10.1.0/2",		/*(GMT+12:00)Auckland, Wllington*/
	"FKM12",		/*(GMT+12:00)Fiji, Kamchatka, Marshall Is.*/
	};
/*ping_zhang:20081217 END*/
int getTime(char *name, struct CWMP_LEAF *entity, int *type, void **data)
{
	char	*lastname = entity->info->name;
	unsigned int vChar=0;
	//unsigned char vChar=0;
	struct in_addr ipAddr;
	char buff[256]={0};
	
	if( (name==NULL) || (type==NULL) || (data==NULL) || (entity==NULL)) 
		return -1;

	*type = entity->info->type;
	*data = NULL;
	if(strcmp( lastname, "Enable" )==0 )
	{
		mib_get( MIB_NTP_ENABLED, (void *)&vChar);
		*data = uintdup( vChar!=0 );
	}else if( strcmp( lastname, "Status" )==0 )
	{
		unsigned int timeStatus;
		mib_get( MIB_NTP_ENABLED, (void *)&vChar);
		if(vChar==0)
		 	*data=strdup( "Disabled" );
		else
		{
			FILE *fp;
			fp=fopen("/tmp/timeStatus","r");
			if(fp){
				fscanf(fp,"%d",&timeStatus);
				fclose(fp);
				//unlink("/tmp/timeStatus");
			}
			switch(timeStatus)
			{
			case eTStatusDisabled:
				*data=strdup( "Disabled" );
				break;
			case eTStatusUnsynchronized:
				*data=strdup( "Unsychronized" );
				break;
			case eTStatusSynchronized:
				*data=strdup( "Synchronized" );
				break;
			case eTStatusErrorFailed:
				*data=strdup( "Error_FailedToSynchronize" );
				break;
			case eTStatusError:
			default:
				*data=strdup( "Unsychronized" );
				break;
			}
		}
	}else if( strcmp( lastname, "NTPServer1" )==0 )
	{
		char enabled;
		mib_get(MIB_NTP_ENABLED, (void *)&enabled);
		if(!enabled){//disabled, return NULL
			*data = strdup("");
		}else{//enabled
			int ntpServerIdx;
			mib_get(MIB_NTP_SERVER_ID,(void *)&ntpServerIdx);
			
			if(ntpServerIdx == 0 || ntpServerIdx == 1){
				if(ntpServerIdx == 0 )
					mib_get(MIB_NTP_SERVER_IP1, (void *)&ipAddr);
				else
					mib_get(MIB_NTP_SERVER_IP2, (void *)&ipAddr);

				strcpy( buff, inet_ntoa(ipAddr) );
                *data=strdup( buff );
			}
			else
				*data = strdup("");
		}
	}else if( strcmp( lastname, "NTPServer2" )==0 ){
		*data = strdup("");
	}else if( strcmp( lastname, "NTPServer3" )==0 ){
		*data = strdup("");
	}else if( strcmp( lastname, "NTPServer4" )==0 ){
		*data = strdup("");
	}else if( strcmp( lastname, "NTPServer5" )==0 ){
		*data = strdup("");
	}else if( strcmp( lastname, "CurrentLocalTime" )==0 ){
		*data = timedup( time(NULL) );
	}
	else if( strcmp( lastname, "LocalTimeZoneName" )==0 )
	{	
		/*exaple:EST+5EDT,M4.1.0/2,M10.5.0/2
		    current system does't support Daylight Savings Time,so TZName like EST+5*/
		unsigned int i,found=0;
		mib_get(MIB_NTP_TIMEZONE, (void *)buff);
		for(i=0;i<65;i++)
		{
			if(strcmp((char*)buff,TimeZoneVal[i])==0)
			{
				found = 1;
				*data = strdup(TimeZoneName[i]);
				break;
			}
		}
		if(found !=1)
			*data = strdup( "" );
	}
	
#if 0 //This parameter is OBSOLETED because the information that it represents is fully covered by LocalTimeZoneName.
	else if( strcmp( lastname, "LocalTimeZone" )==0 )
	{
		char *pStr;
		int  timeoffset=0;
		mib_get(MIB_NTP_TIMEZONE, (void *)buff);
		pStr = strstr(buff, " ");
		if (pStr != NULL) pStr[0] = '\0';
		timeoffset = atoi( buff );
		timeoffset = 0 - timeoffset;
		if(timeoffset>=0)
			sprintf( buff, "+%02d:00", timeoffset );
		else
			sprintf( buff, "-%02d:00", -timeoffset );
		
		*data = strdup( buff );
	}
	else if( strcmp( lastname, "DaylightSavingsUsed" )==0 )
	{
		mib_get( MIB_DAYLIGHT_SAVE, (void *)&vChar);
		if(vChar == 0)
			*data = uintdup( 0 );
		else
			*data = uintdup( 1 );
	}
	else if( strcmp( lastname, "DaylightSavingsStart" )==0 )
	{

	}
	else if( strcmp( lastname, "DaylightSavingsEnd" )==0 )
	{

	}
#endif 	
	else
	{
		return ERR_9005;
	}
	
	return 0;
}

int setTime(char *name, struct CWMP_LEAF *entity, int type, void *data)
{
	char	*lastname = entity->info->name;
	char	*buf=data;
	//unsigned char vChar=0;
	unsigned int vChar=0;
	int isNtpUpdated = 0;
#ifdef MULTI_WAN_SUPPORT
	extern int ntp_reinit_mode;
#endif
	if( (name==NULL) || (data==NULL) || (entity==NULL)) return -1;
#ifdef _PRMT_X_CT_COM_DATATYPE
	int tmpint=0;
	unsigned int tmpuint=0;
	int tmpbool=0;
	if(changestring2int(data,entity->info->type,type,&tmpint,&tmpuint,&tmpbool)<0)
		return ERR_9006;
#else
	if( entity->info->type!=type ) return ERR_9006;
#endif

	//printf("lastname=%s\n", lastname);
	if( strcmp( lastname, "Enable" )==0 )
	{
#ifdef _PRMT_X_CT_COM_DATATYPE
		int *i = &tmpbool;		
#else
		int *i = data;
#endif
		if( i==NULL ) return ERR_9007;
		vChar = (*i==0)?0:1;
		mib_set(MIB_NTP_ENABLED, (void *)&vChar);

		return 1;
	}else if( strcmp( lastname, "NTPServer1" )==0 )
	{
		struct in_addr in;
		if(buf==NULL) return ERR_9007;
		if(strlen(buf)==0) return ERR_9007;
		if(inet_aton( buf, &in )==0) return ERR_9007;

		vChar = 1;
		mib_set(MIB_NTP_ENABLED, (void *)&vChar);
		mib_set(MIB_NTP_SERVER_ID, (void *)&vChar);
		mib_set(MIB_NTP_SERVER_IP2, (void *)&in);

		return 1;

	}else if( strcmp( lastname, "NTPServer2" )==0 ){
		return ERR_9001;
	}else if( strcmp( lastname, "NTPServer3" )==0 ){
		return ERR_9001;
	}else if( strcmp( lastname, "NTPServer4" )==0 ){
		return ERR_9001;
	}else if( strcmp( lastname, "NTPServer5" )==0 ){
		return ERR_9001;
	}else if( strcmp( lastname, "LocalTimeZoneName" )==0 )
	{
		int i,setSuccess=0;
		char tmp[16];

		if(buf==NULL) return ERR_9007;
		if( strlen(buf)==0 || strlen(buf) > 64) return ERR_9007;
		for(i=0;i<65;i++)
		{
			//printf("NTP: buf=%s\n", buf);
			if(strcmp(buf,TimeZoneName[i])==0)
			{
				//printf("NTP: current TimeZoneName=%d\n", i);
				mib_set(MIB_NTP_TIMEZONE, (void *)TimeZoneVal[i]);
				setSuccess = 1;
				break;
			}
		}
		if(setSuccess==0) return ERR_9007;
		

		return 1;



	}
#if 0
	else if( strcmp( lastname, "LocalTimeZone" )==0 )
	{
		int hh=0,mm=0;
		char tmp[16];

		if(buf==NULL) return ERR_9007;
		if( (strlen(buf)==0) || (strlen(buf)>6) ) return ERR_9007;
		//format: +/-hh:mm (length==6)
		if( sscanf( buf, "%d:%d", &hh, &mm )==2 )
		{
			if( hh<-12 || hh>12 || mm<0 || mm>60 ) return ERR_9007;
			if(hh<=0) //-11 ==> 11
				sprintf( tmp, "+%d 1", -hh );
			else      // 11 ==> -11
				sprintf( tmp, "%d 1", -hh );
				
			mib_set(MIB_NTP_TIMEZONE, (void *)tmp);			
		}else
			return ERR_9007;

		return 1;
	}
	else if( strcmp( lastname, "DaylightSavingsUsed" )==0 )
	{
		int *i = data;
		vChar = (*i==0)?0:1;
		mib_set( MIB_DAYLIGHT_SAVE, (void *)&vChar);
	}
#endif

	else{
		return ERR_9005;
	}
	
	return 0;
}

#endif /*TIME_ZONE*/
