extern	byte	WorkEnable;		// work flag
extern	short	currentregim;	// 0 - test, 1-3 scene selection

// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech;			// Давление пара на технологию
extern	float	P_par_in_heater;		// Давление пара на входе в теплообменник
extern	float	P_water_in_heater;	// Давление воды на входе в теплообменник
extern	float	P_water_out_heater;	// Давление воды на выходе из теплообменника
extern	float	P_water_gvs_accum;	// Давление воды на подогрев ГВС за баком-аккумулятором
extern	float	S_water_reg_temp;		// Положение клапана регулятора температуры воды
extern	float	L_water_bak_accum;	// Уровень воды в баке-аккумуляторе
extern	float	L_cond_bak_nakop;		// Уровень конденсата в баке-накопителе
extern	float	V_water_bak_accum;	// Уровень воды в баке-аккумуляторе
extern	float	S_KT;					// Положение клапана

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater;		// Температура пара на входе в теплообменник
extern	float	T_water_in_heater;	// Температура воды на входе в теплообменник
extern	float	T_water_out_heater;	// Температура воды на выходе из теплообменника
extern	float	T_water_out_gvs;		// Температура ГВС на потребителей
extern	float	T_water_podp_hvs;		// Температура подпиточной воды ХВС
extern	float	T_water_bak_accum;	// Температура воды в баке-аккумуляторе
extern	float	T_cond_bak_nakop;		// Температура конденсата в баке-накопителе
extern	float	P_gvs_in_bak_nak;		// Давление воды циркуляции ГВС перед баком-аккум-ром

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened;		// Затвор на напоре насоса подогрева ГВС открыт
extern	byte	podgvs_zatvor_napor_closed;	// Затвор на напоре насоса подогрева ГВС закрыт
extern	byte	podgvs_rele_nasos_status;		// Реле давления на всасе насоса подогрева ГВС
extern	byte	podgvs_regim_nasos_system;	// Насос подогрева ГВС в режиме "Системное"
extern	byte	podgvs_regim_nasos_hand;		// Насос подогрева ГВС в режиме "Ручное"
extern	byte	podgvs_kont_nasos_vkl;		// Контактор насоса подогрева ГВС включен

extern	byte	podpdear_zatv_nasos_opened;		// Затвор на напоре насоса подпитки деаэратора открыт
extern	byte	podpdear_zatv_nasos_closed;	// Затвор на напоре насоса подпитки деаэратора закрыт
extern	byte	podpdear_rele_nasos_closed;	// Реле давления на всасе насоса подпитки деаэратора
extern	byte	podpdear_regim_nasos_system;	// Насос подпитки деаэратора в режиме "Системное"
extern	byte	podpdear_regim_nasos_hand;	// Насос подпитки деаэратора в режиме "Ручное"
extern	byte	podpdear_kont_nasos_vkl;		// Контактор насоса подпитки деаэратора включен

extern	byte	circgvs_zatv_nasos_opened;		// Затвор на напоре насоса циркуляции ГВС открыт
extern	byte	circgvs_zatv_nasos_closed;	// Затвор на напоре насоса циркуляции ГВС закрыт
extern	byte	circgvs_rele_nasos_status;	// Реле давления на всасе насоса циркуляции ГВС
extern	byte	circgvs_regim_nasos_system;	// Насос циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_regim_nasos_hand;		// Насос циркуляции ГВС в режиме "Ручное"
extern	byte	circgvs_kont_nasos_gvs;		// Контактор насоса циркуляции ГВС включен

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system;		// Затвор на подогрев ГВС в режиме "Системное"
extern	byte	podgvs_zatv_nasos_opened;		// Затвор на подогрев ГВС открыт
extern	byte	podgvs_zatv_nasos_closed;		// Затвор на подогрев ГВС закрыт

