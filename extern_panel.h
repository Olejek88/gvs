// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech=0;			// �������� ��� �� �孮�����
extern	float	P_par_in_heater=0;		// �������� ��� �� �室� � ⥯����������
extern	float	P_water_in_heater=0;	// �������� ���� �� �室� � ⥯����������
extern	float	P_water_out_heater=0;	// �������� ���� �� ��室� �� ⥯�����������
extern	float	P_water_gvs_accum=0;	// �������� ���� �� �����ॢ ��� �� �����-�������஬
extern	float	S_water_reg_temp=0;		// ��������� ������� ॣ���� ⥬������� ����
extern	float	L_water_bak_accum=0;	// �஢��� ���� � ����-��������
extern	float	L_cond_bak_nakop=0;		// �஢��� �������� � ����-������⥫�

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater=0;		// ��������� ��� �� �室� � ⥯����������
extern	float	T_water_in_heater=0;	// ��������� ���� �� �室� � ⥯����������
extern	float	T_water_out_heater=0;	// ��������� ���� �� ��室� �� ⥯�����������
extern	float	T_water_out_gvs=0;		// ��������� ��� �� ���ॡ�⥫��
extern	float	T_water_podp_hvs=0;		// ��������� ������筮� ���� ���
extern	float	T_water_bak_accum=0;	// ��������� ���� � ����-��������
extern	float	T_cond_bak_nakop=0;		// ��������� �������� � ����-������⥫�
extern	float	P_gvs_in_bak_nak=0;		// �������� ���� ����樨 ��� ��। �����-����-஬

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened=0;		// ��⢮� �� ����� ���� �����ॢ� ��� �����
extern	byte	podgvs_zatvor_napor_closed=0;	// ��⢮� �� ����� ���� �����ॢ� ��� ������
extern	byte	podgvs_rele_nasos_status=0;		// ���� �������� �� ��� ���� �����ॢ� ���
extern	byte	podgvs_regim_nasos_system=0;	// ���� �����ॢ� ��� � ०��� "���⥬���"
extern	byte	podgvs_regim_nasos_hand=0;		// ���� �����ॢ� ��� � ०��� "��筮�"
extern	byte	podgvs_kont_nasos_vkl=0;		// ���⠪�� ���� �����ॢ� ��� ����祭

extern	byte	podpdear_zatv_nasos_opened=0;		// ��⢮� �� ����� ���� �����⪨ ������� �����
extern	byte	podpdear_zatv_nasos_closed=0;	// ��⢮� �� ����� ���� �����⪨ ������� ������
extern	byte	podpdear_rele_nasos_closed=0;	// ���� �������� �� ��� ���� �����⪨ �������
extern	byte	podpdear_regim_nasos_system=0;	// ���� �����⪨ ������� � ०��� "���⥬���"
extern	byte	podpdear_regim_nasos_hand=0;	// ���� �����⪨ ������� � ०��� "��筮�"
extern	byte	podpdear_kont_nasos_vkl=0;		// ���⠪�� ���� �����⪨ ������� ����祭

extern	byte	circgvs_zatv_nasos_opened=0;		// ��⢮� �� ����� ���� ����樨 ��� �����
extern	byte	circgvs_zatv_nasos_closed=0;	// ��⢮� �� ����� ���� ����樨 ��� ������
extern	byte	circgvs_rele_nasos_status=0;	// ���� �������� �� ��� ���� ����樨 ���
extern	byte	circgvs_regim_nasos_system=0;	// ���� ����樨 ��� � ०��� "���⥬���"
extern	byte	circgvs_regim_nasos_hand=0;		// ���� ����樨 ��� � ०��� "��筮�"
extern	byte	circgvs_kont_nasos_gvs=0;		// ���⠪�� ���� ����樨 ��� ����祭

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system=0;		// ��⢮� �� �����ॢ ��� � ०��� "���⥬���"
extern	byte	podgvs_zatv_nasos_opened=0;		// ��⢮� �� �����ॢ ��� �����
extern	byte	podgvs_zatv_nasos_closed=0;		// ��⢮� �� �����ॢ ��� ������

extern	byte	podgvs_regim_obrat_system=0;		// ��⢮� �� ���⪥ �����ॢ� ��� � ०��� "���⥬���"
extern	byte	podgvs_zatv_obrat_opened=0;		// ��⢮� �� ���⪥ �����ॢ� ��� �����
extern	byte	podgvs_zatv_obrat_closed=0;		// ��⢮� �� ���⪥ �����ॢ� ��� ������

extern	byte	circgvs_regim_zatv_system=0;	// ��⢮� �� ������ ��� � ०��� "���⥬���"
extern	byte	circgvs_zatv_opened=0;			// ��⢮� �� ������ ��� �����
extern	byte	circgvs_zatv_closed=0;			// ��⢮� �� ������ ��� ������

extern	byte	circgvs_regim_obrat_system=0;	// ��⢮� �� ���⪥ ����樨 ��� � ०��� "���⥬���"
extern	byte	circgvs_zatv_obrat_opened=0;	// ��⢮� �� ���⪥ ����樨 ��� �����
extern	byte	circgvs_zatv_obrat_closed=0;	// ��⢮� �� ���⪥ ����樨 ��� ������

extern	byte	bypass_regim_bakaccum_system=0;	// ��⢮� �� ������ ����-�����-� � ०��� "���⥬���"
extern	byte	bypass_zatv_bakaccum_opened=0;	// ��⢮� �� ������ ����-�������� �����
extern	byte	bypass_zatv_bakaccum_closed=0;	// ��⢮� �� ������ ����-�������� ������

extern	byte	regulator_klapan_tvoda_system=0;// ������ ॣ���� ⥬������� ���� � ०. "���⥬���"
extern	byte	regulator_klapan_tvoda_opened=0;	// ������ ॣ���� ⥬������� ���� �����
extern	byte	regulator_klapan_tvoda_closed=0;// ������ ॣ���� ⥬������� ���� ������

extern	byte	podphvs_zatv_regim_system=0;	// ��⢮� �����⪨ ��� � ०��� "���⥬���"
extern	byte	podphvs_zatv_hvs_opened=0;		// ��⢮� �����⪨ ��� �����
extern	byte	podphvs_zatv_hvs_closed=0;		// ��⢮� �����⪨ ��� ������

extern	byte	podpaccum_zatv_regim_system=0;	// ��⢮� �� �����⪥ � ���-������⥫� � ०��� "���⥬���"
extern	byte	podpaccum_zatv_accum_opened=0;	// ��⢮� �� �����⪥ � ���-������⥫� �����
extern	byte	podpaccum_zatv_accum_closed=0;	// ��⢮� �� �����⪥ � ���-������⥫� ������

extern	byte	podpdear_zatv_bypass_system=0;	// ��⢮� �� ������ �����⪨ ������� � ०��� "���⥬���"
extern	byte	podpdear_zatv_bypass_opened;		// ��⢮� �� ������ �����⪨ ������� �����
extern	byte	podpdear_zatv_bypass_closed;	// ��⢮� �� ������ �����⪨ ������� ������

extern	byte	podpar_zatv_regim_system=0;		// ��⢮� �� ����� ��� � ०��� "���⥬���"
extern	byte	podpar_zatv_obrat_opened=0;		// ��⢮� �� ����� ��� �����
extern	byte	podpar_zatv_obrat_closed=0;		// ��⢮� �� ����� ��� ������

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open=0;		// ������ ��⢮� �� ����� ���� �����ॢ� ���       (��2)
extern	byte	podgvs_zatv_nasos_close=0;		// ������� ��⢮� �� ����� ���� �����ॢ� ���       (��2)
extern	byte	podgvs_kont_nasos_on=0;			// ������� ���⠪�� ���� �����ॢ� ���                   (�2)
extern	byte	podgvs_kont_nasos_off=0;		// �⪫���� ���⠪�� ���� �����ॢ� ���                 (�2)

