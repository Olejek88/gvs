// constants							//Experemental       LastCorrerct
#define		Level_Alarm_Up		13.2	//12				// 14
#define		Level_Warn_Up		13	//11				// 13.5
#define		Level_Work_Up		12.6	//10				// 13

#define		Level_Work_Down		9.5		//8					// 7
#define		Level_Warn_Down		7		//6					// 4
#define		Level_Alarm_Down	3		//5					// 3

#define		Temp_Alarm_Up		90		//50				// 90
#define		Temp_Warn_Up		80		//45				// 80
#define		Temp_Work_Up		78		//40				// 75
#define		Temp_Work_Down		70		//30				// 68
#define		Temp_Warn_Down		40		//20				// 40
#define		Temp_Alarm_Down		15		//15				// 15

#define		Temp_Test_Need		45

#define		P_Alarm_Potr		3.6
#define		P_Work_Potr			3.5

// global variables
char	mainlog[100];	// main log file

byte	WorkEnable=1;	// work flag
byte	WorkEnable2=1;	// work flag
byte	TestRegim=0;	// �������� �����
//byte	FinishWork2=0;	// exit by errors
byte	StatusFinish=0;	// exit by errors

// test variables
byte	StartTest1=0;	// 40
byte	StartTest2=0;	// 41
byte	StartTest3=0;	// 42
byte	StartTest4=0;	// 43
byte	StartTest5=0;	// 44
byte	FinishWork=0;	// 45
byte	FinishWork2=0;	// 46
byte	FinishWork3=0;	// 47

byte	EndTest1=0;		// 253
byte	LevelOK=0;		// 254
byte	WaterOK=0;		// 255
byte	PumpStop=0;		// 256
byte	EndTest2=0;		// 257
byte	StartPar3=0;	// 258
byte	EndTest3=0;		// 259
byte	EndTest4=0;		// 260
byte	EndTest5=0;		// 261
byte	PumpStop2=0;	// 262

uint	currentregim;			// 0 - test

uint	timer_Ppotr_high=0;	// ������ �������� �������� ���� �� ������������
uint	timer_open_KT=0;	// ������ �������� �������

extern	uint	PANEL_TYPE;		// regim from panel
extern	byte	PANEL_STOP;

HANDLE	hPort;			// internal port handler
TCHAR	errorBuf[64];	// buffer for error messages

HANDLE	hThrdIO;		// I/O thread handle
DWORD	dwThrdIDIO;		// I/O thread ID value
HANDLE	hReadEventsIO;	// I/O thread 

HANDLE	hThrdSI8;		// SI8 thread handle
DWORD	dwThrdIDSI8;	// SI8 thread ID value
HANDLE	hReadEventsSI8;	// SI8 thread 

HANDLE	hThrdMT;		// Panel thread handle
DWORD	dwThrdIDMT;		// Panel thread ID value
HANDLE	hReadEventsMT;	// Panel thread 

HANDLE	hThrdAlg;		// Algorithm thread handle
DWORD	dwThrdIDAlg;	// Algorithm thread ID value
HANDLE	hReadEventsAlg; // Algorithm thread 

HANDLE	hThrdService;		// Service handle
DWORD	dwThrdIDService;	// Service thread ID value
HANDLE	hReadEventsService; // Service thread 

// IO variables
// [0][MAI1.1] i-87017RW
float	P_par_tech=0;			// �������� ���� �� ����������
float	P_par_in_heater=0;		// �������� ���� �� ����� � �������������
float	P_water_in_heater=0;	// �������� ���� �� ����� � �������������
float	P_water_out_heater=0;	// �������� ���� �� ������ �� ��������������
float	P_water_gvs_accum=0;	// �������� ���� �� �������� ��� �� �����-�������������
float	L_water_bak_accum=0;	// ������� ���� � ����-������������
float	V_water_bak_accum=0;	// ����� ���� � ����-������������
float	P_water_potreb=0;		// �������� ���� �� ������ �� ��������������
float	S_KT=0;					// ��������� �������

// [1][MAI1.2] i-87017RW
float	T_par_in_heater=0;		// ����������� ���� �� ����� � �������������
float	T_water_in_heater=0;	// ����������� ���� �� ����� � �������������
float	T_water_out_heater=0;	// ����������� ���� �� ������ �� ��������������
float	T_water_out_gvs=0;		// ����������� ��� �� ������������
float	T_water_podp_hvs=0;		// ����������� ����������� ���� ���
float	T_water_bak_accum=0;	// ����������� ���� � ����-������������

float	T_water_prach=0;		// ����������� ���� � ���������
float	T_water_stolv=0;		// ����������� ���� � ��������

