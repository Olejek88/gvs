#define ReadHoldingRegisters	0x3
#define ReadInputRegisters		0x4
#define PresetSingleRegister  	0x5
#define PresetMultiRegister  	0x6

// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech;				// �������� ���� �� ����������
extern	float	P_par_in_heater;		// �������� ���� �� ����� � �������������
extern	float	P_water_in_heater;		// �������� ���� �� ����� � �������������
extern	float	P_water_out_heater;		// �������� ���� �� ������ �� ��������������
extern	float	P_water_gvs_accum;		// �������� ���� �� �������� ��� �� �����-�������������
extern	float	L_water_bak_accum;		// ������� ���� � ����-������������
extern	float	V_water_bak_accum;		// ����� ���� � ����-������������
extern	float	P_water_potreb;			// �������� ���� �� ������ �� ��������������

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater;		// ����������� ���� �� ����� � �������������
extern	float	T_water_in_heater;		// ����������� ���� �� ����� � �������������
extern	float	T_water_out_heater;		// ����������� ���� �� ������ �� ��������������
extern	float	T_water_out_gvs;		// ����������� ��� �� ������������
extern	float	T_water_podp_hvs;		// ����������� ����������� ���� ���
extern	float	T_water_bak_accum;		// ����������� ���� � ����-������������
extern	float	T_water_prach;			// ����������� ���� � ���������
extern	float	T_water_stolv;			// ����������� ���� � ��������

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened;	// ������ �� ������ ������ ��������� ��� ������
extern	byte	podgvs_zatvor_napor_closed;	// ������ �� ������ ������ ��������� ��� ������
extern	byte	podgvs_rele_nasos_status;	// ���� �������� �� ����� ������ ��������� ���
extern	byte	podgvs_regim_nasos_system;	// ����� ��������� ��� � ������ "���������"
extern	byte	podgvs_regim_nasos_hand;	// ����� ��������� ��� � ������ "������"
extern	byte	podgvs_kont_nasos_vkl;		// ��������� ������ ��������� ��� �������

extern	byte	gvs_zatv_nasos_opened;		// ������ �� ������ ������ ��� ������
extern	byte	gvs_zatv_nasos_closed;		// ������ �� ������ ������ ��� ������
extern	byte	circgvs_rele_nasos_status;	// ���� �������� �� ����� ������ ���������� ���
extern	byte	circgvs_regim_nasos_system;	// ����� ���������� ��� � ������ "���������"
extern	byte	circgvs_regim_nasos_hand;	// ����� ���������� ��� � ������ "������"
extern	byte	circgvs_kont_nasos_gvs;		// ��������� ������ ���������� ��� �������

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system;		// ������ �� �������� ��� � ������ "���������"
extern	byte	podgvs_zatv_nasos_opened;		// ������ �� �������� ��� ������
extern	byte	podgvs_zatv_nasos_closed;		// ������ �� �������� ��� ������

extern	byte	podgvs_regim_obrat_system;		// ������ �� ������� ��������� ��� � ������ "���������"
extern	byte	podgvs_zatv_obrat_opened;		// ������ �� ������� ��������� ��� ������
extern	byte	podgvs_zatv_obrat_closed;		// ������ �� ������� ��������� ��� ������

extern	byte	circgvs_regim_zatv_system;		// ������ �� ���������� ��� � ������ "���������"
extern	byte	circgvs_zatv_opened;			// ������ �� ���������� ��� ������
extern	byte	circgvs_zatv_closed;			// ������ �� ���������� ��� ������

extern	byte	circgvs_regim_obrat_system;		// ������ �� ������� ���������� ��� � ������ "���������"
extern	byte	circgvs_zatv_obrat_opened;		// ������ �� ������� ���������� ��� ������
extern	byte	circgvs_zatv_obrat_closed;		// ������ �� ������� ���������� ��� ������

extern	byte	regulator_klapan_tvoda_system;	// ������ ���������� ����������� ���� � ���. "���������"
extern	byte	regulator_klapan_tvoda_opened;	// ������ ���������� ����������� ���� ������
extern	byte	regulator_klapan_tvoda_closed;	// ������ ���������� ����������� ���� ������

extern	byte	podphvs_zatv_regim_system;		// ������ �������� ��� � ������ "���������"
extern	byte	podphvs_zatv_hvs_opened;		// ������ �������� ��� ������
extern	byte	podphvs_zatv_hvs_closed;		// ������ �������� ��� ������

extern	byte	podpar_zatv_regim_system;		// ������ �� ������ ���� � ������ "���������"
extern	byte	podpar_zatv_obrat_opened;		// ������ �� ������ ���� ������
extern	byte	podpar_zatv_obrat_closed;		// ������ �� ������ ���� ������

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open;			// ������� ������ �� ������ ������ ��������� ���       (��2)
extern	byte	podgvs_zatv_nasos_close;		// ������� ������ �� ������ ������ ��������� ���       (��2)
extern	byte	podgvs_kont_nasos_on;			// �������� ��������� ������ ��������� ���                   (�2)
extern	byte	podgvs_kont_nasos_off;			// ��������� ��������� ������ ��������� ���                 (�2)

extern	byte	circgvs_zatv_nasos_open;	// ������� ������ �� ������ ������ ���������� ���     (��3)
extern	byte	circgvs_zatv_nasos_close;	// ������� ������ �� ������ ������ ���������� ���     (��3)
extern	byte	circgvs_kont_nasos_on;		// �������� ��������� ������ ���������� ���                 (�3)
extern	byte	circgvs_kont_nasos_off;		// ��������� ��������� ������ ���������� ���               (�3)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open;		// ������� ������ �� �������� ���                                      (��4)
extern	byte	podgvs_zatv_gvs_close;		// ������� ������ �� �������� ���                                       (��4)
extern	byte	podgvs_zatv_obr_open;		// ������� ������ �� ������� ��������� ���                    (��5)
extern	byte	podgvs_zatv_obr_close;		// ������� ������ �� ������� ��������� ���                     (��5)