extern	byte	circgvs_zatv_nasos_open=0;		// ������ ��⢮� �� ����� ���� ����樨 ���     (��3)
extern	byte	circgvs_zatv_nasos_close=0;		// ������� ��⢮� �� ����� ���� ����樨 ���     (��3)
extern	byte	circgvs_kont_nasos_on=0;		// ������� ���⠪�� ���� ����樨 ���                 (�3)
extern	byte	circgvs_kont_nasos_off=0;		// �⪫���� ���⠪�� ���� ����樨 ���               (�3)

extern	byte	podpdear_zatv_nasos_open=0;		// ������ ��⢮� �� ����� ���� �����⪨ �����-� (��1)
extern	byte	podpdear_zatv_nasos_close=0;	// ������� ��⢮� �� ����� ���� �����⪨ �����-� (��1)
extern	byte	podpdear_kont_nasos_on=0;		// ������� ���⠪�� ���� �����⪨ �������      (�1)
extern	byte	podpdear_kont_nasos_off=0;		// �⪫���� ���⠪�� ���� �����⪨ �������    (�1)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open=0;			// ������ ��⢮� �� �����ॢ ���                                      (��4)
extern	byte	podgvs_zatv_gvs_close=0;		// ������� ��⢮� �� �����ॢ ���                                       (��4)
extern	byte	podgvs_zatv_obr_open=0;			// ������ ��⢮� �� ���⪥ �����ॢ� ���                    (��5)
extern	byte	podgvs_zatv_obr_close=0;			// ������� ��⢮� �� ���⪥ �����ॢ� ���                     (��5)

extern	byte	circgvs_zatv_gvs_open=0;		// ������ ��⢮� �� ������ ���        (��6)
extern	byte	circgvs_zatv_gvs_close=0;		// ������� ��⢮� �� ������ ���        (��6)
extern	byte	circgvs_zatv_obr_open=0;		// ������ ��⢮� �� ���⪥ ����樨 ���(��7)
extern	byte	circgvs_zatv_obr_close=0;		// ������� ��⢮� �� ���⪥ ����樨 ���(��7)

extern	byte	podphvs_zatv_hvs_open=0;		// ������ ��⢮� �����⪨ ���         (��8)
extern	byte	podphvs_zatv_hvs_close=0;		// ������� ��⢮� �����⪨ ���         (��8)

// [5][MDO1.6] i-87061W
extern	byte	podpaccum_zatv_bak_open=0;		// ������ ��⢮� �� �����⪥ � ���-������⥫�           (��9)
extern	byte	podpaccum_zatv_bak_close=0;		// ������� ��⢮� �� �����⪥ � ���-������⥫�           (��9)
extern	byte	podpdear_zatv_bypass_open=0;	// ������ ��⢮� �� ������ �����⪨ �������     (��10)
extern	byte	podpdear_zatv_bypass_close=0;	// ������� ��⢮� �� ������ �����⪨ �������     (��10)
extern	byte	bakaccum_zatv_bypass_open=0;	// ������ ��⢮� �� ������ ����-��������        (��11)
extern	byte	bakaccum_zatv_bypass_close=0;	// ������� ��⢮� �� ������ ����-��������        (��11)
extern	byte	podpar_zatv_par_open=0;			// ������ ��⢮� �� ����� ���                                      (��12)
extern	byte	podpar_zatv_par_close=0;		// ������� ��⢮� �� ����� ���                                      (��12)

// [6][MDO1.7] i-87061W
extern	byte	regtemp_klap_voda_open=0;		// ������ ������ ॣ���� ⥬������� ����
extern	byte	regtemp_klap_voda_close=0;		// ������� ������ ॣ���� ⥬������� ����
