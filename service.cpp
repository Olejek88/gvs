#include <windows.h>
#include "service.h"

#define MAIN_FILE	"\\Micro_SD\\Temp\\FTP\\data.log"
#define XML_FILE	"\\Micro_SD\\Temp\\FTP\\data.xml"
#define FINISH_FILE	"\\Micro_SD\\Temp\\FTP\\stop"

FILE	*Log;
FILE    *Dat;
extern	char	mainlog[100];				// main log file
extern	byte	FinishWork;
extern	VOID ULOGW (CHAR* string, ...);		// log file function
extern	byte	FinishWork4;

bool WriteDataFile (byte format);
bool WriteDataFile2 (byte format);
uint ParseFile (char* buf, char* param);
bool LoadFinishFile ();

//----------------------------------------------------------------------------------------------------
// [Thread] service thread
VOID ServiceThread (LPVOID lpParam)
{
 while (WorkEnable)
	{
	 Sleep (120000);
	 WriteDataFile (0);
	 LoadFinishFile ();
	 Sleep (180000);
	 WriteDataFile2 (0);
	} 
}
//----------------------------------------------------------------------------------------------------
// get data from SQL and save to CSV(0)/XML(1) file
bool WriteDataFile (byte format)
{
 TCHAR InBuffer[300];
 CHAR   buf[300],date[50];
 Dat =  fopen(XML_FILE,"w");

 GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_SHORTDATE, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), date, sizeof(date), NULL,NULL);
 GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf, sizeof(buf), NULL,NULL);
 sprintf (date,"%s %s",date,buf);

 sprintf (buf,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"); fprintf (Dat, buf);
 sprintf (buf,"<stats>\n"); fprintf (Dat, buf);
 sprintf (buf,"</stats>\n"); fprintf (Dat, buf); 

 sprintf (buf,"<inputs>\n"); fprintf (Dat, buf);
 sprintf (buf,"</inputs>\n"); fprintf (Dat, buf);

 sprintf (buf,"<values>\n"); fprintf (Dat, buf);
 sprintf (buf,"<value =\"V1_dushCGTS\" value=\"%f\" time=\"%s\">\n",V1_dushCGTS,date); fprintf (Dat, buf);
 sprintf (buf,"<value =\"V2_dushPFI\" value=\"%f\" time=\"%s\">\n",V2_dushPFI,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"V3_stol\" value=\"%f\" time=\"%s\">\n",V3_stol,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"V4_prach\" value=\"%f\" time=\"%s\">\n",V4_prach,date); fprintf (Dat, buf); 

 sprintf (buf,"<value =\"P_par_tech\" value=\"%f\" time=\"%s\">\n",P_par_tech,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"P_par_in_heater\" value=\"%f\" time=\"%s\">\n",P_par_in_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"P_water_in_heater\" value=\"%f\" time=\"%s\">\n",P_water_in_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"P_water_out_heater\" value=\"%f\" time=\"%s\">\n",P_water_out_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"P_water_gvs_accum\" value=\"%f\" time=\"%s\">\n",P_water_gvs_accum,date); fprintf (Dat, buf); 
 //sprintf (buf,"<value =\"S_water_reg_temp\" value=\"%f\" time=\"%s\">\n",S_water_reg_temp,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"L_water_bak_accum\" value=\"%f\" time=\"%s\">\n",L_water_bak_accum,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"V_water_bak_accum\" value=\"%f\" time=\"%s\">\n",V_water_bak_accum,date); fprintf (Dat, buf); 
 //sprintf (buf,"<value =\"L_cond_bak_nakop\" value=\"%f\" time=\"%s\">\n",L_cond_bak_nakop,date); fprintf (Dat, buf); 

 sprintf (buf,"<value =\"T_par_in_heater\" value=\"%f\" time=\"%s\">\n",T_par_in_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_in_heater\" value=\"%f\" time=\"%s\">\n",T_water_in_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_out_heater\" value=\"%f\" time=\"%s\">\n",T_water_out_heater,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_out_gvs\" value=\"%f\" time=\"%s\">\n",T_water_out_gvs,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_podp_hvs\" value=\"%f\" time=\"%s\">\n",T_water_podp_hvs,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_bak_accum\" value=\"%f\" time=\"%s\">\n",T_water_bak_accum,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_prach\" value=\"%f\" time=\"%s\">\n",T_water_prach,date); fprintf (Dat, buf); 
 sprintf (buf,"<value =\"T_water_stolv\" value=\"%f\" time=\"%s\">\n",T_water_stolv,date); fprintf (Dat, buf);  
 sprintf (buf,"</values>\n"); fprintf (Dat, buf); 

 fclose (Dat);

 return TRUE;
}
//----------------------------------------------------------------------------------------------------
// get data from SQL and save to CSV(0)/XML(1) file
bool WriteDataFile2 (byte format)
{
 TCHAR InBuffer[300];
 CHAR   buf[300],date[50];
 Dat =  fopen(MAIN_FILE,"a");
 GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_SHORTDATE, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), date, sizeof(date), NULL,NULL);
 GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf, sizeof(buf), NULL,NULL);
 sprintf (date,"%s %s",date,buf);
 sprintf (buf,"%s\tP=%.4f,L=%.4f,V=%.4f|Tp=%.2f,(Ti=%.3f,To=%.3f),[Ta=%.4f],(Tpr=%.2f,Tst=%.2f),V(%.2f,%.2f,%.2f,%.2f)\n",date,P_par_tech,L_water_bak_accum,V_water_bak_accum,T_par_in_heater,T_water_in_heater,T_water_out_heater,T_water_bak_accum,T_water_prach,T_water_stolv,V1_dushCGTS,V2_dushPFI,V3_stol,V4_prach); 
 fprintf (Dat, buf);
 fclose (Dat);
 return TRUE;
}
//----------------------------------------------------------------------------------------------------
bool LoadFinishFile ()
{
 Dat =  fopen(FINISH_FILE,"r");
 if (!Dat) return 0;
 //ULOGW ("FINISHWORK");
 FinishWork=1;	// 45
 FinishWork4=1;
 fclose (Dat);
 return true;
}
//----------------------------------------------------------------------------------------------------
// get data from SQL and save to CSV(0)/XML(1) file
bool LoadDataFile (byte format)
{
 CHAR   buf[340];
 Dat =  fopen(XML_FILE,"r");
 if (!Dat) return 0;
 int j=0;
 while(!feof(Dat))
	{
	 fgets(buf,300,Dat);

	 //if (strstr (buf,"totalDetected")) totalDetected=ParseFile (buf,"totalDetected");
	 //if (strstr (buf,"totalLoaded")) totalLoaded=ParseFile (buf,"totalLoaded");
	 //if (strstr (buf,"todayDetected")) todayDetected=ParseFile (buf,"todayDetected");
	 //if (strstr (buf,"todayLoaded")) todayLoaded=ParseFile (buf,"todayLoaded");
	}
 //ULOGW ("[ser] read stats %d|%d|%d|%d",totalDetected,totalLoaded,todayDetected,todayLoaded);
 fclose (Dat);
 return true;
}
//----------------------------------------------------------------------------------------------------
uint ParseFile (char* buf, char* param)
{
 CHAR   date[50];
 CHAR	*cur, *cur2;
 int	res=0;
 cur=strstr(buf,param); 
 if (cur!=NULL) 
	{
	 cur2=strstr (cur,"time");
	 if (cur2 && cur2-cur>20)
		{
		 //ULOGW ("[ser] cur=%d cur2=%d",cur,cur2);
		 strncpy (date,cur+strlen (param)+9,cur2-cur-11-strlen (param));
		 //ULOGW ("[ser] %s (%d)",date,cur2-cur-11-strlen (param));
		 res=atoi (date);
		 return res;
		}
	}
 return 0;
}
//----------------------------------------------------------------------------------------------------
// log/output function
VOID ULOGW (CHAR* string, ...)
{
 TCHAR InBuffer[300]; //SYSTEMTIME st;
 CHAR buf[300]; CHAR buf2[30]; CHAR buf3[30]; CHAR buf4[200];
// Log = fopen(MAIN_LOG,"a");
 byte cn=30;
 while (cn)
	{
	 if (Log==NULL) { Log = fopen(mainlog,"a"); break; }
	 else { Sleep(5); cn--; }
	 if (cn<10) return;
	}

 //GetSystemTime(&st); 
 GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_SHORTDATE, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf2, sizeof(buf2), NULL,NULL);
 GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf3, sizeof(buf3), NULL,NULL);

 va_list arg;
 va_start(arg, string);
 _vsnprintf(buf4,sizeof (buf4), string, arg);
 va_end(arg);

 _snprintf (buf,sizeof(buf)-1,"%s %s\t%s\n",buf2,buf3,buf4); 
 //_snprintf (buf,sizeof(buf)-1,"%s %s\t%s\n",buf2,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,buf4); 
 fprintf (Log, buf);
 printf ("%s",buf);
 fclose(Log); Log=NULL;
}
