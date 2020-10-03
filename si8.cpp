#include <windows.h>
#include "Modbus_ARM.h"
#include "winpacsdk.h"
#include "si.h"

extern byte	WorkEnable;		// флаг рабочего режима
extern byte	TestRegim;		// флаг тестового режима

extern	VOID ULOGW (CHAR* string, ...);				// log file function
VOID	OutServError (byte iInitSuccess);			// out in console and log SRV error
byte	CRC (char* in, byte count, byte* crc);		// crc calculation function
byte	SendData (int type, int adr, unsigned func, byte* ndata, byte* data, byte nbytes);	// send/recieve data function
VOID	ReadRegisters (int adr);					// read all input/output signals
VOID	OutSRVError (byte iInitSuccess);			// вывод ошибки сервопривода
//unsigned Hash(char Byte, char nbit, unsigned CRC);
//UINT Hash2(BYTE* Data,INT Len);
//unsigned short owenCRC16(unsigned char* packet, size_t length);

float	ConvertDataToValue	(byte* data, byte len);	// конвертаци€ считанных данных в значение
uint	ConvertHexValue	(byte* data, byte len);		// конвертаци€ считанных данных в 0x16

HANDLE	hPort3;					// SI8 port handler

static  TCHAR	errorBuf[32];	// buffer for error messages
static	int		result=0;		// read/write result
//----------------------------------------------------------------------------------------------------
// [Thread] Get/Set all values from all SI8
VOID SI8Connection (LPVOID lpParam)
{
 int	adr=0;						// address on modbus
 byte	data[100];					// input/output buffer
 byte	ret=0;						// return code
 UINT	value=0;
 float	val=0.0,del=0.0;

 hPort3 = uart_Open("COM2:,9600,N,8,1");
 uart_EnableCheckSum(hPort3, false);
 uart_SetTimeOut(hPort3, 50, CTO_TIMEOUT_ALL);

 if (hPort3) ULOGW ("[si8] initialize SI8 driver on port [COM2:9600:None:8bit:1sb] success (hPort3=%x)",hPort3);
 else
	{
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
 	 ULOGW ("[si8] error open COM2 internal port on speed 9600 [8-N-1] [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}
 //dev	D681
 //ver	2D5B	ASCII	¬ерси€ прошивки прибора

 while (WorkEnable)
 for (int si=0;si<sizeof(SIdevice)/sizeof(SIdevice[0]);si++)
	{
	 //1	DCNT	C173	DEC_dot0| SGND	—читать показани€ счетчика импульсов	-9999999Е.. 9999999
	 //2	DSPD	8FC2	DEC_dot0		—читать показани€ расходомера			0Е 9999999
	 //3	DTMR	E69C	CLK_frm			—читать показани€ таймера (счетчика времени)	0Е.99999595999
	 if (SendData (1, SIdevice[si].adr, COM_DCNT, (byte *)"", data, 0)) 
		{ 
		 value=data[1]*1000000+data[2]*100000+data[3]*10000+data[4]*1000+data[5]*100+data[6]*10+data[7];
		 if (data[0]==0) del=1;
		 if (data[0]==1) del=10;
		 if (data[0]==2) del=100;
		 if (data[0]==3) del=1000;
		 //del=(float)pow (10,data[0]);
		 //data[0]=0; data[8]=0;
		 //val=(float)atof ((char *)data);
		 if (del) val=value/(float)del;
		 //if (SIdevice[si].adr==3) ULOGW ("[si8][%d] flow meter: [%x][%x][%x][%x][%x][%x][%x][%x] [%d][%f][%d]",SIdevice[si].adr,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],value,val,del);
		 if (SIdevice[si].adr==2) V4_prach=val;
		 if (SIdevice[si].adr==3) V1_dushCGTS=val;
		 if (SIdevice[si].adr==5) V2_dushPFI=val;
		 if (SIdevice[si].adr==4) V3_stol=val;
		 //ULOGW ("[si8] [1][%f] [2][%f] [3][%f] [4][%f]",V1_dushCGTS,V2_dushPFI,V3_stol,V4_prach);
		}
	 if (SendData (1, SIdevice[si].adr, COM_DSPD, (byte *)"", data, 0)) 
		{
		 value=data[0]*10000000+data[1]*1000000+data[2]*100000+data[3]*10000+data[4]*1000+data[5]*100+data[6]*10+data[7];
		 data[8]=0;
		 val=(float)atof ((char *)data);
		 //ULOGW ("[si8][%d] flow meter: [%x][%x][%x][%x][%x][%x][%x][%x] [%d]",SIdevice[si].adr,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],value);
		 //value=(data[0]<<24)+(data[1]<<16)+(data[2]<<8)+data[3]; 
		 //if (SIdevice[si].adr==3) V1_dushCGTS=(float)val;
		 //if (SIdevice[si].adr==4) V2_dushPFI=(float)val;
		 //if (SIdevice[si].adr==5) V3_stol=(float)val;
		 //if (SIdevice[si].adr==2) V4_prach=(float)val;
		}
	 if (SendData (1, SIdevice[si].adr, COM_DTMR, (byte *)"", data, 0)) 
		{ 
		 value=data[0]*10000000+data[1]*1000000+data[2]*100000+data[3]*10000+data[4]*1000+data[5]*100+data[6]*10+data[7];
		 //ULOGW ("[si8][%d] timer: [%x][%x][%x][%x][%x][%x][%x][%x] [%d]",SIdevice[si].adr,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],value);
		}	 
	 Sleep (1000);
	}

 ULOGW ("[si8] close COM6 [srv] port");
 if (hPort3) uart_Close(hPort3); hPort3=NULL;
 ExitThread(0); 
}
//------------------------------------------------------------------------------------------
// function send data to SRVousilitel 
byte SendData (int type, int adr, unsigned func, byte* ndata, byte* data, byte nbytes)
{
 // byte && 0xf + 0x47
 // # 0xd
 byte out[100],in[100],dt[50],cnt=0;
 unsigned crc=0;
 byte count=3;
 DWORD bytes=0;
 bool	res=FALSE;
 if (adr<1) return 0;

 //23 47 48 48 47 53 48 4E 4A 51 4F 48 4F 0D
 //23 47 48 48 47 4F 56 53 49 54 4C 56 4C 0D
 //23 47 48 48 47 55 4D 50 53 50 49 53 4D 0D

 out[0]=0x23;				// # start
 out[1]=((adr&0xf0)>>4);	// adr high
 out[2]=((byte)adr&0xf);	// adr low
 
 out[3]=((0x10&0xf0)>>4);	// запрос high
 out[4]=(0x10&0xf);			// запрос low

 out[5]=((func&0xf000)>>12);// hash
 out[6]=((func&0xf00)>>8);	// hash
 out[7]=((func&0xf0)>>4);	// hash
 out[8]=(func&0xf);			// hash
 //crc=owenCRC16(out+1,8);
 if (func==COM_DCNT) crc=SIcrc[adr-1].DCNT;
 if (func==COM_DSPD) crc=SIcrc[adr-1].DSPD;
 if (func==COM_DTMR) crc=SIcrc[adr-1].DTMR;

/* char char_for_hash; 		//символ дл€ обработки с помощью hash-функции
 for (byte i=1; i<=8; i++)
	{
	 //if (out[i]>=0x47 && out[i]<=0x56) char_for_hash=out[i]-0x47;
	 char_for_hash=out[i]-0x47;
	 char_for_hash*=2;
	 //ULOGW ("[si8] send [%d] %02d",i,char_for_hash);
	 crc = Hash(char_for_hash, 7, crc);
	}*/
 out[9]= ((crc/256)&0xf0)>>4;	// crc high
 out[10]=(crc/256)&0xf;			// crc low
 out[11]=((crc%256)&0xf0)>>4;	// crc high
 out[12]=(crc%256)&0xf;			// crc low
 for (byte i=1; i<=12; i++) out[i]+=0x47;
 out[13]=0xd;
// ULOGW ("[si8] send [14] %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9],out[10],out[11],out[12],out[13]);

 res=uart_BinSend (hPort3,(char *)out,14);
 Sleep (130);
 bytes=uart_GetDataSize(hPort3,IN_DATA);
 if (bytes<10) ULOGW ("[si8] recieve %d bytes",bytes);
 if (bytes>50) return 0;

 res=uart_BinRecv (hPort3,(char *)in,bytes);
 if (!res) 
	{
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[si8] error recieve from SI8 [0x%x]: %ls",pac_GetLastError(), errorBuf);
	}

 if (bytes)
	{
	 //ULOGW ("[si8] recieve [%d] %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",bytes,in[0],in[1],in[2],in[3],in[4],in[5],in[6],in[7],in[8],in[9],in[10],in[11],in[12],in[13],in[14],in[15],in[16],in[17],in[18],in[19],in[20],in[21]);
	 //for (byte i=0; i<bytes; i++) ULOGW ("[si8] in[%d]=%x (%x)",i,in[i],in[i]-0x80);
	 cnt=0;
	 for (i=0; i<bytes; i++) if (in[i]>0x80) in[i]=in[i]-0x80;

 	 if (in[0]==0x23)
	 for (i=1; i<bytes; i++)
		{		 
		 if (in[i]>=0x47) dt[cnt]=(in[i]-0x47);
		 else dt[cnt]=0;
 		 //ULOGW ("[si8] dt[%d]=%x",cnt,dt[cnt]);
		 cnt++;
		}
	 memcpy (data,dt+8,8); data[8]=0;
	 
	 /*if (in[0]==0x23)
	 for (i=1; i<bytes; i=i+2)
		{		 
		 dt[cnt]=(in[i]-0x47)*16+(in[i+1]-0x47);
 		 ULOGW ("[si8] dt[%d]=%x",cnt,dt[cnt]);
		 cnt++;
		}*/
	 crc=0;
	 //for (i=1; i<=bytes-1; i++)	crc = Hash(in[i], 7, crc);
 	 //ULOGW ("[si8] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,iRecv[iRecv[2]+3],iRecv[iRecv[2]+4]);	  
	 return 1;
	}
 if (!res) 
	{
	 pac_GetErrorMessage(pac_GetLastError(), errorBuf);
	 ULOGW ("[si8] error recieve from SI8. error [0x%x]: %ls",pac_GetLastError(), errorBuf);
	 if (hPort3) uart_Close(hPort3);
	 hPort3 = uart_Open("COM2:,9600,N,8,1");
	 count--;
	}

 return 0;
}
//---------------------------------------------------------------------------------------------------- 
unsigned short owenCRC16(unsigned char* packet, size_t length)
{
	size_t i, j;
	unsigned short crc;
	crc = 0;
	for (i = 0; i < length; ++i)
	{
		unsigned char b = packet[i];
		for (j = 0; j < 8; ++j, b <<= 1)
		{
			if ((b ^ (crc >> 8)) & 0x80)
			{
				crc <<= 1;
				crc ^= 0x8F57;
			}
			else
				crc <<= 1;
		}
	}
	return crc;
}
//---------------------------------------------------------------------------------------------------- 
