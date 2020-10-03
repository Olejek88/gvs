// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech=0;			// Давление пара на технологию
extern	float	P_par_in_heater=0;		// Давление пара на входе в теплообменник
extern	float	P_water_in_heater=0;	// Давление воды на входе в теплообменник
extern	float	P_water_out_heater=0;	// Давление воды на выходе из теплообменника
extern	float	P_water_gvs_accum=0;	// Давление воды на подогрев ГВС за баком-аккумулятором
extern	float	S_water_reg_temp=0;		// Положение клапана регулятора температуры воды
extern	float	L_water_bak_accum=0;	// Уровень воды в баке-аккумуляторе
extern	float	L_cond_bak_nakop=0;		// Уровень конденсата в баке-накопителе

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater=0;		// Температура пара на входе в теплообменник
extern	float	T_water_in_heater=0;	// Температура воды на входе в теплообменник
extern	float	T_water_out_heater=0;	// Температура воды на выходе из теплообменника
extern	float	T_water_out_gvs=0;		// Температура ГВС на потребителей
extern	float	T_water_podp_hvs=0;		// Температура подпиточной воды ХВС
extern	float	T_water_bak_accum=0;	// Температура воды в баке-аккумуляторе
extern	float	T_cond_bak_nakop=0;		// Температура конденсата в баке-накопителе
extern	float	P_gvs_in_bak_nak=0;		// Давление воды циркуляции ГВС перед баком-аккум-ром

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened=0;		// Затвор на напоре насоса подогрева ГВС открыт
extern	byte	podgvs_zatvor_napor_closed=0;	// Затвор на напоре насоса подогрева ГВС закрыт
extern	byte	podgvs_rele_nasos_status=0;		// Реле давления на всасе насоса подогрева ГВС
extern	byte	podgvs_regim_nasos_system=0;	// Насос подогрева ГВС в режиме "Системное"
extern	byte	podgvs_regim_nasos_hand=0;		// Насос подогрева ГВС в режиме "Ручное"
extern	byte	podgvs_kont_nasos_vkl=0;		// Контактор насоса подогрева ГВС включен

extern	byte	podpdear_zatv_nasos_opened=0;		// Затвор на напоре насоса подпитки деаэратора открыт
extern	byte	podpdear_zatv_nasos_closed=0;	// Затвор на напоре насоса подпитки деаэратора закрыт
extern	byte	podpdear_rele_nasos_closed=0;	// Реле давления на всасе насоса подпитки деаэратора
extern	byte	podpdear_regim_nasos_system=0;	// Насос подпитки деаэратора в режиме "Системное"
extern	byte	podpdear_regim_nasos_hand=0;	// Насос подпитки деаэратора в режиме "Ручное"
extern	byte	podpdear_kont_nasos_vkl=0;		// Контактор насоса подпитки деаэратора включен

extern	byte	circgvs_zatv_nasos_opened=0;		// Затвор на напоре насоса циркуляции ГВС открыт
extern	byte	circgvs_zatv_nasos_closed=0;	// Затвор на напоре насоса циркуляции ГВС закрыт
extern	byte	circgvs_rele_nasos_status=0;	// Реле давления на всасе насоса циркуляции ГВС
extern	byte	circgvs_regim_nasos_system=0;	// Насос циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_regim_nasos_hand=0;		// Насос циркуляции ГВС в режиме "Ручное"
extern	byte	circgvs_kont_nasos_gvs=0;		// Контактор насоса циркуляции ГВС включен

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system=0;		// Затвор на подогрев ГВС в режиме "Системное"
extern	byte	podgvs_zatv_nasos_opened=0;		// Затвор на подогрев ГВС открыт
extern	byte	podgvs_zatv_nasos_closed=0;		// Затвор на подогрев ГВС закрыт

extern	byte	podgvs_regim_obrat_system=0;		// Затвор на обратке подогрева ГВС в режиме "Системное"
extern	byte	podgvs_zatv_obrat_opened=0;		// Затвор на обратке подогрева ГВС открыт
extern	byte	podgvs_zatv_obrat_closed=0;		// Затвор на обратке подогрева ГВС закрыт

extern	byte	circgvs_regim_zatv_system=0;	// Затвор на циркуляцию ГВС в режиме "Системное"
extern	byte	circgvs_zatv_opened=0;			// Затвор на циркуляцию ГВС открыт
extern	byte	circgvs_zatv_closed=0;			// Затвор на циркуляцию ГВС закрыт

extern	byte	circgvs_regim_obrat_system=0;	// Затвор на обратке циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_zatv_obrat_opened=0;	// Затвор на обратке циркуляции ГВС открыт
extern	byte	circgvs_zatv_obrat_closed=0;	// Затвор на обратке циркуляции ГВС закрыт

extern	byte	bypass_regim_bakaccum_system=0;	// Затвор на байпасе бака-аккумул-ра в режиме "Системное"
extern	byte	bypass_zatv_bakaccum_opened=0;	// Затвор на байпасе бака-аккумулятора открыт
extern	byte	bypass_zatv_bakaccum_closed=0;	// Затвор на байпасе бака-аккумулятора закрыт

