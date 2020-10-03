#define MAIN_LOG	"\\Micro_SD\\Temp\\FTP\\logs\\"

#include <windows.h>
#include <urlmon.h>
//#include <oledb.h>
//#include "sqlce_oledb.h"

#include "Modbus_ARM.h"
#include "winpacsdk.h"
#include "kernel.h"

bool Init (VOID);					// initialize function
bool deInit (VOID);					// deinitialize function
VOID dispatcher (VOID);				// dispatcher 
VOID ULOGW (CHAR* string, ...);		// log file function
VOID GetInfo (VOID);				// get system information
VOID SetConfiguration (VOID);		// set system configuration
VOID CheckIO (VOID);				// check input/output modules/channels

VOID GetAllIOStatus (LPVOID lpParam);	// [Thread] Get all input/output status/values 
VOID MainAlgorithm (LPVOID lpParam);	// [Thread] Main algorithm thread 
extern VOID PanelConnection (LPVOID lpParam);	// [Thread] Get/Set all input/output values from/to panel
extern VOID SI8Connection (LPVOID lpParam);	// [Thread] Get/Set all input/output values from/to servoprivod
extern VOID ServiceThread (LPVOID lpParam);		// [Thread] Service thread

extern	bool WriteDataFile (byte format);		// write data in file
extern	bool WriteDataFile2 (byte format);		// write data in file
extern	bool LoadDataFile (byte format);		// load data from file

VOID OutModbusError (int iInitSuccess);	// out in console and log modbus error
VOID OutError (int iInitSuccess);		// out in console and log winpac errors

bool	Regulator (void);
bool	FillBak (void);
bool	StopPar (void);
bool	StopFill (void);
bool	StartM2 (void);
bool	StopM2 (void);
bool	StopAll (void);
bool	CheckPPotr (void);

byte	Fillbak=0;
byte	Stopfill=0;
byte	NoHVS=0;
byte	StatusM2=0;
byte	Statusfill=0;

extern	HANDLE	hPort3;					// SRV port handler

extern FILE *Log;
//----------------------------------------------------------------------------------------------------
INT _tmain(INT argc, CHAR *argv[])
{  
 TCHAR InBuffer[300]; CHAR buf3[30]; CHAR buf2[30];
 GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, TEXT("hhmmss"), InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf3, sizeof(buf3), NULL,NULL);
 GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, NULL, TEXT("MMdd"), InBuffer, sizeof(InBuffer));
 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf2, sizeof(buf2), NULL,NULL);

 sprintf (mainlog,"%slog_%s_%s.log",MAIN_LOG,buf2,buf3);
 //sprintf (mainlog,"%slog_%d.log",MAIN_LOG,rand());
 Log = fopen(mainlog,"w");
 if (!Log) { printf ("critical! error open port, maybe MicroSD card not inserted"); Sleep (3000); return -1; }
 if (fclose (Log))	printf ("not closed");			// close log file
 Log=NULL;
 TestRegim=0;			// not test
 ULOGW ("uaiz gvs kernel v0.86.5 started (26.10.2014)");
 LoadDataFile (0);
 GetInfo ();			// get system info
 if (Init ()) ULOGW ("initialize success");
 else { ULOGW ("initialize error! please check out all hardware and software"); Sleep (30000); return -1; }
  //SetConfiguration ();	// set project/system configuration
  //CheckIO ();				// test input/output modules
 dispatcher ();		// start dispatcher
 deInit ();			// deinitialize all
 ULOGW ("uaiz gvs kernel finished");
 return 0; 
}
//----------------------------------------------------------------------------------------------------
// initialise 
bool Init (VOID)
{
 hPort = uart_Open("COM0:,115200,N,8,1");
 if (hPort) ULOGW ("open COM0 internal port on speed 115200 [8-N-1] success (hPort=%x)",hPort);
 else 
	{
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("error open COM0 internal port on speed 115200 [8-N-1] error [0x%x]: %s",pac_GetLastError(), errorBuf);
	 return FALSE;
	}
 return TRUE;
}
//----------------------------------------------------------------------------------------------------
// deinitialise function 
bool deInit (VOID)
{
 if (hPort) { uart_Close(hPort); ULOGW ("close COM0 internal port"); }
 WorkEnable=0;			// disable all work 
 if (hPort3) { uart_Close(hPort3); ULOGW ("close modbusRTU COM1 [panel] port"); }
 MBRTUClose(3);
 //pac_EnableSlotInterrupt(2, false); // disable slot2 [87053W] interrupt
 //pac_UnregisterSlotInterrupt(2);
 //MBRTUClose (1);		// close panel interface
 return TRUE;
}
//----------------------------------------------------------------------------------------------------
VOID dispatcher (VOID)
{
 BYTE stopbytime=0;
 WorkEnable=1;			// work enable
 UINT	count=30050;
 MEMORYSTATUS lpBuffer;
 DWORD	AvailPhys=0;
 TCHAR  InBuffer[300]; CHAR   buf[100];
 pac_EnableWatchDog(0, 30);

 hThrdMT = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) PanelConnection, &hReadEventsMT, 0, &dwThrdIDMT);
 if (hThrdMT==NULL) ULOGW ("[mt] Panel thread start error");
 
 hThrdSI8 = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) SI8Connection, &hReadEventsSI8, 0, &dwThrdIDSI8);
 if (hThrdSI8==NULL) ULOGW ("[si8] SI8 thread start error");

 hThrdIO = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) GetAllIOStatus, &hReadEventsIO, 0, &dwThrdIDIO);
 if (hThrdIO==NULL) ULOGW ("[io] Get IO thread start error");
 if (hThrdIO) CeSetThreadPriority(hThrdIO, 5); 

 hThrdAlg = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) MainAlgorithm, &hReadEventsAlg, 0, &dwThrdIDAlg);
 if (hThrdAlg==NULL) ULOGW ("[alg] Algorithm thread start error");

 hThrdService = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) ServiceThread, &hReadEventsService, 0, &dwThrdIDService); 
 if (hThrdService==NULL) ULOGW ("[serv] Service thread start error");
 GlobalMemoryStatus(&lpBuffer); ULOGW ("memory: [%d] %ld %ld",lpBuffer.dwMemoryLoad, lpBuffer.dwAvailPhys, lpBuffer.dwAvailVirtual); 
 AvailPhys=lpBuffer.dwAvailPhys;
 while (1)
	{
	 //GlobalMemoryStatus(&lpBuffer); ULOGW ("memory: [%d] %ld %ld",lpBuffer.dwMemoryLoad, lpBuffer.dwAvailPhys, lpBuffer.dwAvailVirtual);
	 if (count%5==0)
		{
		 GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, TEXT("hh:mm:ss"), InBuffer, sizeof(InBuffer));
		 WideCharToMultiByte(CP_ACP, 0, InBuffer, sizeof(InBuffer), buf, sizeof(buf), NULL,NULL);
		 if (strstr (buf,"22:00:")) { stopbytime=1; break; }
		}
	 if (FinishWork || FinishWork4) break;
	 Sleep (5000); count--;
	}
 GlobalMemoryStatus(&lpBuffer); ULOGW ("memory: [%d] %ld %ld [eaten=%ld]",lpBuffer.dwMemoryLoad, lpBuffer.dwAvailPhys, lpBuffer.dwAvailVirtual,AvailPhys-lpBuffer.dwAvailPhys);