// [2][MDI1.3] i-87040W
byte	podgvs_zatvor_napor_closed=0;	// ������ �� ������ ������ ��������� ��� ������	(��1)	50
byte	podgvs_zatvor_napor_opened=0;	// ������ �� ������ ������ ��������� ��� ������	(��1)	51
byte	podgvs_rele_nasos_status=0;		// ���� �������� �� ����� ������ ��������� ���	(�1)	52
byte	podgvs_regim_nasos_hand=0;		// ����� ��������� ��� � ������ "���������"		(�1)	53
byte	podgvs_regim_nasos_system=0;	// ����� ��������� ��� � ������ "������"		(�1)	54
byte	podgvs_kont_nasos_vkl=0;		// ��������� ������ ��������� ��� �������		(�1)	55

byte	gvs_zatv_nasos_opened=0;		// ������ �� ������ ������ ��� ������			(��2)	56
byte	gvs_zatv_nasos_closed=0;		// ������ �� ������ ������ ��� ������			(��2)	57
byte	circgvs_rele_nasos_status=0;	// ���� �������� �� ����� ������ ���������� ���	(�2)	58
byte	circgvs_regim_nasos_system=0;	// ����� ���������� ��� � ������ "���������"	(�2)	59
byte	circgvs_regim_nasos_hand=0;		// ����� ���������� ��� � ������ "������"		(�2)	60
byte	circgvs_kont_nasos_gvs=0;		// ��������� ������ ���������� ��� �������		(�2)	61

byte	critical_temp_kond=0;			// ����������� ����������� ����������

// [3][MDI1.4] i-87040W
byte	podgvs_regim_zatv_system=0;		// ������ �� �������� ��� � ������ "���������"	(��4)	62
byte	podgvs_zatv_nasos_closed=0;		// ������ �� �������� ��� ������				(��4)	63		// ch
byte	podgvs_zatv_nasos_opened=0;		// ������ �� �������� ��� ������				(��4)	64

byte	podgvs_regim_obrat_system=0;	// ������ �� ������� ��������� ��� � ������ "���������"(��5)65
byte	podgvs_zatv_obrat_closed=0;		// ������ �� ������� ��������� ��� ������			(��5)	66
byte	podgvs_zatv_obrat_opened=0;		// ������ �� ������� ��������� ��� ������			(��5)	67

byte	circgvs_regim_zatv_system=0;	// ������ �� ���������� ��� � ������ "���������"	(��6)	68
byte	circgvs_zatv_closed=0;			// ������ �� ���������� ��� ������					(��6)	69 // ch
byte	circgvs_zatv_opened=0;			// ������ �� ���������� ��� ������					(��6)	70

byte	circgvs_regim_obrat_system=0;	// ������ �� ������� ���������� ��� � ������ "���������"	71
byte	circgvs_zatv_obrat_opened=0;	// ������ �� ������� ���������� ��� ������			(��7)	72
byte	circgvs_zatv_obrat_closed=0;	// ������ �� ������� ���������� ��� ������			(��7)	73

byte	regulator_klapan_tvoda_system=0;// ������ ���������� ����������� ���� � ���. "���������"	74
byte	regulator_klapan_tvoda_closed=0;// ������ ���������� ����������� ���� ������				75
byte	regulator_klapan_tvoda_opened=0;// ������ ���������� ����������� ���� ������				76

byte	podphvs_zatv_regim_system=0;	// ������ �������� ��� � ������ "���������"			(��3)	77
byte	podphvs_zatv_hvs_opened=0;		// ������ �������� ��� ������						(��3)	78
byte	podphvs_zatv_hvs_closed=0;		// ������ �������� ��� ������						(��3)	79

byte	podpar_zatv_regim_system=0;		// ������ �� ������ ���� � ������ "���������"		(��8)	80
byte	podpar_zatv_obrat_opened=0;		// ������ �� ������ ���� ������						(��8)	81
byte	podpar_zatv_obrat_closed=0;		// ������ �� ������ ���� ������						(��8)	82

// [4][MDO1.5] i-87040W
byte	podgvs_zatv_nasos_open=0;		// ������� ������ �� ������ ������ ��������� ���    (��1)	0
byte	podgvs_zatv_nasos_close=0;		// ������� ������ �� ������ ������ ��������� ���    (��1)	1
byte	podgvs_kont_nasos_on=0;			// �������� ��������� ������ ��������� ���          (�1)	2
byte	podgvs_kont_nasos_off=0;		// ��������� ��������� ������ ��������� ���         (�1)	3

byte	circgvs_zatv_nasos_open=0;		// ������� ������ �� ������ ������ ���������� ���     (��2)			4
byte	circgvs_zatv_nasos_close=0;		// ������� ������ �� ������ ������ ���������� ���     (��2)			5
byte	circgvs_kont_nasos_on=0;		// �������� ��������� ������ ���������� ���                 (�2)	6
byte	circgvs_kont_nasos_off=0;		// ��������� ��������� ������ ���������� ���               (�2)		7