extern	byte	regulator_klapan_tvoda_system=0;// Клапан регулятора температуры воды в реж. "Системное"
extern	byte	regulator_klapan_tvoda_opened=0;	// Клапан регулятора температуры воды открыт
extern	byte	regulator_klapan_tvoda_closed=0;// Клапан регулятора температуры воды закрыт

extern	byte	podphvs_zatv_regim_system=0;	// Затвор подпитки ХВС в режиме "Системное"
extern	byte	podphvs_zatv_hvs_opened=0;		// Затвор подпитки ХВС открыт
extern	byte	podphvs_zatv_hvs_closed=0;		// Затвор подпитки ХВС закрыт

extern	byte	podpaccum_zatv_regim_system=0;	// Затвор на подпитке в бак-накопитель в режиме "Системное"
extern	byte	podpaccum_zatv_accum_opened=0;	// Затвор на подпитке в бак-накопитель открыт
extern	byte	podpaccum_zatv_accum_closed=0;	// Затвор на подпитке в бак-накопитель закрыт

extern	byte	podpdear_zatv_bypass_system=0;	// Затвор на байпасе подпитки деаэратора в режиме "Системное"
extern	byte	podpdear_zatv_bypass_opened;		// Затвор на байпасе подпитки деаэратора открыт
extern	byte	podpdear_zatv_bypass_closed;	// Затвор на байпасе подпитки деаэратора закрыт

extern	byte	podpar_zatv_regim_system=0;		// Затвор на подаче пара в режиме "Системное"
extern	byte	podpar_zatv_obrat_opened=0;		// Затвор на подаче пара открыт
extern	byte	podpar_zatv_obrat_closed=0;		// Затвор на подаче пара закрыт

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open=0;		// Открыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_zatv_nasos_close=0;		// Закрыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_kont_nasos_on=0;			// Включить контактор насоса подогрева ГВС                   (М2)
extern	byte	podgvs_kont_nasos_off=0;		// Отключить контактор насоса подогрева ГВС                 (М2)

extern	byte	circgvs_zatv_nasos_open=0;		// Открыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_zatv_nasos_close=0;		// Закрыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_kont_nasos_on=0;		// Включить контактор насоса циркуляции ГВС                 (М3)
extern	byte	circgvs_kont_nasos_off=0;		// Отключить контактор насоса циркуляции ГВС               (М3)

extern	byte	podpdear_zatv_nasos_open=0;		// Открыть затвор на напоре насоса подпитки деаэр-р (ЗД1)
extern	byte	podpdear_zatv_nasos_close=0;	// Закрыть затвор на напоре насоса подпитки деаэр-ра (ЗД1)
extern	byte	podpdear_kont_nasos_on=0;		// Включить контактор насоса подпитки деаэратора      (М1)
extern	byte	podpdear_kont_nasos_off=0;		// Отключить контактор насоса подпитки деаэратора    (М1)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open=0;			// Открыть затвор на подогрев ГВС                                      (ЗД4)
extern	byte	podgvs_zatv_gvs_close=0;		// Закрыть затвор на подогрев ГВС                                       (ЗД4)
extern	byte	podgvs_zatv_obr_open=0;			// Открыть затвор на обратке подогрева ГВС                    (ЗД5)
extern	byte	podgvs_zatv_obr_close=0;			// Закрыть затвор на обратке подогрева ГВС                     (ЗД5)

extern	byte	circgvs_zatv_gvs_open=0;		// Открыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_gvs_close=0;		// Закрыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_obr_open=0;		// Открыть затвор на обратке циркуляции ГВС(ЗД7)
extern	byte	circgvs_zatv_obr_close=0;		// Закрыть затвор на обратке циркуляции ГВС(ЗД7)

extern	byte	podphvs_zatv_hvs_open=0;		// Открыть затвор подпитки ХВС         (ЗД8)
extern	byte	podphvs_zatv_hvs_close=0;		// Закрыть затвор подпитки ХВС         (ЗД8)

// [5][MDO1.6] i-87061W
extern	byte	podpaccum_zatv_bak_open=0;		// Открыть затвор на подпитке в бак-накопитель           (ЗД9)
extern	byte	podpaccum_zatv_bak_close=0;		// Закрыть затвор на подпитке в бак-накопитель           (ЗД9)
extern	byte	podpdear_zatv_bypass_open=0;	// Открыть затвор на байпасе подпитки деаэратора     (ЗД10)
extern	byte	podpdear_zatv_bypass_close=0;	// Закрыть затвор на байпасе подпитки деаэратора     (ЗД10)
extern	byte	bakaccum_zatv_bypass_open=0;	// Открыть затвор на байпасе бака-аккумулятора        (ЗД11)
extern	byte	bakaccum_zatv_bypass_close=0;	// Закрыть затвор на байпасе бака-аккумулятора        (ЗД11)
extern	byte	podpar_zatv_par_open=0;			// Открыть затвор на подаче пара                                      (ЗД12)
extern	byte	podpar_zatv_par_close=0;		// Закрыть затвор на подаче пара                                      (ЗД12)

// [6][MDO1.7] i-87061W
extern	byte	regtemp_klap_voda_open=0;		// Открыть клапан регулятора температуры воды
extern	byte	regtemp_klap_voda_close=0;		// Закрыть клапан регулятора температуры воды
