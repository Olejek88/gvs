// SI8 
struct SIdevices
	{
	 UINT	adr;
	 INT	DCNT;
	 UINT	DSPD;
	 LONG	DTMR;
    };
SIdevices SIdevice[] =
	{{ 4, 0, 0, 0},
	{ 5, 0, 0, 0},
	{ 2, 0, 0, 0},
	{ 3, 0, 0, 0}};

#define		COM_DCNT	0xC173
#define		COM_DSPD	0x8FC2
#define		COM_DTMR	0xE69C

struct SIcomCRC
	{
	 UINT	DCNT;
	 UINT	DSPD;
	 UINT	DTMR;
	};

SIcomCRC	SIcrc[] =
	{{	0xA818, 0xD5F5, 0x92C6},
	{ 0xE71A, 0x9AF7, 0xDDC4},
	{ 0xDDE4, 0xA009, 0xE73A},
	{ 0x791E, 0x04F3, 0x43C0},
	{ 0x43E0, 0x3E0D, 0x793E},
	{ 0x0CE2, 0x710F, 0x363C},
	{ 0x361C, 0x4BF1, 0x0CC2},
	{ 0xCA41, 0xB7AC, 0xF09F}};
// параметры

//--------------------------------------------------------------------------------------------------------
extern float	V1_dushCGTS;
extern float	V2_dushPFI;
extern float	V3_stol;
extern float	V4_prach;