// printf ("memory: [%d] %ld %ld [eaten=%ld]",lpBuffer.dwMemoryLoad, lpBuffer.dwAvailPhys, lpBuffer.dwAvailVirtual,AvailPhys-lpBuffer.dwAvailPhys);
 
 WorkEnable=0;			// disable all work
 Sleep (150000);		// waiting for the stop
 pac_DisableWatchDog (0);
 WorkEnable2=0;			// disable all work
 if (stopbytime) pac_Reboot();
 Sleep (2000);			// waiting for the stop
}
//----------------------------------------------------------------------------------------------------
// get system information
VOID GetInfo (VOID)
{
  DWORD mem_size,eeprom_size;
  char CPU[32],MAC[32],OS[32],SN[32],DLL[32];
  char slotCard[10];
  byte LAN = 1;
  byte slot = 1;
  int type = 0, nBattery1=0, nBattery2=0;
  bool bExist;

  bExist = pac_SDExists();
  pac_GetMacAddress(LAN,MAC);
  mem_size = pac_GetMemorySize(WINPAC_MEM_SRAM);
  eeprom_size = pac_GetMemorySize(WINPAC_MEM_EEPROM);
  pac_GetCPUVersion(CPU);
  pac_GetOSVersion(OS);
  pac_GetSerialNumber(SN);
  pac_GetSDKVersion(DLL);
  type=pac_GetRotaryID();
  nBattery1 = pac_GetBatteryLevel(1);
  nBattery2 = pac_GetBatteryLevel(2);
  ULOGW ("PAC seial number %s",SN);
  ULOGW ("CPU: %s | memory size: %ldKb | eeprom size: %ldKb",CPU,mem_size,eeprom_size);
  ULOGW ("OS installed: %s | SDK version: %s",OS, DLL);
  ULOGW ("Rotary switch in %d position", type);
  ULOGW ("mac adress %s",MAC);
  ULOGW ("battery level [1]=%d | [2]=%d",nBattery1,nBattery2);
  ULOGW ("device booted %ld seconds ago",pac_GetBPTimerTimeTick_ms()/1000);

  if (bExist) ULOGW ("micro SD card is installed"); else ULOGW ("micro SD card is not installed");
  for (slot=0; slot<=7; slot++)
	{
	 pac_GetModuleName(slot, slotCard);
     type=pac_GetModuleType(slot);
	 switch (type)
		{
		 case PAC_PARALLEL: ULOGW ("[%d] module in slot %s [0x%x] | general I-8000W module",slot,slotCard,type); break;
		 case PAC_PARALLEL_RW: ULOGW ("[%d] module in slot %s [0x%x] | I-8000RW module", slot,slotCard,type); break;
		 case PAC_SCAN: ULOGW ("[%d] module in slot %s [0x%x] | scan module", slot,slotCard,type); break;
		 case PAC_DI32: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 32 DI channels", slot,slotCard,type); break;
		 case PAC_32BIT: ULOGW ("[%d] module in slot %s [0x%x] | bit32 module", slot,slotCard,type); break;
		 case PAC_DO32: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 32 DO channels", slot,slotCard,type); break;
		 case PAC_DI16DO16: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 16 DI channels and 16 DO channels", slot,slotCard,type); break;
		 case PAC_DI16: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 16 DI channels",slot,slotCard,type); break;
		 case PAC_DO16: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 16 DO channels",slot,slotCard,type); break;
		 case PAC_DI8DO8: ULOGW ("[%d] module in slot %s [0x%x] | I-8000W module with 8 DI channels and 8 DO channels", slot,slotCard,type); break;
		 case PAC_8K: ULOGW ("[%d] module in slot %s [0x%x] | 8K series module",slot,slotCard,type); break;
		 default: ULOGW ("[%d] no module defined [0x%x]", slot,type);
		}
	}
}
//----------------------------------------------------------------------------------------------------
VOID CheckIO (VOID)
{
 //DWORD do_value=0x4,di_value=0;
 //ULOGW ("read IO modules complete"); 
}
//----------------------------------------------------------------------------------------------------
// [Thread] Get all input/output status/values 
VOID GetAllIOStatus (LPVOID lpParam)
{
 DWORD di_value,do_value4,do_value5,do_value6;
 bool rs=0; byte cnt=0;
 float	value=0;
 double	R=1.05, H=4.3, Sc=0,O=0,St=0,S=0;
 // float ao_value;
 while (WorkEnable2)
	{
	 pac_ReadAI(hPort, 0, 0, 8, &value);	// Давление пара на технологию
	 P_par_tech=(value-4)*10/16; aP_par_tech=value;
	 //if (P_par_tech<0) P_par_tech=0; ULOGW ("[wp][0] (0)value=%.4f",value);
	 pac_ReadAI(hPort, 0, 1, 8, &value);	// Давление пара на входе в теплообменник
	 P_par_in_heater=(value-4)*10/16; aP_par_in_heater=value;
 	 //ULOGW ("[wp][0] (1)value=%.4f",value);
	 pac_ReadAI(hPort, 0, 2, 8, &value);	// Давление воды на входе в теплообменник
	 P_water_in_heater=(value-4)*6/16; aP_water_in_heater=value;
	 //if (P_water_in_heater<0) P_water_in_heater=0; ULOGW ("[wp][0] (2)value=%.4f",value);
	 pac_ReadAI(hPort, 0, 3, 8, &value);	// Давление воды на выходе из теплообменника
	 P_water_out_heater=(value-4)*10/16; aP_water_out_heater=value;
	 pac_ReadAI(hPort, 0, 4, 8, &value);	// Давление воды на подогрев ГВС за баком-аккумулятором
	 P_water_gvs_accum=(value-4)*6/16;	 aP_water_gvs_accum=value;
	 pac_ReadAI(hPort, 0, 5, 8, &value);	// Уровень воды в баке-аккумуляторе
	 L_water_bak_accum=((value-4)*(float)2.5/16)-(float)0.3;	 aL_water_bak_accum=value;
	 pac_ReadAI(hPort, 0, 6, 8, &value);	// Давление воды на потребителей
	 P_water_potreb=(value-4)*10/16;		 aP_water_potreb=value;
	 pac_ReadAI(hPort, 0, 7, 8, &value);
	 S_KT=(value);							//-4)*10/16;

	 if (L_water_bak_accum>R*2) L_water_bak_accum=(float)R*2;
	 if (L_water_bak_accum<0) L_water_bak_accum=0;
	 
	 //float	R=1.15, H=4.44, a=0, Sc=0, O=0, p=0, St=0, S=0;
	 Sc=2*acos ((R-L_water_bak_accum)/R)*R*R/2;
	 O=sqrt (R*R-(R-L_water_bak_accum)*(R-L_water_bak_accum));
	 St=(R-L_water_bak_accum)*O/2;
	 V_water_bak_accum=((float)Sc-(float)St)*(float)H;
	 //ULOGW ("[wp] R=%.2f | L=%.2f | Sc=%.2f | O=%.2f | St=%.2f | H=%.2f",R,L_water_bak_accum,Sc,O,St,H);
	 //if (cnt%100==0) ULOGW ("[wp][0] (0)%.4f|(1)%.4f|(2)%.4f|(3)%.4f|(4)%.4f|(6)%.4f (V=%.4f)",P_par_tech,P_par_in_heater,P_water_in_heater, P_water_out_heater,P_water_gvs_accum,L_water_bak_accum,V_water_bak_accum);

	 // [1][MAI1.2] i-87017RW
	 pac_ReadAI(hPort, 1, 0, 8, &value);	// Температура пара на входе в теплообменник
	 T_par_in_heater=(value-4)*200/16;		aT_par_in_heater=value;
	 pac_ReadAI(hPort, 1, 1, 8, &value);	// Температура воды на входе в теплообменник
	 T_water_in_heater=(value-4)*100/16;	aT_water_in_heater=value;
	 pac_ReadAI(hPort, 1, 2, 8, &value);	// Температура воды на выходе из теплообменника	 
 	 T_water_out_heater=(value-4)*100/16;	aT_water_out_heater=value;
	 pac_ReadAI(hPort, 1, 3, 8, &value);	// Температура ГВС на потребителей
	 T_water_out_gvs=(value-4)*100/16;		aT_water_out_gvs=value;
	 pac_ReadAI(hPort, 1, 4, 8, &value);	// Температура подпиточной воды ХВС
	 T_water_podp_hvs=(value-4)*100/16-50;	aT_water_podp_hvs=value;
	 pac_ReadAI(hPort, 1, 5, 8, &value);	// Температура воды в баке-аккумуляторе
	 T_water_bak_accum=(value-4)*100/16;	aT_water_bak_accum=value;
	 pac_ReadAI(hPort, 1, 6, 8, &value);	// Температура воды в прачечной
	 T_water_prach=(value-4)*100/16;		aT_water_prach=value;
	 pac_ReadAI(hPort, 1, 7, 8, &value);	// Температура воды в столовой
	 T_water_stolv=(value-4)*100/16;		aT_water_stolv=value;

 	 if (aL_water_bak_accum<4 || V_water_bak_accum<0 || aT_water_in_heater<4 || aT_water_bak_accum<4 || aT_water_out_heater<4) FinishWork3=1;
	 else { FinishWork3=0; StatusFinish=0; }
	 //SYSTEMTIME tt={0}; GetLocalTime(&tt);
	 if (cnt%1000==0) 
		{
		 if (FinishWork3) ULOGW ("[wp][0][!!!] (6)%.3f (V=%.4f) [1] (0)%.3f|(1)%.3f|(2)%.3f|(3)%.3f|(4)%.3f|(5)%.3f|(6)%.3f|(7)%.3f",L_water_bak_accum,V_water_bak_accum,T_par_in_heater,T_water_in_heater,T_water_out_heater, T_water_out_gvs,T_water_podp_hvs,T_water_bak_accum,T_water_prach,T_water_stolv);
		 else ULOGW ("[wp][0] (6)%.3f (V=%.4f) [1] (0)%.3f|(1)%.3f|(2)%.3f|(3)%.3f|(4)%.3f|(5)%.3f|(6)%.3f|(7)%.3f",L_water_bak_accum,V_water_bak_accum,T_par_in_heater,T_water_in_heater,T_water_out_heater, T_water_out_gvs,T_water_podp_hvs,T_water_bak_accum,T_water_prach,T_water_stolv);
		}

	 // [2][MDI1.3] i-87040W
	 pac_ReadDI(hPort,2,32, &di_value);
 	 //if (di_value!=di_value2_prev)
	 if (1)
		{
		 podgvs_zatvor_napor_closed=(byte)(di_value&0x1);		// Затвор на напоре насоса подогрева ГВС открыт
		 podgvs_zatvor_napor_opened=(byte)((di_value&0x2)>>1);	// Затвор на напоре насоса подогрева ГВС закрыт
		 podgvs_rele_nasos_status=(byte)((di_value&0x4)>>2);	// Реле давления на всасе насоса подогрева ГВС
		 podgvs_regim_nasos_system=(byte)((di_value&0x8)>>3);	// Насос подогрева ГВС в режиме "Системное"
		 podgvs_regim_nasos_hand=(byte)((di_value&0x10)>>4);	// Насос подогрева ГВС в режиме "Ручное"
		 podgvs_kont_nasos_vkl=(byte)((di_value&0x20)>>5);		// Контактор насоса подогрева ГВС включен

		 gvs_zatv_nasos_opened=(byte)((di_value&0x40)>>6);		// Затвор на напоре насоса ГВС открыт
		 gvs_zatv_nasos_closed=(byte)((di_value&0x80)>>7);		// Затвор на напоре насоса ГВС закрыт
		 circgvs_rele_nasos_status=(byte)((di_value&0x100)>>8);	// Реле давления на всасе насоса циркуляции ГВС
		 circgvs_regim_nasos_system=(byte)((di_value&0x200)>>9);// Насос циркуляции ГВС в режиме "Системное"
		 circgvs_regim_nasos_hand=(byte)((di_value&0x400)>>10);	// Насос циркуляции ГВС в режиме "Ручное"
		 circgvs_kont_nasos_gvs=(byte)((di_value&0x800)>>11);	// Контактор насоса циркуляции ГВС включен

		 critical_temp_kond=(byte)((di_value&0x1000)>>12);		// Температура конденсата высокая
		 /*
		 ULOGW ("[wp][2] (0)%d|(1)%d|(2)%d|(3)%d|(4)%d|(5)%d|(6)%d|(7)%d|(8)%d|(9)%d(10)%d|(11)%d",
			podgvs_zatvor_napor_opened, podgvs_zatvor_napor_closed, podgvs_rele_nasos_status,
			podgvs_regim_nasos_system, podgvs_regim_nasos_hand, podgvs_kont_nasos_vkl,
			gvs_zatv_nasos_opened, gvs_zatv_nasos_closed, circgvs_rele_nasos_status,
			circgvs_regim_nasos_system, circgvs_regim_nasos_hand, circgvs_kont_nasos_gvs);
			*/
		 di_value2_prev=di_value;
		}
	 // [3][MDI1.4] i-87040W
	 pac_ReadDI(hPort,3,32, &di_value); 	
	 if (di_value!=di_value3_prev)
		{
 		 //ULOGW ("[wp][3] di_value=%x",di_value);
		 podgvs_regim_zatv_system=(byte)(di_value&0x1);				// Затвор на подогрев ГВС в режиме "Системное"
		 podgvs_zatv_nasos_closed=(byte)((di_value&0x2)>>1);		// Затвор на подогрев ГВС открыт
		 podgvs_zatv_nasos_opened=(byte)((di_value&0x4)>>2);		// Затвор на подогрев ГВС закрыт

		 podgvs_regim_obrat_system=(byte)((di_value&0x8)>>3);		// Затвор на обратке подогрева ГВС в режиме "Системное"
		 // changed 13_02
		 podgvs_zatv_obrat_closed=(byte)((di_value&0x10)>>4);		// Затвор на обратке подогрева ГВС открыт
		 podgvs_zatv_obrat_opened=(byte)((di_value&0x20)>>5);		// Затвор на обратке подогрева ГВС закрыт

		 circgvs_regim_zatv_system=(byte)((di_value&0x40)>>6);		// Затвор на циркуляцию ГВС в режиме "Системное"
		 circgvs_zatv_closed=(byte)((di_value&0x80)>>7);			// Затвор на циркуляцию ГВС открыт
		 circgvs_zatv_opened=(byte)((di_value&0x100)>>8);			// Затвор на циркуляцию ГВС закрыт

		 circgvs_regim_obrat_system=(byte)((di_value&0x200)>>9);		// Затвор на обратке циркуляции ГВС в режиме "Системное"
		 circgvs_zatv_obrat_opened=(byte)((di_value&0x400)>>10);		// Затвор на обратке циркуляции ГВС открыт
		 circgvs_zatv_obrat_closed=(byte)((di_value&0x800)>>11);		// Затвор на обратке циркуляции ГВС закрыт

		 regulator_klapan_tvoda_system=(byte)((di_value&0x1000)>>12);	// Клапан регулятора температуры воды в реж. "Системное"
		 regulator_klapan_tvoda_closed=(byte)((di_value&0x2000)>>13);	// Клапан регулятора температуры воды открыт
	 	 regulator_klapan_tvoda_opened=(byte)((di_value&0x4000)>>14);	// Клапан регулятора температуры воды закрыт

		 podphvs_zatv_regim_system=(byte)((di_value&0x10000)>>16);		// Затвор подпитки ХВС в режиме "Системное"
		 podphvs_zatv_hvs_closed=(byte)((di_value&0x20000)>>17);		// Затвор подпитки ХВС открыт
		 podphvs_zatv_hvs_opened=(byte)((di_value&0x40000)>>18);		// Затвор подпитки ХВС закрыт

		 podpar_zatv_regim_system=(byte)((di_value&0x80000)>>19);	// Затвор на подаче пара в режиме "Системное"
		 podpar_zatv_obrat_closed=(byte)((di_value&0x100000)>>20);	// Затвор на подаче пара открыт
		 podpar_zatv_obrat_opened=(byte)((di_value&0x200000)>>21);	// Затвор на подаче пара закрыт

		 ULOGW ("[wp][3] (0)%d|(1)%d|(2)%d|(3)%d|(4)%d|(5)%d|(6)%d|(7)%d|(8)%d|(9)%d(10)%d|(11)%d|(12)%d|(13)%d|(14)%d|(15)%d|(16)%d|(17)%d|(18)%d|(19)%d|(20)%d",
		 podgvs_regim_zatv_system, podgvs_zatv_nasos_opened, podgvs_zatv_nasos_closed,
		 podgvs_regim_obrat_system, podgvs_zatv_obrat_opened, podgvs_zatv_obrat_closed,
		 circgvs_regim_zatv_system, circgvs_zatv_opened, circgvs_zatv_closed,
		 circgvs_regim_obrat_system, circgvs_zatv_obrat_opened, circgvs_zatv_obrat_closed,

		 regulator_klapan_tvoda_system, regulator_klapan_tvoda_opened, regulator_klapan_tvoda_closed,
		 podphvs_zatv_regim_system,	podphvs_zatv_hvs_opened, podphvs_zatv_hvs_closed, 
		 podpar_zatv_regim_system, podpar_zatv_obrat_opened, podpar_zatv_obrat_closed);
		 di_value3_prev=di_value;
		}

	 // [4][MDO1.5] i-87040W
	 do_value4=podgvs_zatv_nasos_open+podgvs_zatv_nasos_close*2+podgvs_kont_nasos_on*4+podgvs_kont_nasos_off*8+
		 circgvs_zatv_nasos_open*16+circgvs_zatv_nasos_close*32+circgvs_kont_nasos_on*64+circgvs_kont_nasos_off*128;
	 if (do_value4!=do_value4_prev)
		{
		 do_value4_prev=do_value4;
		 rs=pac_WriteDO(hPort,4,16, do_value4);
		 //ULOGW ("[wp] write [4!]0x%x [5]0x%x [6]0x%x (res=%d)",do_value4,do_value5,do_value6,rs);
		}
	 // [5][MDO1.5] i-87061W
	 do_value5=podgvs_zatv_gvs_open+podgvs_zatv_gvs_close*2+podgvs_zatv_obr_open*4+podgvs_zatv_obr_close*8+
		 circgvs_zatv_gvs_open*16+circgvs_zatv_gvs_close*32+circgvs_zatv_obr_open*64+circgvs_zatv_obr_close*128+
		 podphvs_zatv_hvs_open*256+podphvs_zatv_hvs_close*512+podpar_zatv_par_open*4096+podpar_zatv_par_close*8192;
	 if (do_value5!=do_value5_prev)
		{
		 do_value5_prev=do_value5;
		 rs=pac_WriteDO(hPort,5,16, do_value5);
		 //ULOGW ("[wp] write [4]0x%x [5!]0x%x [6]0x%x (res=%d)",do_value4,do_value5,do_value6,rs);
		}
	 // [5][MDO1.6] i-87061W
	 do_value6=regtemp_klap_voda_open+regtemp_klap_voda_close*2;
	 if (do_value6!=do_value6_prev)
		{
		 do_value6_prev=do_value6;
		 rs=pac_WriteDO(hPort,6,8, do_value6);
		 //ULOGW ("[wp] write [4]0x%x [5]0x%x [6!]0x%x (res=%d)",do_value4,do_value5,do_value6,rs);
		}
	 Sleep (100);
	 pac_RefreshWatchDog (0);
	 //WriteDataFile (0);
	 cnt++;
	}
 ExitThread(0);
}
//----------------------------------------------------------------------------------------------------
// main algorithm
VOID MainAlgorithm (LPVOID lpParam)
{
 DWORD	do_value=0,di_value=0,di_latch=0;
 bool	res=0;
 uint	cnt=0,t=0,sl=0;
 // включаем циркуляцию
 podgvs_zatv_nasos_open=1; podgvs_zatv_nasos_close=0; Sleep (8000); // Открыть затвор на напоре насоса подогрева ГВС (ЗД1) 
 podgvs_kont_nasos_on=1; podgvs_kont_nasos_off=0; Sleep (3000);		// Выключить контактор насоса подогрева ГВС (М1)
 StopAll ();
 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	Sleep (1000);	// открываем задвижку ХВС
 Statusfill=1;
 //if (FinishWork) StatusFinish=1;

 PumpStop=0;
 while (WorkEnable)
	{  
	 // ----------------------------------------------------------------------------------------------
	 //ULOGW ("[wp] [%d|%d|%d|%d|%d || %d|%d|%d|%d|%d] [%d | %d]",StartTest1,StartTest2,StartTest3,StartTest4,StartTest5,EndTest1,EndTest2,EndTest3,EndTest4,EndTest5,WaterOK,PumpStop);
	 if (V_water_bak_accum>Level_Alarm_Up) LevelOK=1; else LevelOK=0;
	 if (podgvs_rele_nasos_status) WaterOK=0; else WaterOK=1;
	 if (podgvs_kont_nasos_vkl) PumpStop=1; else PumpStop=0;
	 
	 //#include "kernel_testregim.cpp"

	 Sleep (1000);
	 //ULOGW ("[wp] [----]");
	 if (TestRegim) continue;
	 if (FinishWork2 || StatusFinish || FinishWork3) continue;
	 // ----------------------------------------------------------------------------------------------
	 // рабочий режим
	 // Fillbak		-	заполнение бака
	 // уровень ниже нижнего предупредительного
	 if (FinishWork2 || FinishWork3) { StopAll (); StatusFinish=1; continue; }	
	 if (StatusFinish || FinishWork2 || FinishWork3) continue;

	 if (V_water_bak_accum<Level_Warn_Down) bak_level_warning_low=1;
	 if (V_water_bak_accum<Level_Work_Down && !Fillbak) { FillBak(); bak_level_work_low=1; }
	 if (V_water_bak_accum>Level_Alarm_Up) 
		{
		 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;		// Закрыть затвор на ХВС (ЗД3)
		 Statusfill=0; Fillbak=0;
		}

	 // ----------------------------------------------------------------------------------------------
	 if (regulator_klapan_tvoda_NOT_closed && !regulator_klapan_tvoda_closed) { StopPar(); continue; }
	 else regulator_klapan_tvoda_NOT_closed=false;
	 //if (podpar_zatv_obrat_NOT_closed && !podpar_zatv_obrat_closed) continue;
	 //else podpar_zatv_obrat_NOT_closed=false;
	 //if (podphvs_zatv_hvs_NOT_closed && !podphvs_zatv_hvs_closed) continue;
	 //else podphvs_zatv_hvs_NOT_closed=false;
	 // ----------------------------------------------------------------------------------------------

 	 if (V_water_bak_accum>Level_Warn_Down && !StatusFinish && !critical_temp_kond) // 8.05.13 +датчик температуры на конденсат // && V_water_bak_accum<Level_Work_Up 21.06.13 меньше верхнего
	 if (T_water_bak_accum<Temp_Work_Down) // <65
		{
		 bak_level_work_low=0;
		 // Statusfill=0; // ??
		 ULOGW ("[wp][ZD4] (podgvs_zatv_gvs_open)");
		 //podgvs_zatv_nasos_open=0; podgvs_zatv_nasos_close=1;			// Закрыть затвор на напоре насоса подогрева ГВС (ЗД1)
		 if (!podgvs_zatv_nasos_opened) { podgvs_zatv_gvs_open=1; podgvs_zatv_gvs_close=0; Sleep (9000); } // Открыть затвор на подогрев ГВС (ЗД4)
		 ULOGW ("[wp][S] podgvs_rele_nasos_status=%d",podgvs_rele_nasos_status);
		 if (podgvs_rele_nasos_status)
			{
			 ULOGW ("[wp][ZD1] (podgvs_zatvor_napor_closed)=%d",podgvs_zatvor_napor_closed);
			 if (podgvs_zatvor_napor_closed)		// Затвор на напоре насоса подогрева ГВС открыт
				{
				 ULOGW ("[wp][ZD5] (podgvs_zatv_obrat_closed)=%d",podgvs_zatv_obrat_closed);
				 if (podgvs_zatv_obrat_closed)
					{
					 ULOGW ("[wp][ZD5] (podgvs_zatv_obr_open)");					 
					 podgvs_zatv_obr_open=1; podgvs_zatv_obr_close=0; Sleep (10000); // Открыть затвор на обратке подогрева ГВС (ЗД5)
					}
				 ULOGW ("[wp][ZD5] (podgvs_zatv_obrat_opened)=%d",podgvs_zatv_obrat_opened);
				 if (podgvs_zatv_obrat_opened || !podgvs_zatv_obrat_closed)
					{
					 ULOGW ("[wp][M1] (podgvs_kont_nasos_on)");
					 podgvs_kont_nasos_on=1; podgvs_kont_nasos_off=0;// Включить контактор насоса подогрева ГВС (М1)
					 Sleep (3000);
					 if (!podgvs_zatvor_napor_opened)
						{
						 ULOGW ("[wp][ZD1] (podgvs_zatv_nasos_open)");
						 podgvs_zatv_nasos_open=1; podgvs_zatv_nasos_close=0; Sleep (8000); // Открыть затвор на напоре насоса подогрева ГВС (ЗД1)
						}
					 while (WorkEnable)
						{
						 if (podgvs_kont_nasos_vkl && podgvs_zatvor_napor_opened) break;
					     ULOGW ("[wp][M1] podgvs_kont_nasos_vkl=%d ZD1=%d",podgvs_kont_nasos_vkl,podgvs_zatvor_napor_opened);
						 Sleep (1000);
						}
					}
				 ULOGW ("[wp][ZD5] podgvs_zatv_obrat_opened=%d",podgvs_zatv_obrat_opened);
				 if (podgvs_zatv_obrat_opened)
					{
					 ULOGW ("[wp] P_par_tech=%f",P_par_tech);
					 if (P_par_tech>0.5) // -3
						{
						 ULOGW ("[wp][ZT] (regtemp_klap_voda_close)");
						 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;// Закрыть клапан регулятора температуры воды
						 while (WorkEnable)
							{
							 if (regulator_klapan_tvoda_closed) break;
							 if (T_water_bak_accum>Temp_Work_Up) break;
							 if (V_water_bak_accum>Level_Work_Up) break;

						     ULOGW ("[wp][ZT] regulator_klapan_tvoda_closed=%d",regulator_klapan_tvoda_closed);
							 Sleep (1000);
							}
						 ULOGW ("[wp][ZD8] (podpar_zatv_par_open)");
						 podpar_zatv_par_open=1; podpar_zatv_par_close=0;	// Открыть затвор на подаче пара   (ЗД8)
						 //ULOGW ("[wp][ZD7] (circgvs_zatv_obr_open)");
						 //circgvs_zatv_obr_open=1; circgvs_zatv_obr_close=0;	// Открыть затвор конденсата в бак (ЗД7)
						 while (WorkEnable)
							{
							 podpar_zatv_par_open=1; podpar_zatv_par_close=0;	// Открыть затвор на подаче пара   (ЗД8)
							 //circgvs_zatv_obr_open=1; circgvs_zatv_obr_close=0;	// Открыть затвор конденсата в бак (ЗД7)
							 if (cnt%100==0) ULOGW ("[wp][ZD7,8] ZD7=%d, ZD8=%d | T=%f < %d | To=%f[%d,%d]",circgvs_zatv_obrat_opened,podpar_zatv_obrat_opened,T_water_bak_accum,Temp_Work_Up,T_water_out_heater,Temp_Work_Down,Temp_Work_Up);
							 Regulator ();
							 if (FinishWork2) { StopAll (); StatusFinish=1; break; }

							 if (T_water_bak_accum>Temp_Warn_Down) StartM2 ();
							
							 if (critical_temp_kond)  // 8.05.13 +датчик температуры на конденсат
								{
								 ULOGW ("[wp] [!!!] (critical_temp_condensat) [%d]",critical_temp_kond);
								 StopPar ();
								 break;
								}
							 if (V_water_bak_accum<Level_Work_Down && !NoHVS && !Statusfill) 
								{
								 if (cnt%10==0) ULOGW ("[wp] [!!!] (voda_level_work_down) [%f < %d]",V_water_bak_accum,Level_Work_Down);
								 //ULOGW ("[wp][ZD3] (podphvs_zatv_hvs_open)");
								 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	Sleep (10000); // открываем задвижку ХВС
								 Statusfill=1;
								}
							 if (V_water_bak_accum<Level_Alarm_Down)
								{
 								 ULOGW ("[wp] [!!!] (voda_level_alarm_down) [%f < %d]",V_water_bak_accum,Level_Alarm_Down);
								 StopPar ();
								 break; // >70
								}
							 Sleep (1000);
							 if (T_water_bak_accum>Temp_Work_Up || T_water_out_heater>85) 
								{
								 ULOGW ("[wp] [!!!] (voda_temp_work_high) [%f > %d]",T_water_bak_accum,Temp_Work_Up);
								 StopPar ();
								 break; // >70
								}						 	 						 
							 //CheckPPotr ();

							 if (V_water_bak_accum>Level_Work_Up && Statusfill) 
								{
								 if (cnt%10==0) ULOGW ("[wp] [!!!] (voda_level_work_high) [%f > %d]",V_water_bak_accum,Level_Work_Up);
								 StopFill();
								}
							 if (V_water_bak_accum>Level_Warn_Up)
								{
								 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;		// Закрыть затвор на ХВС (ЗД3)
								 Statusfill=0; Fillbak=0;
								}
							 // уровень выше верхнего аварийного
							if (V_water_bak_accum>Level_Alarm_Up) 
								{
								 bak_level_critical_high=1;
								 ULOGW ("[wp] [!!!] (voda_level_alarm_high) [%f > %d]",V_water_bak_accum,Level_Alarm_Up);
								 ULOGW ("[wp] [ZD8] (podpar_zatv_par_close)");
								 podpar_zatv_par_open=0; podpar_zatv_par_close=1;		// Закрыть затвор на подаче пара  (ЗД8)
								 ULOGW ("[wp] [ZT] (regtemp_klap_voda_close)");
								 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;	// Закрыть клапан регулятора температуры воды
								 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;		// Закрыть затвор на ХВС (ЗД3)
								 Statusfill=0; Fillbak=0;
								}
							 else bak_level_critical_high=0; 

							 if (regulator_klapan_tvoda_NOT_closed) break;

							 if (!podgvs_rele_nasos_status)
								{
								 ULOGW ("[wp] [!!!] (podgvs_rele_nasos_status)");
								 podpar_zatv_par_open=0; podpar_zatv_par_close=1;		// Закрыть затвор на подаче пара   (ЗД8)
								 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;	// Закрыть клапан регулятора температуры воды
								 //podgvs_zatv_obr_open=0; podgvs_zatv_obr_close=1; 		// Закрыть затвор на обратке подогрева ГВС (ЗД5)
								 podgvs_kont_nasos_on=0; podgvs_kont_nasos_off=1; 		// Выключить контактор насоса подогрева ГВС (М1)
								 //podgvs_zatv_nasos_open=0; podgvs_zatv_nasos_close=1;   // Закрыть затвор на напоре насоса подогрева ГВС (ЗД1)
								 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;		// Закрыть затвор на ХВС (ЗД3)
								 //podgvs_zatv_gvs_open=0; podgvs_zatv_gvs_close=1;		// Закрыть затвор на подогрев ГВС (ЗД4)
								 Statusfill=0;
								 if (podphvs_zatv_hvs_opened && podgvs_zatv_nasos_closed) NoHVS=1;
								 break; // >70
								}
							 cnt++;
							}
						}
					}
				}
			 else if (!podgvs_zatvor_napor_closed)
				{
				 ULOGW ("[wp][ZD1] (podgvs_zatv_nasos_close)");
				 podgvs_zatv_nasos_open=0; podgvs_zatv_nasos_close=1;// Закрыть затвор на напоре насоса подогрева ГВС (ЗД1)
				 Sleep (7000);
				}
			}
		}	

	 // уровень выше рабочего
	 if (V_water_bak_accum>Level_Work_Up)
		{
		 //ULOGW ("[wp] [!!!] (voda_level_work_high) [%f > %d] StopFill",V_water_bak_accum,Level_Work_Up);
		 StopFill ();
		}
	 else bak_level_work_high=0; 
	 
	 // уровень выше верхнего предупредительного
	 if (V_water_bak_accum>Level_Warn_Up) bak_level_warning_high=1;
	 else bak_level_warning_high=0; 

	 if (V_water_bak_accum<Level_Work_Down && !NoHVS && !Statusfill) 
			{
			 if (cnt%10==0) ULOGW ("[wp] [!!!] (voda_level_work_down) [%f < %d]",V_water_bak_accum,Level_Work_Down);
			 //ULOGW ("[wp][ZD3] (podphvs_zatv_hvs_open)");
			 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	Sleep (10000); // открываем задвижку ХВС
			 Statusfill=1; Fillbak=1;
			}

	 // уровень выше верхнего аварийного
	 if (V_water_bak_accum>Level_Alarm_Up) 
		{
		 bak_level_critical_high=1;
		 ULOGW ("[wp] [!!!] (voda_level_alarm_high) [%f > %d]",V_water_bak_accum,Level_Alarm_Up);
		 ULOGW ("[wp] [ZD8] (podpar_zatv_par_close)");
		 podpar_zatv_par_open=0; podpar_zatv_par_close=1;		// Закрыть затвор на подаче пара  (ЗД8)
		 ULOGW ("[wp] [ZT] (regtemp_klap_voda_close)");
		 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;	// Закрыть клапан регулятора температуры воды
		 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;		// Закрыть затвор на ХВС (ЗД3)
		 Statusfill=0; Fillbak=0;
		}
	 else bak_level_critical_high=0; 


	 // уровень ниже нижнего предупредительного
	 if (V_water_bak_accum<Level_Warn_Down) 
		{
		 bak_level_warning_low=1;
		 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	// Открыть затвор подпитки ХВС    (ЗД3)
		 Statusfill=1; Fillbak=1;
		}
	 else bak_level_warning_low=0; 

	 // уровень ниже нижнего аварийного
	 if (V_water_bak_accum<Level_Alarm_Down && !FinishWork2)
		{
		 NoHVS=0;
		 ULOGW ("[wp] [!!!] (voda_level_critical_low) [%f < %d] [S=%d F=%d]",L_water_bak_accum,Level_Alarm_Down,StatusFinish,FinishWork2);
		 bak_level_critical_low=1;	
		 if (!podgvs_zatv_obrat_opened)
			{
			 podgvs_zatv_obr_open=1; podgvs_zatv_obr_close=0;		// Открыть затвор на обратке подогрева ГВС (ЗД5)
			}
		 Sleep(8000);
		 //if (podgvs_zatvor_napor_closed) // !!! gvs_zatv_nasos_closed
		 if (1) // 19_07
			{
			 ULOGW ("[wp] [M2] (circgvs_kont_nasos_off)");
			 circgvs_kont_nasos_on=0; circgvs_kont_nasos_off=1;		// Выключить контактор насоса циркуляции ГВС  (М2)
			 Sleep(8000); StatusM2=0;
			 // см kernel_1707.cpp
			 //if (gvs_zatv_nasos_closed==1 && circgvs_kont_nasos_gvs==0 && circgvs_zatv_closed==1) !!! убрали М2 анализ 06.05.13
			 ULOGW ("[wp] [ZD3] (podphvs_zatv_hvs_open)");
			 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	// Открыть затвор подпитки ХВС    (ЗД3)
			 Statusfill=1;
			 Sleep (3000);
			}
		}
	 else bak_level_critical_low=0; 

	 if (T_water_bak_accum>Temp_Warn_Down && !StatusFinish)
		{ 
		 //ULOGW ("[wp] [!!!] StatusFinish=%d | FinishWork2=%d | FinishWork3=%d",StatusFinish,FinishWork2,FinishWork3);
		 StartM2 (); 
		}

	 // температура выше верхней рабочей
	 if (T_water_bak_accum>Temp_Work_Up) voda_temp_work_high=1;
	 else voda_temp_work_high=0;
	 // температура ниже нижней рабочей
	 if (T_water_bak_accum<Temp_Work_Down) voda_temp_work_low=1;
	 else voda_temp_work_low=0;
	 // температура выше верхней предупредительной
	 if (T_water_bak_accum>Temp_Warn_Up)
		{		 
		 if (!voda_temp_warning_high) 
			{
			 ULOGW ("[wp] [!!!] (voda_temp_warning_high) [%f > %d]",T_water_bak_accum,Temp_Warn_Up);
			 ULOGW ("[wp] [ZT] (regtemp_klap_voda_close)");
			}
		 voda_temp_warning_high=1;
		 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;	// Закрыть клапан регулятора температуры воды
		 timer_open_KT=0;
		}
	 else voda_temp_warning_high=0;

	 // температура ниже нижней предупредительной
	 if (T_water_bak_accum<Temp_Warn_Down) voda_temp_warning_low=1;
	 else voda_temp_warning_low=0;

	 // температура выше верхней аварийной
	 if (T_water_bak_accum>Temp_Alarm_Up || T_water_out_heater>85) 
		{
		 if (!voda_temp_critical_high)
			{ 
			 ULOGW ("[wp] [!!!] (voda_temp_critical_high) [%f > %d]",T_water_bak_accum,Temp_Alarm_Up); 
			 voda_temp_critical_high=1; 
			}
 		 ULOGW ("[wp] [ZD8] (podpar_zatv_par_close)");
		 podpar_zatv_par_open=0; podpar_zatv_par_close=1;		// Закрыть затвор на подаче пара  (ЗД8)
		 ULOGW ("[wp] [ZT] (regtemp_klap_voda_close)");
		 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;	// Закрыть клапан регулятора температуры воды
		 timer_open_KT=0;
		 StopPar ();
		}
	 else voda_temp_critical_high=0;

	 // температура ниже нижней аварийной
	 if (T_water_bak_accum<Temp_Alarm_Down) 
		{		  
		 if (!voda_temp_critical_low) { ULOGW ("[wp] [!!!] (voda_temp_critical_low) [%f < %d]",T_water_bak_accum,Temp_Alarm_Down); voda_temp_critical_low=1; }
		 if (StatusM2) StopM2 ();
		}
	 else voda_temp_critical_low=0;

 	 // давления на потребителей нет
	 //CheckPPotr ();
	}

 //---------------------------------------------------------------------------------------------------
 ULOGW ("[wp] (closed all)");
 StopAll (); Sleep (1000);
 ULOGW ("[wp] (closed all finished)");
 ExitThread(0); 
}
//----------------------------------------------------------------------------------------------------
// decode WinPAC error code
VOID OutError (int iInitSuccess)
{
 switch (iInitSuccess)
	{
	 case 0x00001: ULOGW ("[error %x] Unknow Error",iInitSuccess); break;
	 case 0x10001: ULOGW ("[error %x] Slot registered error",iInitSuccess); break;
	 case 0x10002: ULOGW ("[error %x] Slot not registered error",iInitSuccess); break;
	 case 0x10003: ULOGW ("[error %x] Unknown Module",iInitSuccess); break;
	 case 0x10004: ULOGW ("[error %x] Module doesn't exist",iInitSuccess); break;
	 case 0x10005: ULOGW ("[error %x] Invalid COM port number",iInitSuccess); break;
	 case 0x10006: ULOGW ("[error %x] Function not supported",iInitSuccess); break;
	 case 0x11001: ULOGW ("[error %x] EEPROM accesses invalid address",iInitSuccess); break;
	 case 0x11002: ULOGW ("[error %x] SRAM accesses invalid address",iInitSuccess); break;
	 case 0x11003: ULOGW ("[error %x] SRAM accesses invalid type",iInitSuccess); break;
	 case 0x11004: ULOGW ("[error %x] NVRAM accesses invalid address",iInitSuccess); break;
	 case 0x11005: ULOGW ("[error %x] EEPROM write protection",iInitSuccess); break;
	 case 0x11006: ULOGW ("[error %x] EEPROM write fail",iInitSuccess); break;
	 case 0x11007: ULOGW ("[error %x] EEPROM read fail",iInitSuccess); break;
	 case 0x12001: ULOGW ("[error %x] The input value is invalid",iInitSuccess); break;
	 case 0x12002: ULOGW ("[error %x] The wdt doesn't exist",iInitSuccess); break;
	 case 0x12003: ULOGW ("[error %x] The wdt init error",iInitSuccess); break;
	 case 0x13001: ULOGW ("[error %x] Create interrupt's event failure",iInitSuccess); break;
	 case 0x14001: ULOGW ("[error %x] Uart check sum error",iInitSuccess); break;
	 case 0x14002: ULOGW ("[error %x] Uart read timeout",iInitSuccess); break;
	 case 0x14003: ULOGW ("[error %x] Uart response error",iInitSuccess); break;
	 case 0x14004: ULOGW ("[error %x] Uart under input range",iInitSuccess); break;
	 case 0x14005: ULOGW ("[error %x] Uart exceed input range",iInitSuccess); break;
	 case 0x14006: ULOGW ("[error %x] Uart open filed",iInitSuccess); break;
	 case 0x14007: ULOGW ("[error %x] Uart get Comm Modem status error",iInitSuccess); break;
	 case 0x14008: ULOGW ("[error %x] Uart get wrong line status",iInitSuccess); break;
	 case 0x15001: ULOGW ("[error %x] IO card does not support this API function",iInitSuccess); break;
	 case 0x15002: ULOGW ("[error %x] API unsupport this IO card",iInitSuccess); break;
	 case 0x15003: ULOGW ("[error %x] Slot's value exceeds its range",iInitSuccess); break;
	 case 0x15004: ULOGW ("[error %x] Channel's value exceeds its range",iInitSuccess); break;
	 case 0x15005: ULOGW ("[error %x] Gain's value exceeds its range",iInitSuccess); break;
	 case 0x15006: ULOGW ("[error %x] Unsupported interrupt mode",iInitSuccess); break;
	 case 0x15007: ULOGW ("[error %x] I/O value is out of the range",iInitSuccess); break;
	 case 0x15008: ULOGW ("[error %x] I/O channel is out of the range",iInitSuccess); break;
	 default: ULOGW ("[error] unknown error code [0x%x]",iInitSuccess);
	}
}
//----------------------------------------------------------------------------------------------------
// decode WinPAC error code
VOID OutModbusError (int iInitSuccess)
{
 switch (iInitSuccess)
	{
	 case	MB_RTC_OK:				ULOGW ("[modbus] error [%d] RTC OK",iInitSuccess); break;
	 case	MB_ILLEGAL_FUNCTION:	ULOGW ("[modbus] error [%d] illegal function",iInitSuccess); break;
	 case	MB_ILLEGAL_DATA_ADDRESS:ULOGW ("[modbus] error [%d] illegal data address",iInitSuccess); break;
	 case	MB_ILLEGAL_DATA_VALUE:	ULOGW ("[modbus] error [%d] illegal data value",iInitSuccess); break;
	 case	MB_SLAVE_DEVICE_FAILURE:ULOGW ("[modbus] error [%d] slave device failure",iInitSuccess); break;
	 case	MB_ACKNOWLEDGE:			ULOGW ("[modbus] error [%d] acknowledge",iInitSuccess); break;
	 case	MB_SLAVE_DEVICE_BUSY:	ULOGW ("[modbus] error [%d] slave device busy",iInitSuccess); break;
	 case	MB_NEGATIVE_ACKNOWLEDGE:ULOGW ("[modbus] error [%d] negative acknowledge",iInitSuccess); break;
	 case	MB_MEMORY_PARITY_ERROR:	ULOGW ("[modbus] error [%d] memory parity error",iInitSuccess); break;
	 case	MB_GATEWAY_PATH_UNAVAILABLE:	ULOGW ("[modbus] error [%d] gateway path unavailable",iInitSuccess); break;
	 case	MB_GATEWAY_FAILED_TO_RESPOND:	ULOGW ("[modbus] error [%d] gateway failed to respond",iInitSuccess); break;
	 case	MB_OPEN_PORT_ERROR:		ULOGW ("[modbus] error [%d] open COM/TCP Port error",iInitSuccess); break;
	 case	MB_PORTNO_OVER:			ULOGW ("[modbus] error [%d] COM Port is 1-8",iInitSuccess); break;
	 case	MB_PORT_NOT_OPEN:		ULOGW ("[modbus] error [%d] COM/TCP Port does not open yet",iInitSuccess); break;
	 case	MB_FUN_ERROR:			ULOGW ("[modbus] error [%d] modbus Fun. No. error",iInitSuccess); break;
	 case	MB_READ_COUNT_OVER:		ULOGW ("[modbus] error [%d] reading Count of Register or Bits is over range (RTU: 120 register, 1920 coils)",iInitSuccess); break;
	 case	MB_SLAVENO_OVER:		ULOGW ("[modbus] error [%d] modbus Slave No. must be 1 - 247",iInitSuccess); break;
	 case	MB_ADDRESS_OVER:		ULOGW ("[modbus] error [%d] register or Coil Address must count from 1",iInitSuccess); break;
	 case	MB_COMM_TIMEOUT:		ULOGW ("[modbus] error [%d] communication timeout",iInitSuccess); break;
	 case	MB_CRC_ERROR:			ULOGW ("[modbus] error [%d] RTU CRC Check error",iInitSuccess); break;
	 case	MB_LRC_ERROR:			ULOGW ("[modbus] error [%d] ASCII LRC Check error",iInitSuccess); break;
	 case	MB_INVALID_SOCKET:		ULOGW ("[modbus] error [%d] Initial Socket error",iInitSuccess); break;
	 case	MB_TCP_CONNECT_ERROR:   ULOGW ("[modbus] error [%d] connect Remote Modbus Server error",iInitSuccess); break;
	 case	MB_TCP_SEND_ERROR:      ULOGW ("[modbus] error [%d] send TCP Data error",iInitSuccess); break;
	 case	MB_TCP_TIMEOUT:         ULOGW ("[modbus] error [%d] Waiting Modbus Response Timeout",iInitSuccess); break; 
	 case	MB_WSA_INIT_ERROR:      ULOGW ("[modbus] error [%d] WSA Startup error",iInitSuccess); break;
	 case	MB_TCP_SOCKET_ERROR:    ULOGW ("[modbus] error [%d] Create Socket error",iInitSuccess); break;
	 case	MB_TCP_BIND_ERROR:      ULOGW ("[modbus] error [%d] TCP Server Bind error",iInitSuccess); break;
	 case	MB_TCP_LISTEN_ERROR:    ULOGW ("[modbus] error [%d] TCP Server Listen error",iInitSuccess); break;
	 case	MB_TCP_HAS_DATA:		ULOGW ("[modbus] error [%d] it has data from remote Modbus Master",iInitSuccess); break;
	 case	MB_WRITE_COUNT_OVER:    ULOGW ("[modbus] error [%d] reading Count of Register or Bits is over range (RTU: 120 register, 1920 coils)",iInitSuccess); break;
	 default: ULOGW ("[modbus] unknown error code [0x%x]",iInitSuccess);
	}
}
//----------------------------------------------------------------------------------------------------
bool	Regulator ()
{
 UINT	sl=0;
//if (circgvs_zatv_obrat_opened && podpar_zatv_obrat_opened && T_water_out_heater<70)
 float Tup=75.0,Tdown=70.0, maxgate=40.0;
 //Tup=T_water_in_heater+25;
 //Tdown=T_water_in_heater+20;

 Tup=T_water_in_heater+(maxgate-T_water_in_heater*(maxgate/(Temp_Work_Up+10)));
 Tdown=Tup-5;
 if (Tup>80) Tup=80;
 //Tdown=80+(50-80*(50/70))=68; 
 //Tdown=T_water_in_heater+20;
 //if (Tup>Temp_Work_Up)	{	 Tup=Temp_Work_Up;	 Tdown=Temp_Work_Down;	}

 if (podpar_zatv_obrat_opened && T_water_out_heater<Tdown && timer_open_KT<11100)
	{
	 regtemp_klap_voda_open=1; regtemp_klap_voda_close=0;// Открыть клапан регулятора температуры воды	 
	 sl=(UINT)(Tdown*30-T_water_out_heater*30);
	 if (sl<0) sl=30; if (sl>110) sl=110;
	 ULOGW ("[wp][ZT] (regtemp_klap_voda_open) [%f - %f (%d)] [timer=%d]",Tdown,T_water_out_heater,sl,timer_open_KT);
	 Sleep (sl);
	 //ULOGW ("[wp][ZT] (regtemp_klap_voda_stop)");
	 timer_open_KT+=sl;
	 regtemp_klap_voda_open=0; regtemp_klap_voda_close=0;// Открыть клапан регулятора температуры воды
	 Sleep (7000);
	}
 if (podpar_zatv_obrat_opened && T_water_out_heater>Tup)
 //if (circgvs_zatv_obrat_opened && podpar_zatv_obrat_opened && T_water_out_heater>70)
	{
	 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;// Открыть клапан регулятора температуры воды
	 sl=(UINT)((T_water_out_heater-Tup)*1000);
	 if (sl<100) sl=100; if (sl>1500) sl=1500;
	 ULOGW ("[wp][ZT] (regtemp_klap_voda_close) [%f - %f (%d)]",T_water_out_heater,Tup,sl);
	 Sleep (sl);
	 //ULOGW ("[wp][ZT] (regtemp_klap_voda_close)");
	 timer_open_KT=0;
	 regtemp_klap_voda_open=0; regtemp_klap_voda_close=0;// Открыть клапан регулятора температуры воды
	 Sleep (4000);
	}
 return 1;
}

//----------------------------------------------------------------------------------------------------
bool FillBak ()
{
 ULOGW ("[wp] (level low) L=%f < Lwd=%d",V_water_bak_accum,Level_Work_Down);
 ULOGW ("[wp][ZD3] (podphvs_zatv_hvs_open)");
 podphvs_zatv_hvs_open=1; podphvs_zatv_hvs_close=0;	Sleep (10000); // открываем задвижку ХВС		 
 ULOGW ("[wp] (level low) nasos_stat=%d",podgvs_rele_nasos_status);
 Fillbak=1; Statusfill=1;

 if (podphvs_zatv_hvs_opened && podgvs_rele_nasos_status)
	{
	 ULOGW ("[wp] (level low)(podgvs_zatv_obrat_closed)=%d",podgvs_zatv_obrat_closed);
	 if (podgvs_zatv_obrat_closed)
		{
		 podgvs_zatv_obr_open=1; podgvs_zatv_obr_close=0;		// Открыть затвор на обратке подогрева ГВС (ЗД5)
		}
	}
 return 1;
}
//----------------------------------------------------------------------------------------------------
bool StopPar ()
{
 UINT	count=36; // counters 
 ULOGW ("[wp] [ZD3] (podphvs_zatv_hvs_close)");
 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;			// Закрыть затвор на ХВС (ЗД3)
 //ULOGW ("[wp] [ZD4] (podgvs_zatv_gvs_open)");
 //podgvs_zatv_gvs_open=1; podgvs_zatv_gvs_close=0;			// Открыть затвор на подогрев ГВС (ЗД4)
 
 ULOGW ("[wp] [ZD8] (podpar_zatv_par_close)");
 podpar_zatv_par_open=0; podpar_zatv_par_close=1;			// Закрыть затвор на подаче пара   (ЗД8)

 ULOGW ("[wp] [ZT] (regtemp_klap_voda_close)");
 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1; Sleep (8000);	// Закрыть клапан регулятора температуры воды
 while (WorkEnable && !regulator_klapan_tvoda_closed && count)
	{
     ULOGW ("[wp][ZT] regulator_klapan_tvoda_closed=%d [%d]",regulator_klapan_tvoda_closed,count);
	 Sleep (5000); count--;
	}
 if (!count) regulator_klapan_tvoda_NOT_closed=true;
 else timer_open_KT=0;

 //ULOGW ("[wp] [ZD7] (circgvs_zatv_obr_close)");
 //circgvs_zatv_obr_open=0; circgvs_zatv_obr_close=1; 		// Закрыть затвор конденсата в бак (ЗД7)
 count=30;
 Sleep (8000);
 while (fabs(T_water_in_heater-T_water_out_heater)>((T_water_in_heater+T_water_out_heater)/20) && count)
	{
     ULOGW ("[wp] T_water_in_heater=%f, T_water_out_heater=%f [%f - %f] [%d]",T_water_in_heater,T_water_out_heater,fabs(T_water_in_heater-T_water_out_heater),(T_water_in_heater+T_water_out_heater)/20,count);
	 Sleep (5000); count--;
	}
 //podgvs_zatv_obr_open=0; podgvs_zatv_obr_close=1; Sleep (5000);		// Закрыть затвор на обратке подогрева ГВС (ЗД5)
 //podgvs_zatv_nasos_open=0; podgvs_zatv_nasos_close=1; Sleep (5000); // Закрыть затвор на напоре насоса подогрева ГВС (ЗД1)
 //podgvs_kont_nasos_on=0; podgvs_kont_nasos_off=1; Sleep (5000);		// Выключить контактор насоса подогрева ГВС (М1)
 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;					// Закрыть затвор на ХВС (ЗД3)
 return 1;
}
//----------------------------------------------------------------------------------------------------
bool StopFill ()
{ 
 if (Statusfill==0) return 0;
 UINT	count=36;
 ULOGW ("[wp] (level high) L=%f > Lwd=%d",V_water_bak_accum,Level_Work_Up); 
 bak_level_work_high=1;
 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1; Sleep (8000);	// Закрыть клапан регулятора температуры воды
 while (WorkEnable && !regulator_klapan_tvoda_closed && count)
	{
     ULOGW ("[wp][ZT] regulator_klapan_tvoda_closed=%d",regulator_klapan_tvoda_closed);
	 Sleep (5000); count--;
	}
 if (!count) regulator_klapan_tvoda_NOT_closed=true;
 else timer_open_KT=0;

 //podgvs_zatv_gvs_open=1; podgvs_zatv_gvs_close=0; Sleep (15000); // Открыть затвор на подогрев ГВС (ЗД4)
 if (podgvs_zatv_nasos_opened)
	{
	 ULOGW ("[wp] [ZD3](close) [ZD4](open) (level high)");
	 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;			// Закрыть затвор подпитки ХВС    (ЗД3)
	 Stopfill=0; Statusfill=0;
	}
 return 1;
}
//----------------------------------------------------------------------------------------------------
bool StartM2 ()
{ 
 if (StatusM2) return 0;
 if (P_water_potreb>P_Work_Potr && voda_potr_stop) return 0;
 if (T_water_bak_accum<Temp_Warn_Down || StatusFinish) return 0;

 ULOGW ("[wp] (start M2) [M2,SS2]",circgvs_kont_nasos_gvs,circgvs_rele_nasos_status); 
 //ULOGW ("[wp] [ZD6] (circgvs_zatv_gvs_open)");
 if (!circgvs_zatv_opened)
	{
	 circgvs_zatv_gvs_open=1; circgvs_zatv_gvs_close=0;		// Открыть затвор на циркуляцию ГВС (ЗД6)
	}
 circgvs_zatv_nasos_open=1; circgvs_zatv_nasos_close=0;		// Открыть затвор на напоре насоса циркуляции ГВС (ЗД2)
 Sleep (5000);
 ULOGW ("[wp] [M2]%d [SS2]%d [ZD6]%d",circgvs_kont_nasos_gvs,circgvs_rele_nasos_status,circgvs_zatv_opened);
 //if (!circgvs_kont_nasos_gvs && circgvs_rele_nasos_status && circgvs_zatv_opened) !!! 06.05.13 убрали
 if (circgvs_rele_nasos_status && circgvs_zatv_opened)
	{
	 //ULOGW ("[wp] [ZD2] (circgvs_zatv_nasos_close)");
	 //circgvs_zatv_nasos_open=0; circgvs_zatv_nasos_close=1;	// Закрыть затвор на напоре насоса циркуляции ГВС (ЗД2)
	 //Sleep(8000);
	 //if (gvs_zatv_nasos_closed)
	 if (1)
		{
		 ULOGW ("[wp] [M2] (circgvs_kont_nasos_on)");
		 circgvs_kont_nasos_on=1; circgvs_kont_nasos_off=0;		// Включить контактор насоса циркуляции ГВС  (М2)
	 	 //circgvs_zatv_nasos_open=1; circgvs_zatv_nasos_close=0;	// Открыть затвор на напоре насоса циркуляции ГВС (ЗД2)
		 StatusM2=1;
		}
	}
 return 1;
}
//----------------------------------------------------------------------------------------------------
bool StopM2 ()
{
 ULOGW ("[wp] [StopM2] [ZD2] (circgvs_zatv_nasos_close)");
 //circgvs_zatv_nasos_open=0; circgvs_zatv_nasos_close=1;	// Закрыть затвор на напоре насоса циркуляции ГВС (ЗД2)
 Sleep(8000);
 //if (gvs_zatv_nasos_closed)
	{
	 ULOGW ("[wp] [M2] (circgvs_kont_nasos_off)");
	 circgvs_kont_nasos_on=0; circgvs_kont_nasos_off=1;		// Выключить контактор насоса циркуляции ГВС  (М2)
	 Sleep (2000);
	 circgvs_kont_nasos_on=0; circgvs_kont_nasos_off=1;		// Выключить контактор насоса циркуляции ГВС  (М2)
	 //ULOGW ("[wp] [ZD6] (circgvs_zatv_gvs_close)");
	 //circgvs_zatv_gvs_open=0; circgvs_zatv_gvs_close=1;		// Открыть затвор на циркуляцию ГВС (ЗД6)
	 StatusM2=0;
	}
 return TRUE;
}
//----------------------------------------------------------------------------------------------------
bool CheckPPotr ()
{
 if (P_water_potreb>P_Alarm_Potr)	// давления на потребителей нет
	{
	 voda_potr_high=1;				// давление воды на потребителей высокое
	 if (timer_Ppotr_high%100==0) ULOGW ("[wp] [!!!] (voda_potr_high) [%f > %f][%d]",P_water_potreb,P_Alarm_Potr,timer_Ppotr_high);
	 timer_Ppotr_high++; 
	} 
 else 
	{ 
	 if (voda_potr_high) ULOGW ("[wp] [!!!] (voda_potr_norm) [%f < %f][%d]",P_water_potreb,P_Work_Potr,timer_Ppotr_high);
	 timer_Ppotr_high=0; voda_potr_high=0; 
	 if (P_water_potreb<P_Work_Potr) { StartM2 (); voda_potr_stop=0; }
	}	 
 if (timer_Ppotr_high>=300)
	{
	 voda_potr_stop=1; 
	 //ULOGW ("[wp] [!!!] (voda_potr_stop) [%f < %f]",P_water_potreb,P_Alarm_Potr);
	 if (StatusM2) StopM2 ();
	}
 return 0;
}
//----------------------------------------------------------------------------------------------------
bool StopAll ()
{
 UINT	count=80;
 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1; Sleep (1000);	// Закрыть клапан регулятора температуры воды
 timer_open_KT=0;
 podpar_zatv_par_open=0; podpar_zatv_par_close=1;					// Закрыть затвор на подаче пара   (ЗД8)
 //circgvs_zatv_obr_open=0; circgvs_zatv_obr_close=1; Sleep (1000);	// Закрыть затвор конденсата в бак (ЗД7) 
 while (!regulator_klapan_tvoda_closed && count)
	{
	 ULOGW ("[wp][exit][ZT] regulator_klapan_tvoda_closed=%d",regulator_klapan_tvoda_closed);
	 regtemp_klap_voda_open=0; regtemp_klap_voda_close=1;
	 Sleep (2000); count--;
	}
 if (!count) regulator_klapan_tvoda_NOT_closed=true;
 count=80;
 while (!podpar_zatv_obrat_closed && count)
	{
	 ULOGW ("[wp][exit][ZD8] podpar_zatv_obrat_closed=%d",podpar_zatv_obrat_closed);
	 podpar_zatv_par_open=0; podpar_zatv_par_close=1;
	 Sleep (2000); count--;
	} 
 if (!count) podpar_zatv_obrat_NOT_closed=true;

 count=80;
 while (fabs(T_water_in_heater-T_water_out_heater)>10 && count)
		{
		 if (aT_water_in_heater<4 || aT_water_out_heater<4) break;
	     ULOGW ("[wp][exit] T_water_in_heater=%f, T_water_out_heater=%f [%f - %f]",T_water_in_heater,T_water_out_heater,fabs(T_water_in_heater-T_water_out_heater),(T_water_in_heater+T_water_out_heater)/20);
		 Sleep (2000); count--;
		}
 //podgvs_zatv_obr_open=0; podgvs_zatv_obr_close=1; Sleep (8000);		// Закрыть затвор на обратке подогрева ГВС (ЗД5)
 //podgvs_zatv_nasos_open=0; podgvs_zatv_nasos_close=1; Sleep (8000); // Закрыть затвор на напоре насоса подогрева ГВС (ЗД1) 
 //while (WorkEnable)
 //{
 //	 ULOGW ("[wp][exit][ZD1] podgvs_zatvor_napor_closed=%d",podgvs_zatvor_napor_closed);
 //	 if (podgvs_zatvor_napor_closed) break;
 //	 Sleep (5000);
 //	}
 podgvs_kont_nasos_on=0; podgvs_kont_nasos_off=1; Sleep (3000);		// Выключить контактор насоса подогрева ГВС (М1)
 //podgvs_zatv_gvs_open=0; podgvs_zatv_gvs_close=1; Sleep (5000);		// Закрыть затвор на подогрев ГВС (ЗД4)
 podphvs_zatv_hvs_open=0; podphvs_zatv_hvs_close=1;	Sleep (5000);	// Закрыть затвор на ХВС (ЗД3)
 Statusfill=0;
 StopM2 ();
 return true;
}