// [5][MDO1.5] i-87061W
byte	podgvs_zatv_gvs_open=0;			// ������� ������ �� �������� ���                    (��4)			8
byte	podgvs_zatv_gvs_close=0;		// ������� ������ �� �������� ���                    (��4)			9
byte	podgvs_zatv_obr_open=0;			// ������� ������ �� ������� ��������� ���           (��5)			10
byte	podgvs_zatv_obr_close=0;		// ������� ������ �� ������� ��������� ���			 (��5)			11

byte	circgvs_zatv_gvs_open=0;		// ������� ������ �� ���������� ���        (��6)					12
byte	circgvs_zatv_gvs_close=0;		// ������� ������ �� ���������� ���        (��6)					13
byte	circgvs_zatv_obr_open=0;		// ������� ������ ���������� � ��� (��7)							14
byte	circgvs_zatv_obr_close=0;		// ������� ������ ���������� � ��� (��7)							15

byte	podphvs_zatv_hvs_open=0;		// ������� ������ �������� ���         (��3)						16
byte	podphvs_zatv_hvs_close=0;		// ������� ������ �������� ���         (��3)						17
//
//
byte	podpar_zatv_par_open=0;			// ������� ������ �� ������ ����       (��8)						18
byte	podpar_zatv_par_close=0;		// ������� ������ �� ������ ����       (��8)						19

// [6][MDO1.6] i-87061W
byte	regtemp_klap_voda_open=0;		// ������� ������ ���������� ����������� ����						20
byte	regtemp_klap_voda_close=0;		// ������� ������ ���������� ����������� ����						21

// [6][MDO1.7] i-87061W
// [7][MDO1.8] i-87065W

byte	bak_level_critical_low=0;		// ������� � ���� ������ �����������
byte	bak_level_warning_low=0;		// ������� � ���� ������ �����������������
byte	bak_level_work_low=0;			// ������� � ���� ������ �������
byte	bak_level_critical_high=0;		// ������� � ���� ������� �����������
byte	bak_level_warning_high=0;		// ������� � ���� ������� �����������������
byte	bak_level_work_high=0;			// ������� � ���� ������� �������

byte	voda_temp_critical_low=0;		// ����������� ���� ������ �����������
byte	voda_temp_warning_low=0;		// ����������� ���� ������ �����������������
byte	voda_temp_work_low=0;			// ����������� ���� ������ �������
byte	voda_temp_critical_high=0;		// ����������� ���� ������� �����������
byte	voda_temp_warning_high=0;		// ����������� ���� ������� �����������������
byte	voda_temp_work_high=0;			// ����������� ���� ������� �������

byte	gvs_temp_potr_low=0;			// ����������� ���� �� ������������ ������
byte	gvs_temp_potr_high=0;			// ����������� ���� �� ������������ �������
byte	voda_potr_high=0;				// �������� ���� �� ������������ �������
byte	voda_potr_stop=0;				// ��� ������� - ���������� �2

DWORD do_value4_prev=0xffff,do_value5_prev=0xffff,do_value6_prev=0xffff,do_value7_prev=0xffff;
DWORD di_value2_prev=0xff,di_value3_prev=0xff;

// IO variables
// [0][MAI1.1] i-87017RW
float	aP_par_tech=0;			// �������� ���� �� ����������
float	aP_par_in_heater=0;		// �������� ���� �� ����� � �������������
float	aP_water_in_heater=0;	// �������� ���� �� ����� � �������������
float	aP_water_out_heater=0;	// �������� ���� �� ������ �� ��������������
float	aP_water_gvs_accum=0;	// �������� ���� �� �������� ��� �� �����-�������������
float	aL_water_bak_accum=0;	// ������� ���� � ����-������������
float	aP_water_potreb=0;		// �������� ���� �� ������������

// [1][MAI1.2] i-87017RW
float	aT_par_in_heater=0;		// ����������� ���� �� ����� � �������������
float	aT_water_in_heater=0;	// ����������� ���� �� ����� � �������������
float	aT_water_out_heater=0;	// ����������� ���� �� ������ �� ��������������
float	aT_water_out_gvs=0;		// ����������� ��� �� ������������
float	aT_water_podp_hvs=0;	// ����������� ����������� ���� ���
float	aT_water_bak_accum=0;	// ����������� ���� � ����-������������
float	aT_water_prach=0;		// ����������� ���� � ���������
float	aT_water_stolv=0;		// ����������� ���� � ��������

// V
float	V1_dushCGTS=0;
float	V2_dushPFI=0;
float	V3_stol=0;
float	V4_prach=0;

byte	FinishWork4=0;

BOOL regulator_klapan_tvoda_NOT_closed=false;
BOOL podpar_zatv_obrat_NOT_closed=false;
BOOL podphvs_zatv_hvs_NOT_closed=false;