extern	byte	podgvs_regim_obrat_system;		// Затвор на обратке подогрева ГВС в режиме "Системное"
extern	byte	podgvs_zatv_obrat_opened;		// Затвор на обратке подогрева ГВС открыт
extern	byte	podgvs_zatv_obrat_closed;		// Затвор на обратке подогрева ГВС закрыт

extern	byte	circgvs_regim_zatv_system;	// Затвор на циркуляцию ГВС в режиме "Системное"
extern	byte	circgvs_zatv_opened;			// Затвор на циркуляцию ГВС открыт
extern	byte	circgvs_zatv_closed;			// Затвор на циркуляцию ГВС закрыт

extern	byte	circgvs_regim_obrat_system;	// Затвор на обратке циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_zatv_obrat_opened;	// Затвор на обратке циркуляции ГВС открыт
extern	byte	circgvs_zatv_obrat_closed;	// Затвор на обратке циркуляции ГВС закрыт

extern	byte	bypass_regim_bakaccum_system;	// Затвор на байпасе бака-аккумул-ра в режиме "Системное"
extern	byte	bypass_zatv_bakaccum_opened;	// Затвор на байпасе бака-аккумулятора открыт
extern	byte	bypass_zatv_bakaccum_closed;	// Затвор на байпасе бака-аккумулятора закрыт

extern	byte	regulator_klapan_tvoda_system;// Клапан регулятора температуры воды в реж. "Системное"
extern	byte	regulator_klapan_tvoda_opened;	// Клапан регулятора температуры воды открыт
extern	byte	regulator_klapan_tvoda_closed;// Клапан регулятора температуры воды закрыт

extern	byte	podphvs_zatv_regim_system;	// Затвор подпитки ХВС в режиме "Системное"
extern	byte	podphvs_zatv_hvs_opened;		// Затвор подпитки ХВС открыт
extern	byte	podphvs_zatv_hvs_closed;		// Затвор подпитки ХВС закрыт

extern	byte	podpaccum_zatv_regim_system;	// Затвор на подпитке в бак-накопитель в режиме "Системное"
extern	byte	podpaccum_zatv_accum_opened;	// Затвор на подпитке в бак-накопитель открыт
extern	byte	podpaccum_zatv_accum_closed;	// Затвор на подпитке в бак-накопитель закрыт

extern	byte	podpdear_zatv_bypass_system;	// Затвор на байпасе подпитки деаэратора в режиме "Системное"
extern	byte	podpdear_zatv_bypass_opened;		// Затвор на байпасе подпитки деаэратора открыт
extern	byte	podpdear_zatv_bypass_closed;	// Затвор на байпасе подпитки деаэратора закрыт

extern	byte	podpar_zatv_regim_system;		// Затвор на подаче пара в режиме "Системное"
extern	byte	podpar_zatv_obrat_opened;		// Затвор на подаче пара открыт
extern	byte	podpar_zatv_obrat_closed;		// Затвор на подаче пара закрыт

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open;		// Открыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_zatv_nasos_close;		// Закрыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_kont_nasos_on;			// Включить контактор насоса подогрева ГВС                   (М2)
extern	byte	podgvs_kont_nasos_off;		// Отключить контактор насоса подогрева ГВС                 (М2)

extern	byte	circgvs_zatv_nasos_open;		// Открыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_zatv_nasos_close;		// Закрыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_kont_nasos_on;		// Включить контактор насоса циркуляции ГВС                 (М3)
extern	byte	circgvs_kont_nasos_off;		// Отключить контактор насоса циркуляции ГВС               (М3)

