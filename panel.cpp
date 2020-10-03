#include <windows.h>
#include "winpacsdk.h"
#include "panel.h"
#include "Modbus_ARM.h"

extern byte	WorkEnable;		// work flag
extern short currentregim;	// regim selection
extern byte	TestRegim;		// test regim

HANDLE	hPort2;				// Panel port handler
HANDLE	hPort5;				// Panel port handler

extern	VOID ULOGW (CHAR* string, ...);		// log file function
extern	VOID OutError (int iInitSuccess);	// out in console and log modbus error
extern	VOID OutModbusError (int iInitSuccess);

int ModbusRTU_Read(int adr, int start, int count, byte *iRecv, int func);
int ModbusRTU_Write(int adr, int start, int count, byte len, byte *iSend, int func);
int ModbusRTU_Answer(int adr, byte count);

UINT CRC (const BYTE* const Data, const BYTE DataSize);
unsigned int CalcCRC(unsigned int c,unsigned int crc);
WORD CRC16 (const BYTE *nData, WORD wLength);
VOID ReadCOM (LPVOID lpParam);

static	TCHAR	errorBuf[32];	// buffer for error messages
static	int		result=0;		// read/write result
//----------------------------------------------------------------------------------------------------
// [Thread] Get/Set all input/output values from/to panel
VOID PanelConnection (LPVOID lpParam)
{
 //int port = *(int *) lpParam;	// port number
 int adr=0x1;					// address on modbus
 int speed=115200;
 int iReadSuccess=0;
 byte	data[150];				// output buffer
 byte	data2[150];				// output buffer
 short	in_reg=0;
 byte	count=0;

 int port=3;
 int iInitSuccess = MBRTUInit(port,speed,1,8,1,200);
 if (!iInitSuccess) ULOGW ("[mt] initialize modbus driver on port [COM%d:115200:Even:8bit:1sb] for [panel] success",port);
 else OutModbusError (iInitSuccess);
 
 while (WorkEnable)
	{
	 //Sleep (1000);
	 //iReadSuccess=MBRTU_R_Coils(port,adr,40+1,1,&StartTest1,0x1);
	 //if (iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //ULOGW ("[mt] [%d|%d|%d]",lStartTest1,lStartTest2,lStartTest3);
	 //iReadSuccess=MBRTU_R_Coils(port,adr,41+1,1,&StartTest2,0x1);
	 //if (iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //ULOGW ("[mt] [%d|%d|%d]",lStartTest1,lStartTest2,lStartTest3);
	 //iReadSuccess=MBRTU_R_Coils(port,adr,42+1,1,&StartTest3,0x1);
	 //if (iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //ULOGW ("[mt] [%d|%d|%d]",lStartTest1,lStartTest2,lStartTest3);
	 //if (iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //ULOGW ("[mt] [%d|%d|%d|%d]",lStartTest1,lStartTest2,lStartTest3);

	 //iReadSuccess=MBRTU_R_Coils(port,adr,45,4,&lStartTest1,0x1);
	 //if (!iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //ULOGW ("[mt] [%x|%x|%x|%x]",lStartTest1,lStartTest2,lStartTest3,lStartTest4);
	 
	 //iReadSuccess=MBRTU_R_Coils(port,adr,0+1,100,mas,0x1);
	 //if (iReadSuccess) ULOGW ("[mt] failed error code: %d",iReadSuccess);
	 //for (int ff=0;ff<10;ff++)
	 //	ULOGW ("[mas] (%d) [%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]",ff*10,mas[ff*10+0],mas[ff*10+1],mas[ff*10+2],mas[ff*10+3],mas[ff*10+4],mas[ff*10+5],mas[ff*10+6],mas[ff*10+7],mas[ff*10+8],mas[ff*10+9]);
	 
	 //UINT PANEL_CYCLE=0;
	 //iReadSuccess=MBRTU_R_Registers(port,adr,54+1,1,&in_reg,0x3);
	 //if (!iReadSuccess) 
	 //{ PANEL_CYCLE=(uint)in_reg; ULOGW ("[mt] read cycle time from panel [%d]",PANEL_CYCLE); }
	 //else ULOGW ("[mt] failed error code: %d",iReadSuccess);

	 memcpy (data,&P_par_tech,sizeof(P_par_tech));
	 memcpy (data+4,&P_par_in_heater,sizeof(P_par_in_heater));
	 memcpy (data+8,&P_water_in_heater,sizeof(P_water_in_heater));
	 memcpy (data+12,&P_water_out_heater,sizeof(P_water_out_heater));
	 memcpy (data+16,&P_water_gvs_accum,sizeof(P_water_gvs_accum));
	 memcpy (data+20,&L_water_bak_accum,sizeof(L_water_bak_accum));
	 memcpy (data+24,&V_water_bak_accum,sizeof(V_water_bak_accum));
	 memcpy (data+28,&P_water_potreb,sizeof(P_water_potreb));
	 iReadSuccess=MBRTU_W_Multi_Registers(port,adr,100+1,16,(short *)data);	 
	 if (iReadSuccess) ULOGW ("[mt] write half AI signals failed error code: %d",iReadSuccess);

	 memcpy (data,&T_par_in_heater,sizeof(T_par_in_heater));
	 memcpy (data+4,&T_water_in_heater,sizeof(T_water_in_heater));
	 memcpy (data+8,&T_water_out_heater,sizeof(T_water_out_heater));
	 memcpy (data+12,&T_water_out_gvs,sizeof(T_water_out_gvs));
	 memcpy (data+16,&T_water_podp_hvs,sizeof(T_water_podp_hvs));
	 memcpy (data+20,&T_water_bak_accum,sizeof(T_water_bak_accum));
	 memcpy (data+24,&T_water_prach,sizeof(T_water_prach));
	 memcpy (data+28,&T_water_stolv,sizeof(T_water_stolv));

	 iReadSuccess=MBRTU_W_Multi_Registers(port,adr,116+1,20,(short *)data);
	 if (iReadSuccess) ULOGW ("[mt] write half AI signals failed error code: %d",iReadSuccess);

	 memcpy (data,&aP_par_tech,sizeof(aP_par_tech));						// 140
	 memcpy (data+4,&aP_par_in_heater,sizeof(aP_par_in_heater));			// 142
	 memcpy (data+8,&aP_water_in_heater,sizeof(aP_water_in_heater));		// 144
	 memcpy (data+12,&aP_water_out_heater,sizeof(aP_water_out_heater));		// 146
	 memcpy (data+16,&aP_water_gvs_accum,sizeof(aP_water_gvs_accum));		// 148
	 memcpy (data+20,&aL_water_bak_accum,sizeof(aL_water_bak_accum));		// 150
	 memcpy (data+24,&aT_par_in_heater,sizeof(aT_par_in_heater));			// 152
	 memcpy (data+28,&aT_water_in_heater,sizeof(aT_water_in_heater));		// 154
	 memcpy (data+32,&aT_water_out_heater,sizeof(aT_water_out_heater));		// 156
	 memcpy (data+36,&aT_water_out_gvs,sizeof(aT_water_out_gvs));			// 158
	 memcpy (data+40,&aT_water_podp_hvs,sizeof(aT_water_podp_hvs));			// 160
	 memcpy (data+44,&aT_water_bak_accum,sizeof(aT_water_bak_accum));		// 162
	 memcpy (data+48,&aT_water_prach,sizeof(aT_water_prach));				// 164
	 memcpy (data+52,&aT_water_stolv,sizeof(aT_water_stolv));				// 166

	 memcpy (data+56,&V1_dushCGTS,sizeof(V1_dushCGTS));						// 168
	 memcpy (data+60,&V2_dushPFI,sizeof(V2_dushPFI));						// 170
	 memcpy (data+64,&V3_stol,sizeof(V3_stol));								// 172
	 memcpy (data+68,&V4_prach,sizeof(V4_prach));							// 174

 	 memcpy (data+72,&aP_water_potreb,sizeof(aP_water_potreb));				// 176
 	 memcpy (data+76,&timer_Ppotr_high,sizeof(timer_Ppotr_high));			// 178

	 iReadSuccess=MBRTU_W_Multi_Registers(port,adr,140+1,40,(short *)data);
	 if	(iReadSuccess) ULOGW ("[mt] write AI signals in milliampers: %d failed",iReadSuccess);

	 memcpy (data2, &podgvs_zatvor_napor_closed, 33);
	 iReadSuccess=MBRTU_W_Multi_Coils(port,adr,50+1,33,data2);
	 if (iReadSuccess) ULOGW ("[mt] write half DI signals failed error code: %d",iReadSuccess);

	 memcpy (data2, &podgvs_zatv_nasos_open, 37);
	 iReadSuccess=MBRTU_W_Multi_Coils(port,adr,1,37,data2);
	 if (iReadSuccess) ULOGW ("[mt] write half DI signals failed error code: %d",iReadSuccess);

	 //memcpy (data2, &bak_level_critical_low, 14);
	 //iReadSuccess=MBRTU_W_Multi_Coils(port,adr,201,14,data2);
	 //if (iReadSuccess) ULOGW ("[mt] write half DI signals failed error code: %d",iReadSuccess);
	 
	 iReadSuccess=MBRTU_R_Coils(port,adr,41,7,&StartTest1,0x1);
	 memcpy (data2, &EndTest1, 10);
	 //byte	EndTest1=0;		// 253
	 //byte	LevelOK=0;		// 254
	 //byte	WaterOK=0;		// 255
	 //byte	PumpStop=0;		// 256
	 //byte	EndTest2=0;		// 257
	 //byte	StartPar3=0;	// 258
	 //byte	EndTest3=0;		// 259
	 //byte	EndTest4=0;		// 260
	 //byte	EndTest5=0;		// 261
	 //byte	PumpStop2=0;	// 262

	 memcpy (data2+10, &TestRegim, 1);		//263
	 memcpy (data2+11, &WorkEnable, 1);		//264
	 memcpy (data2+12, &FinishWork, 1);		//265
	 memcpy (data2+13, &WorkEnable2, 1);	//266
	 memcpy (data2+14, &StatusFinish, 1);	//267
	 memcpy (data2+15, &FinishWork2, 1);	//268
	 memcpy (data2+16, &NoHVS, 1);			//269
	 memcpy (data2+17, &Statusfill, 1);		//270
	 memcpy (data2+18, &StatusM2, 1);		//271
	 iReadSuccess=MBRTU_W_Multi_Coils(port,adr,253+1,19,data2);

	 // read all coils - commands from panel
	 //MBRTU_R_Coils(port,adr,1,48,&podgvs_zatvor_napor_closed,0x1);
	 // read all coils - commands from panel
	 //MBRTU_R_Coils(port,adr,50,32,&podgvs_zatv_nasos_open,0x1);
	 //MBRTU_R_Coils(port,adr,200,14,&bak_level_critical_low,0x1);

	 // send all values to panel	 	
	 //memcpy (data,&SRV_REGIM,sizeof(SRV_REGIM));				// 400 
	 //MBRTU_W_Multi_Registers(port,adr,400+1,20,(short *)data);
	 //MBRTU_W_Multi_Coils(port,adr,78+1,9,data);

	 //memcpy (data, &SRV_SON, 18);
	 //MBRTU_W_Multi_Coils(port,adr,400+1,18,data);
	 //if (!MBRTU_W_Multi_Coils(port,adr,400+1,18,data)) ULOGW ("[mt] write current SON-CDP [%d]",SRV_SON);
	 //memcpy (data, &SRV_RD, 18);
	 //MBRTU_W_Multi_Coils(port,adr,420+1,18,data);
	 //if (!MBRTU_W_Multi_Coils(port,adr,420+1,18,data)) ULOGW ("[mt] write current RD-ABSV [%d]",SRV_RD);
	 
	 //memcpy (data, &FQ1_ERROR, 10);
	 //MBRTU_W_Multi_Coils(port,adr,10+1,10,data);
	 //if (!MBRTU_W_Multi_Coils(port,adr,10+1,10,data)) ULOGW ("[mt] write DO (FQ1_ERROR): [%d %d %d %d %d %d %d %d %d %d]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
	 //else ULOGW ("[mt] write DO (FQ1_ERROR) signals failed");

	 //MBRTU_W_Multi_Registers(port,adr,10+1,20,(short *)data);
	 //memcpy (data, &SERV_SU, 10);
	 //iReadSuccess =MBRTU_W_Multi_Coils(port,adr,120+1,10,data);
	 //memcpy (data, &FQ1_TRIG, 21); 	 
	 //iReadSuccess =MBRTU_W_Multi_Coils(port,adr,100+1,8,data);
	 //iReadSuccess =MBRTU_W_Multi_Coils(port,adr,110+1,8,data+7);
	 //iReadSuccess =MBRTU_W_Multi_Coils(port,adr,120+1,8,data+14);

	 //if (!iReadSuccess) ULOGW ("[mt] write DO[100/110/120]: [%d %d %d %d %d %d %d] [%d %d %d %d %d %d %d] [%d %d %d %d %d %d %d]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15],data[16],data[17],data[18],data[19],data[20]);
	 //else ULOGW ("[mt] write all DO [100/110/120] signals failed error code: %d",iReadSuccess);	 
	 count++;	 
	}
 ULOGW ("[mt] PanelConnection finish");
 MBRTUClose(port);
 // recieve scene number from panel
 // service: recieve in/out command
 ExitThread(0);
}
//--------------------------------------------------------------------------------------------------------------------
// answer on modbus master request
int ModbusRTU_Answer(int adr, byte count)
{
 byte	data[40];		// data array
 UINT	crc=0;		//(* CRC checksum *)
 bool	res=FALSE;
 DWORD	bytes=0;

 res=uart_BinRecv (hPort2,(char *)data,count);
 if (!res) 
	{
	 ULOGW ("[MT] error recieve from panel");
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}
 else
	{
	 ULOGW ("[MT] RD (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
	 if (data[2]>2)
		{
		 crc = CRC16 (data, data[2]+3);
	 	 ULOGW ("[MT] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,data[data[2]+3],data[data[2]+4]);
		}
	}
 
 data[0]=adr;
 //data[1]=func;
 if (data[1]==3) count=data[5];
 else count=data[5]*2;
 data[2]=count;
 for (int i=0; i<count; i++) data[3+i]=0;
 crc = CRC16 (data, 3+count);
 data[3+count]=crc%256;
 data[4+count]=crc/256; 
 res = uart_BinSend(hPort2, (char *)data, 5+count);
 if (data[1]==3) ULOGW ("[MT] SD (0x%x) (0x%x) (0x%x) (0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5]);
 return 0;
}
//--------------------------------------------------------------------------------------------------------------------
// Modbus read coils/registers function
int ModbusRTU_Read(int adr, int start, int count, byte *iRecv, int func)
{
 byte data[40];		// data array
 UINT	crc=0;		//(* CRC checksum *)
 bool	res=FALSE;
 DWORD bytes=0;

 data[0]=adr;
 data[1]=func;
 data[2]=start/256;
 data[3]=start%256;
 data[4]=count/256;
 data[5]=count%256;
 crc = CRC16 (data, 6);

 data[6]=crc%256;
 data[7]=crc/256; 
 res = uart_BinSend(hPort2, (char *)data, 9);
 ULOGW ("[MT] (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);

 if (res) ULOGW ("[MT] send to panel success");
 else  
	{
	 ULOGW ("[MT] error send to panel");
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}	 
 Sleep (30);
 bytes=uart_GetDataSize(hPort2,IN_DATA);
 ULOGW ("[MT] recieve %d bytes",bytes);
 res=uart_BinRecv (hPort2,(char *)iRecv,10);
 if (!res) 
	{
	 ULOGW ("[MT] error recieve from panel");
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}
 if (bytes)
	{
	 if (iRecv[2]>2)
		{
		 crc = CRC16 (data, iRecv[2]+3);
	 	 ULOGW ("[MT] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,iRecv[iRecv[2]+3],iRecv[iRecv[2]+4]);
		}
	}
 return 0;
}
//--------------------------------------------------------------------------------------------------------------------
// Modbus write coils/registers function
int ModbusRTU_Write(int adr, int start, int count, byte len, byte *iSend, int func)
{
 byte data[40];		// data array
 UINT	crc=0;		//(* CRC checksum *)
 bool	res=FALSE;
 DWORD bytes=0;

 data[0]=adr;
 data[1]=func;
 if (func==PresetMultiRegister)
	{
	 data[2]=start/256;
	 data[3]=start%256;
	 data[4]=count/256;
	 data[5]=count%256;
     data[6]=len;
     for (byte i=0; i<len; i++) data[7+i]=iSend[i];	 
     crc = CRC16 (data, 7+len); 
	 data[7+len]=crc%256;
	 data[7+len+1]=crc/256; 
     ULOGW ("[MT] (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) (0x%x) 0x%x [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
     res = uart_BinSend(hPort2, (char *)data, len+9);
	}
 if (func==PresetSingleRegister) 
	{
 	 data[2]=start/256;
	 data[3]=start%256;
	 for (byte i=0; i<len; i++) data[4+i]=iSend[i];
     crc = CRC16 (data, 4+len); 
	 data[4+len]=crc%256;
	 data[4+len+1]=crc/256; 
	 ULOGW ("[MT] (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
	 res = uart_BinSend(hPort2, (char *)data, len+6);
	}

 if (res) ULOGW ("[MT] send to panel success");
 else  
	{
	 ULOGW ("[MT] error send to panel");
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}	 
 Sleep (100);
 bytes=uart_GetDataSize(hPort2,IN_DATA);
 ULOGW ("[MT] recieve %d bytes",bytes);
 res=uart_BinRecv (hPort2,(char *)iSend,bytes);
 if (!res) 
	{
	 ULOGW ("[MT] error recieve from panel");
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}
 if (bytes)
	{
     ULOGW ("[MT] RD (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) (0x%x 0x%x 0x%x 0x%x ... )",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);	 
	 if (iSend[5]>2)
		{
		 crc = CRC16 (data, iSend[2]*2+3);
	 	 ULOGW ("[MT] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,iSend[iSend[2]+3],iSend[iSend[2]+4]);
		}
	}
 return 0;
}
//---------------------------------------------------------------------------------------------------------------------
int crc16 (byte a)
{
 UINT reg,tmp;
 UINT i;
    
 reg = 0xFFFF;                 
 reg ^= (UINT)a;    
    
 for(i=0;i<8;i++)
    {
     tmp = reg;
     reg >>= 1;        
     if((tmp <<=15)==0x8000) reg ^= 0xA001;
    }
 return reg;
}
//--------------------------------------------------------------------------------------------------------------------
UINT CRC (const BYTE* const Data, const BYTE DataSize)
{
 UINT _CRC = 0;
 BYTE* _Data = (BYTE*)Data;
 for(unsigned int i = 0; i < DataSize; i++) 
    {
     //ULOGW ("!%d [0x%x] > [%x]",i,*_Data,(UINT)_CRC);
     _CRC = CalcCRC(*_Data, _CRC);
	 //_CRC = crc16 (*_Data);

     _Data++;
     //ULOGW ("@%d [0x%x] > [%u]",i,*_Data,(UINT)_CRC);
    }

 return _CRC;
}
//--------------------------------------------------------------------------------------------------------------------
unsigned int CalcCRC(unsigned int c,unsigned int crc)
{
 int count,flg;
 for (count=0;count<8;count++)
    {
     flg=crc&0x8000;
     crc<<=1;
     if(((c)&0x80)!=0)crc+=1;
	 if(flg!=0)crc^=0x1021;
	    c<<=1;
    }
 return crc;
}

WORD CRC16 (const BYTE *nData, WORD wLength)
{
static const WORD wCRCTable[] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

BYTE nTemp;
WORD wCRCWord = 0xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord ^= wCRCTable[nTemp];
   }
   return wCRCWord;

}
//------------------------------------------------------------------------------------------------------------------
VOID ReadCOM (LPVOID lpParam)
{
 bool	res=FALSE;
 DWORD bytes=0;
 byte	iRecv[50];
 while (WorkEnable)
	{
	 Sleep (50);
	 bytes=uart_GetDataSize(hPort5,IN_DATA);
	 ULOGW ("[mt] recieve %d bytes",bytes);
	 res=uart_BinRecv (hPort5,(char *)iRecv,10);
	 if (!res) 
		{
		 ULOGW ("[MT] error recieve from panel");
		 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
		 ULOGW ("[MT] error [0x%x]: %ls",pac_GetLastError(), errorBuf);
		}
	 else ULOGW ("[MT] RECV (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",iRecv[0],iRecv[1],iRecv[2],iRecv[3],iRecv[4],iRecv[5],iRecv[6],iRecv[7],iRecv[8],iRecv[9]);
	}
}
//------------------------------------------------------------------------------------------------------------------
