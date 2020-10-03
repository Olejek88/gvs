extern	byte	WorkEnable;		// work flag
extern	short	currentregim;	// 0 - test, 1-3 scene selection

// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech;			// �������� ���� �� ����������
extern	float	P_par_in_heater;		// �������� ���� �� ����� � �������������
extern	float	P_water_in_heater;	// �������� ���� �� ����� � �������������
extern	float	P_water_out_heater;	// �������� ���� �� ������ �� ��������������
extern	float	P_water_gvs_accum;	// �������� ���� �� �������� ��� �� �����-�������������
extern	float	S_water_reg_temp;		// ��������� ������� ���������� ����������� ����
extern	float	L_water_bak_accum;	// ������� ���� � ����-������������
extern	float	L_cond_bak_nakop;		// ������� ���������� � ����-����������
extern	float	V_water_bak_accum;	// ������� ���� � ����-������������
extern	float	S_KT;					// ��������� �������

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater;		// ����������� ���� �� ����� � �������������
extern	float	T_water_in_heater;	// ����������� ���� �� ����� � �������������
extern	float	T_water_out_heater;	// ����������� ���� �� ������ �� ��������������
extern	float	T_water_out_gvs;		// ����������� ��� �� ������������
extern	float	T_water_podp_hvs;		// ����������� ����������� ���� ���
extern	float	T_water_bak_accum;	// ����������� ���� � ����-������������
extern	float	T_cond_bak_nakop;		// ����������� ���������� � ����-����������
extern	float	P_gvs_in_bak_nak;		// �������� ���� ���������� ��� ����� �����-�����-���

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened;		// ������ �� ������ ������ ��������� ��� ������
extern	byte	podgvs_zatvor_napor_closed;	// ������ �� ������ ������ ��������� ��� ������
extern	byte	podgvs_rele_nasos_status;		// ���� �������� �� ����� ������ ��������� ���
extern	byte	podgvs_regim_nasos_system;	// ����� ��������� ��� � ������ "���������"
extern	byte	podgvs_regim_nasos_hand;		// ����� ��������� ��� � ������ "������"
extern	byte	podgvs_kont_nasos_vkl;		// ��������� ������ ��������� ��� �������

extern	byte	podpdear_zatv_nasos_opened;		// ������ �� ������ ������ �������� ���������� ������
extern	byte	podpdear_zatv_nasos_closed;	// ������ �� ������ ������ �������� ���������� ������
extern	byte	podpdear_rele_nasos_closed;	// ���� �������� �� ����� ������ �������� ����������
extern	byte	podpdear_regim_nasos_system;	// ����� �������� ���������� � ������ "���������"
extern	byte	podpdear_regim_nasos_hand;	// ����� �������� ���������� � ������ "������"
extern	byte	podpdear_kont_nasos_vkl;		// ��������� ������ �������� ���������� �������

extern	byte	circgvs_zatv_nasos_opened;		// ������ �� ������ ������ ���������� ��� ������
extern	byte	circgvs_zatv_nasos_closed;	// ������ �� ������ ������ ���������� ��� ������
extern	byte	circgvs_rele_nasos_status;	// ���� �������� �� ����� ������ ���������� ���
extern	byte	circgvs_regim_nasos_system;	// ����� ���������� ��� � ������ "���������"
extern	byte	circgvs_regim_nasos_hand;		// ����� ���������� ��� � ������ "������"
extern	byte	circgvs_kont_nasos_gvs;		// ��������� ������ ���������� ��� �������

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system;		// ������ �� �������� ��� � ������ "���������"
extern	byte	podgvs_zatv_nasos_opened;		// ������ �� �������� ��� ������
extern	byte	podgvs_zatv_nasos_closed;		// ������ �� �������� ��� ������

extern	byte	podgvs_regim_obrat_system;		// ������ �� ������� ��������� ��� � ������ "���������"
extern	byte	podgvs_zatv_obrat_opened;		// ������ �� ������� ��������� ��� ������
extern	byte	podgvs_zatv_obrat_closed;		// ������ �� ������� ��������� ��� ������

extern	byte	circgvs_regim_zatv_system;	// ������ �� ���������� ��� � ������ "���������"
extern	byte	circgvs_zatv_opened;			// ������ �� ���������� ��� ������
extern	byte	circgvs_zatv_closed;			// ������ �� ���������� ��� ������

extern	byte	circgvs_regim_obrat_system;	// ������ �� ������� ���������� ��� � ������ "���������"
extern	byte	circgvs_zatv_obrat_opened;	// ������ �� ������� ���������� ��� ������
extern	byte	circgvs_zatv_obrat_closed;	// ������ �� ������� ���������� ��� ������

extern	byte	bypass_regim_bakaccum_system;	// ������ �� ������� ����-�������-�� � ������ "���������"
extern	byte	bypass_zatv_bakaccum_opened;	// ������ �� ������� ����-������������ ������
extern	byte	bypass_zatv_bakaccum_closed;	// ������ �� ������� ����-������������ ������

extern	byte	regulator_klapan_tvoda_system;// ������ ���������� ����������� ���� � ���. "���������"
extern	byte	regulator_klapan_tvoda_opened;	// ������ ���������� ����������� ���� ������
extern	byte	regulator_klapan_tvoda_closed;// ������ ���������� ����������� ���� ������

extern	byte	podphvs_zatv_regim_system;	// ������ �������� ��� � ������ "���������"
extern	byte	podphvs_zatv_hvs_opened;		// ������ �������� ��� ������
extern	byte	podphvs_zatv_hvs_closed;		// ������ �������� ��� ������

extern	byte	podpaccum_zatv_regim_system;	// ������ �� �������� � ���-���������� � ������ "���������"
extern	byte	podpaccum_zatv_accum_opened;	// ������ �� �������� � ���-���������� ������
extern	byte	podpaccum_zatv_accum_closed;	// ������ �� �������� � ���-���������� ������

extern	byte	podpdear_zatv_bypass_system;	// ������ �� ������� �������� ���������� � ������ "���������"
extern	byte	podpdear_zatv_bypass_opened;		// ������ �� ������� �������� ���������� ������
extern	byte	podpdear_zatv_bypass_closed;	// ������ �� ������� �������� ���������� ������

extern	byte	podpar_zatv_regim_system;		// ������ �� ������ ���� � ������ "���������"
extern	byte	podpar_zatv_obrat_opened;		// ������ �� ������ ���� ������
extern	byte	podpar_zatv_obrat_closed;		// ������ �� ������ ���� ������

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open;		// ������� ������ �� ������ ������ ��������� ���       (��2)
extern	byte	podgvs_zatv_nasos_close;		// ������� ������ �� ������ ������ ��������� ���       (��2)
extern	byte	podgvs_kont_nasos_on;			// �������� ��������� ������ ��������� ���                   (�2)
extern	byte	podgvs_kont_nasos_off;		// ��������� ��������� ������ ��������� ���                 (�2)

extern	byte	circgvs_zatv_nasos_open;		// ������� ������ �� ������ ������ ���������� ���     (��3)
extern	byte	circgvs_zatv_nasos_close;		// ������� ������ �� ������ ������ ���������� ���     (��3)
extern	byte	circgvs_kont_nasos_on;		// �������� ��������� ������ ���������� ���                 (�3)
extern	byte	circgvs_kont_nasos_off;		// ��������� ��������� ������ ���������� ���               (�3)

extern	byte	podpdear_zatv_nasos_open;		// ������� ������ �� ������ ������ �������� �����-� (��1)
extern	byte	podpdear_zatv_nasos_close;	// ������� ������ �� ������ ������ �������� �����-�� (��1)
extern	byte	podpdear_kont_nasos_on;		// �������� ��������� ������ �������� ����������      (�1)
extern	byte	podpdear_kont_nasos_off;		// ��������� ��������� ������ �������� ����������    (�1)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open;			// ������� ������ �� �������� ���                                      (��4)
extern	byte	podgvs_zatv_gvs_close;		// ������� ������ �� �������� ���                                       (��4)
extern	byte	podgvs_zatv_obr_open;			// ������� ������ �� ������� ��������� ���                    (��5)
extern	byte	podgvs_zatv_obr_close;			// ������� ������ �� ������� ��������� ���                     (��5)

extern	byte	circgvs_zatv_gvs_open;		// ������� ������ �� ���������� ���        (��6)
extern	byte	circgvs_zatv_gvs_close;		// ������� ������ �� ���������� ���        (��6)
extern	byte	circgvs_zatv_obr_open;		// ������� ������ �� ������� ���������� ���(��7)
extern	byte	circgvs_zatv_obr_close;		// ������� ������ �� ������� ���������� ���(��7)

extern	byte	podphvs_zatv_hvs_open;		// ������� ������ �������� ���         (��8)
extern	byte	podphvs_zatv_hvs_close;		// ������� ������ �������� ���         (��8)

// [5][MDO1.6] i-87061W
extern	byte	podpaccum_zatv_bak_open;	// ������� ������ �� �������� � ���-����������           (��9)
extern	byte	podpaccum_zatv_bak_close;	// ������� ������ �� �������� � ���-����������           (��9)
extern	byte	podpdear_zatv_bypass_open;	// ������� ������ �� ������� �������� ����������     (��10)
extern	byte	podpdear_zatv_bypass_close;	// ������� ������ �� ������� �������� ����������     (��10)
extern	byte	bakaccum_zatv_bypass_open;	// ������� ������ �� ������� ����-������������        (��11)
extern	byte	bakaccum_zatv_bypass_close;	// ������� ������ �� ������� ����-������������        (��11)
extern	byte	podpar_zatv_par_open;		// ������� ������ �� ������ ����                                      (��12)
extern	byte	podpar_zatv_par_close;		// ������� ������ �� ������ ����                                      (��12)

// [6][MDO1.7] i-87061W
extern	byte	regtemp_klap_voda_open;		// ������� ������ ���������� ����������� ����
extern	byte	regtemp_klap_voda_close;	// ������� ������ ���������� ����������� ����


extern float	V1_dushCGTS;
extern float	V2_dushPFI;
extern float	V3_stol;
extern float	V4_prach;

extern float	P_par_tech;				// �������� ���� �� ����������
extern float	P_par_in_heater;		// �������� ���� �� ����� � �������������
extern float	P_water_in_heater;		// �������� ���� �� ����� � �������������
extern float	P_water_out_heater;		// �������� ���� �� ������ �� ��������������
extern float	P_water_gvs_accum;		// �������� ���� �� �������� ��� �� �����-�������������
//extern float	S_water_reg_temp;		// ��������� ������� ���������� ����������� ����
extern float	L_water_bak_accum;		// ������� ���� � ����-������������
//extern float	L_cond_bak_nakop;		// ������� ���������� � ����-����������

// [1][MAI1.2] i-87017RW
extern float	T_par_in_heater;		// ����������� ���� �� ����� � �������������
extern float	T_water_in_heater;		// ����������� ���� �� ����� � �������������
extern float	T_water_out_heater;		// ����������� ���� �� ������ �� ��������������
extern float	T_water_out_gvs;		// ����������� ��� �� ������������
extern float	T_water_podp_hvs;		// ����������� ����������� ���� ���
extern float	T_water_bak_accum;		// ����������� ���� � ����-������������
extern float	T_water_prach;			// ����������� ���� � ���������
extern float	T_water_stolv;			// ����������� ���� � �������� 