extern	byte	podpdear_zatv_nasos_open;		// Открыть затвор на напоре насоса подпитки деаэр-р (ЗД1)
extern	byte	podpdear_zatv_nasos_close;	// Закрыть затвор на напоре насоса подпитки деаэр-ра (ЗД1)
extern	byte	podpdear_kont_nasos_on;		// Включить контактор насоса подпитки деаэратора      (М1)
extern	byte	podpdear_kont_nasos_off;		// Отключить контактор насоса подпитки деаэратора    (М1)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open;			// Открыть затвор на подогрев ГВС                                      (ЗД4)
extern	byte	podgvs_zatv_gvs_close;		// Закрыть затвор на подогрев ГВС                                       (ЗД4)
extern	byte	podgvs_zatv_obr_open;			// Открыть затвор на обратке подогрева ГВС                    (ЗД5)
extern	byte	podgvs_zatv_obr_close;			// Закрыть затвор на обратке подогрева ГВС                     (ЗД5)

extern	byte	circgvs_zatv_gvs_open;		// Открыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_gvs_close;		// Закрыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_obr_open;		// Открыть затвор на обратке циркуляции ГВС(ЗД7)
extern	byte	circgvs_zatv_obr_close;		// Закрыть затвор на обратке циркуляции ГВС(ЗД7)

extern	byte	podphvs_zatv_hvs_open;		// Открыть затвор подпитки ХВС         (ЗД8)
extern	byte	podphvs_zatv_hvs_close;		// Закрыть затвор подпитки ХВС         (ЗД8)

// [5][MDO1.6] i-87061W
extern	byte	podpaccum_zatv_bak_open;	// Открыть затвор на подпитке в бак-накопитель           (ЗД9)
extern	byte	podpaccum_zatv_bak_close;	// Закрыть затвор на подпитке в бак-накопитель           (ЗД9)
extern	byte	podpdear_zatv_bypass_open;	// Открыть затвор на байпасе подпитки деаэратора     (ЗД10)
extern	byte	podpdear_zatv_bypass_close;	// Закрыть затвор на байпасе подпитки деаэратора     (ЗД10)
extern	byte	bakaccum_zatv_bypass_open;	// Открыть затвор на байпасе бака-аккумулятора        (ЗД11)
extern	byte	bakaccum_zatv_bypass_close;	// Закрыть затвор на байпасе бака-аккумулятора        (ЗД11)
extern	byte	podpar_zatv_par_open;		// Открыть затвор на подаче пара                                      (ЗД12)
extern	byte	podpar_zatv_par_close;		// Закрыть затвор на подаче пара                                      (ЗД12)

// [6][MDO1.7] i-87061W
extern	byte	regtemp_klap_voda_open;		// Открыть клапан регулятора температуры воды
extern	byte	regtemp_klap_voda_close;	// Закрыть клапан регулятора температуры воды


extern float	V1_dushCGTS;
extern float	V2_dushPFI;
extern float	V3_stol;
extern float	V4_prach;

extern float	P_par_tech;				// Давление пара на технологию
extern float	P_par_in_heater;		// Давление пара на входе в теплообменник
extern float	P_water_in_heater;		// Давление воды на входе в теплообменник
extern float	P_water_out_heater;		// Давление воды на выходе из теплообменника
extern float	P_water_gvs_accum;		// Давление воды на подогрев ГВС за баком-аккумулятором
//extern float	S_water_reg_temp;		// Положение клапана регулятора температуры воды
extern float	L_water_bak_accum;		// Уровень воды в баке-аккумуляторе
//extern float	L_cond_bak_nakop;		// Уровень конденсата в баке-накопителе

// [1][MAI1.2] i-87017RW
extern float	T_par_in_heater;		// Температура пара на входе в теплообменник
extern float	T_water_in_heater;		// Температура воды на входе в теплообменник
extern float	T_water_out_heater;		// Температура воды на выходе из теплообменника
extern float	T_water_out_gvs;		// Температура ГВС на потребителей
extern float	T_water_podp_hvs;		// Температура подпиточной воды ХВС
extern float	T_water_bak_accum;		// Температура воды в баке-аккумуляторе
extern float	T_water_prach;			// Температура воды в прачечной
extern float	T_water_stolv;			// Температура воды в столовой 