extern	byte	circgvs_zatv_gvs_open;		// ������� ������ �� ���������� ���        (��6)
extern	byte	circgvs_zatv_gvs_close;		// ������� ������ �� ���������� ���        (��6)
extern	byte	circgvs_zatv_obr_open;		// ������� ������ �� ������� ���������� ���(��7)
extern	byte	circgvs_zatv_obr_close;		// ������� ������ �� ������� ���������� ���(��7)

extern	byte	podphvs_zatv_hvs_open;		// ������� ������ �������� ���         (��8)
extern	byte	podphvs_zatv_hvs_close;		// ������� ������ �������� ���         (��8)
extern	byte	podpar_zatv_par_open;		// ������� ������ �� ������ ����                                      (��12)
extern	byte	podpar_zatv_par_close;		// ������� ������ �� ������ ����                                      (��12)

// [6][MDO1.6] i-87061W
extern	byte	regtemp_klap_voda_open;		// ������� ������ ���������� ����������� ����
extern	byte	regtemp_klap_voda_close;		// ������� ������ ���������� ����������� ����

extern	byte	bak_level_critical_low;		// ������� � ���� ������ ����������� [22]
extern	byte	bak_level_warning_low;		// ������� � ���� ������ ����������������� [23]
extern	byte	bak_level_work_low;			// ������� � ���� ������ ������� [24]
extern	byte	bak_level_critical_high;	// ������� � ���� ������� ����������� [25]
extern	byte	bak_level_warning_high;		// ������� � ���� ������� ����������������� [26]
extern	byte	bak_level_work_high;		// ������� � ���� ������� ������� [27]
//206
extern	byte	voda_temp_critical_low;		// ����������� ���� ������ ����������� [28]
extern	byte	voda_temp_warning_low;		// ����������� ���� ������ ����������������� [29]
extern	byte	voda_temp_work_low;			// ����������� ���� ������ ������� [30]
extern	byte	voda_temp_warning_high;		// ����������� ���� ������� ����������������� [31]
extern	byte	voda_temp_critical_high;	// ����������� ���� ������� ����������� [32]
extern	byte	voda_temp_work_high;		// ����������� ���� ������� ������� [33]

extern	byte	gvs_temp_potr_low;			// ����������� ���� �� ������������ ������ [34]
extern	byte	gvs_temp_potr_high;			// ����������� ���� �� ������������ ������� [35]
extern	byte	voda_potr_high;				// �������� ���� �� ������������ ������� [36]
extern	byte	voda_potr_stop;				// ��� ������� - ���������� �2 [37]
extern	uint	timer_Ppotr_high;			// ������ �������� �������� ���� �� ������������ [38]

// [0][MAI1.1] i-87017RW
extern	float	aP_par_tech;			// �������� ���� �� ����������
extern	float	aP_par_in_heater;		// �������� ���� �� ����� � �������������
extern	float	aP_water_in_heater;		// �������� ���� �� ����� � �������������
extern	float	aP_water_out_heater;	// �������� ���� �� ������ �� ��������������
extern	float	aP_water_gvs_accum;		// �������� ���� �� �������� ��� �� �����-�������������
extern	float	aL_water_bak_accum;		// ������� ���� � ����-������������
extern	float	aP_water_potreb;		// �������� ���� �� ������������

// [1][MAI1.2] i-87017RW
extern	float	aT_par_in_heater;		// ����������� ���� �� ����� � �������������
extern	float	aT_water_in_heater;		// ����������� ���� �� ����� � �������������
extern	float	aT_water_out_heater;	// ����������� ���� �� ������ �� ��������������
extern	float	aT_water_out_gvs;		// ����������� ��� �� ������������
extern	float	aT_water_podp_hvs;		// ����������� ����������� ���� ���
extern	float	aT_water_bak_accum;		// ����������� ���� � ����-������������
extern	float	aT_water_prach;			// ����������� ���� � ���������
extern	float	aT_water_stolv;			// ����������� ���� � ��������

//-------------------------------------------------------------------------
extern float	V1_dushCGTS;
extern float	V2_dushPFI;
extern float	V3_stol;
extern float	V4_prach;

// test variables
extern	byte	StartTest1;		// 40
extern	byte	StartTest2;		// 41
extern	byte	StartTest3;		// 42
extern	byte	StartTest4;		// 43
extern	byte	StartTest5;		// 44

extern	byte	EndTest1;		// 253
extern	byte	LevelOK;		// 254
extern	byte	WaterOK;		// 255
extern	byte	PumpStop;		// 256
extern	byte	EndTest2;		// 257
extern	byte	StartPar3;		// 258
extern	byte	EndTest3;		// 259
extern	byte	EndTest4;		// 260
extern	byte	EndTest5;		// 261
extern	byte	PumpStop2;		// 262
extern	byte	TestRegim;		// 263
extern	byte	WorkEnable;		// 264
extern	byte	FinishWork;		// 265
extern	byte	WorkEnable2;	// 266
extern	byte	StatusFinish;	// 267
extern	byte	FinishWork2;	// 268
extern	byte	NoHVS;			// 269
extern	byte	Statusfill;		// 270
extern	byte	StatusM2;		// 271