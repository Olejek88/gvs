#define ReadHoldingRegisters	0x3
#define ReadInputRegisters		0x4
#define PresetSingleRegister  	0x5
#define PresetMultiRegister  	0x6

// IO variables
// [0][MAI1.1] i-87017RW
extern	float	P_par_tech;				// Давление пара на технологию
extern	float	P_par_in_heater;		// Давление пара на входе в теплообменник
extern	float	P_water_in_heater;		// Давление воды на входе в теплообменник
extern	float	P_water_out_heater;		// Давление воды на выходе из теплообменника
extern	float	P_water_gvs_accum;		// Давление воды на подогрев ГВС за баком-аккумулятором
extern	float	L_water_bak_accum;		// Уровень воды в баке-аккумуляторе
extern	float	V_water_bak_accum;		// Объем воды в баке-аккумуляторе
extern	float	P_water_potreb;			// Давление воды на выходе из теплообменника

// [1][MAI1.2] i-87017RW
extern	float	T_par_in_heater;		// Температура пара на входе в теплообменник
extern	float	T_water_in_heater;		// Температура воды на входе в теплообменник
extern	float	T_water_out_heater;		// Температура воды на выходе из теплообменника
extern	float	T_water_out_gvs;		// Температура ГВС на потребителей
extern	float	T_water_podp_hvs;		// Температура подпиточной воды ХВС
extern	float	T_water_bak_accum;		// Температура воды в баке-аккумуляторе
extern	float	T_water_prach;			// Температура воды в прачечной
extern	float	T_water_stolv;			// Температура воды в столовой

// [2][MDI1.3] i-87040W
extern	byte	podgvs_zatvor_napor_opened;	// Затвор на напоре насоса подогрева ГВС открыт
extern	byte	podgvs_zatvor_napor_closed;	// Затвор на напоре насоса подогрева ГВС закрыт
extern	byte	podgvs_rele_nasos_status;	// Реле давления на всасе насоса подогрева ГВС
extern	byte	podgvs_regim_nasos_system;	// Насос подогрева ГВС в режиме "Системное"
extern	byte	podgvs_regim_nasos_hand;	// Насос подогрева ГВС в режиме "Ручное"
extern	byte	podgvs_kont_nasos_vkl;		// Контактор насоса подогрева ГВС включен

extern	byte	gvs_zatv_nasos_opened;		// Затвор на напоре насоса ГВС открыт
extern	byte	gvs_zatv_nasos_closed;		// Затвор на напоре насоса ГВС закрыт
extern	byte	circgvs_rele_nasos_status;	// Реле давления на всасе насоса циркуляции ГВС
extern	byte	circgvs_regim_nasos_system;	// Насос циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_regim_nasos_hand;	// Насос циркуляции ГВС в режиме "Ручное"
extern	byte	circgvs_kont_nasos_gvs;		// Контактор насоса циркуляции ГВС включен

// [3][MDI1.4] i-87040W
extern	byte	podgvs_regim_zatv_system;		// Затвор на подогрев ГВС в режиме "Системное"
extern	byte	podgvs_zatv_nasos_opened;		// Затвор на подогрев ГВС открыт
extern	byte	podgvs_zatv_nasos_closed;		// Затвор на подогрев ГВС закрыт

extern	byte	podgvs_regim_obrat_system;		// Затвор на обратке подогрева ГВС в режиме "Системное"
extern	byte	podgvs_zatv_obrat_opened;		// Затвор на обратке подогрева ГВС открыт
extern	byte	podgvs_zatv_obrat_closed;		// Затвор на обратке подогрева ГВС закрыт

extern	byte	circgvs_regim_zatv_system;		// Затвор на циркуляцию ГВС в режиме "Системное"
extern	byte	circgvs_zatv_opened;			// Затвор на циркуляцию ГВС открыт
extern	byte	circgvs_zatv_closed;			// Затвор на циркуляцию ГВС закрыт

extern	byte	circgvs_regim_obrat_system;		// Затвор на обратке циркуляции ГВС в режиме "Системное"
extern	byte	circgvs_zatv_obrat_opened;		// Затвор на обратке циркуляции ГВС открыт
extern	byte	circgvs_zatv_obrat_closed;		// Затвор на обратке циркуляции ГВС закрыт

extern	byte	regulator_klapan_tvoda_system;	// Клапан регулятора температуры воды в реж. "Системное"
extern	byte	regulator_klapan_tvoda_opened;	// Клапан регулятора температуры воды открыт
extern	byte	regulator_klapan_tvoda_closed;	// Клапан регулятора температуры воды закрыт

extern	byte	podphvs_zatv_regim_system;		// Затвор подпитки ХВС в режиме "Системное"
extern	byte	podphvs_zatv_hvs_opened;		// Затвор подпитки ХВС открыт
extern	byte	podphvs_zatv_hvs_closed;		// Затвор подпитки ХВС закрыт

extern	byte	podpar_zatv_regim_system;		// Затвор на подаче пара в режиме "Системное"
extern	byte	podpar_zatv_obrat_opened;		// Затвор на подаче пара открыт
extern	byte	podpar_zatv_obrat_closed;		// Затвор на подаче пара закрыт

// [4][MDO1.5] i-87040W
extern	byte	podgvs_zatv_nasos_open;			// Открыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_zatv_nasos_close;		// Закрыть затвор на напоре насоса подогрева ГВС       (ЗД2)
extern	byte	podgvs_kont_nasos_on;			// Включить контактор насоса подогрева ГВС                   (М2)
extern	byte	podgvs_kont_nasos_off;			// Отключить контактор насоса подогрева ГВС                 (М2)

extern	byte	circgvs_zatv_nasos_open;	// Открыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_zatv_nasos_close;	// Закрыть затвор на напоре насоса циркуляции ГВС     (ЗД3)
extern	byte	circgvs_kont_nasos_on;		// Включить контактор насоса циркуляции ГВС                 (М3)
extern	byte	circgvs_kont_nasos_off;		// Отключить контактор насоса циркуляции ГВС               (М3)

// [5][MDO1.5] i-87061W
extern	byte	podgvs_zatv_gvs_open;		// Открыть затвор на подогрев ГВС                                      (ЗД4)
extern	byte	podgvs_zatv_gvs_close;		// Закрыть затвор на подогрев ГВС                                       (ЗД4)
extern	byte	podgvs_zatv_obr_open;		// Открыть затвор на обратке подогрева ГВС                    (ЗД5)
extern	byte	podgvs_zatv_obr_close;		// Закрыть затвор на обратке подогрева ГВС                     (ЗД5)

extern	byte	circgvs_zatv_gvs_open;		// Открыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_gvs_close;		// Закрыть затвор на циркуляцию ГВС        (ЗД6)
extern	byte	circgvs_zatv_obr_open;		// Открыть затвор на обратке циркуляции ГВС(ЗД7)
extern	byte	circgvs_zatv_obr_close;		// Закрыть затвор на обратке циркуляции ГВС(ЗД7)

extern	byte	podphvs_zatv_hvs_open;		// Открыть затвор подпитки ХВС         (ЗД8)
extern	byte	podphvs_zatv_hvs_close;		// Закрыть затвор подпитки ХВС         (ЗД8)
extern	byte	podpar_zatv_par_open;		// Открыть затвор на подаче пара                                      (ЗД12)
extern	byte	podpar_zatv_par_close;		// Закрыть затвор на подаче пара                                      (ЗД12)

// [6][MDO1.6] i-87061W
extern	byte	regtemp_klap_voda_open;		// Открыть клапан регулятора температуры воды
extern	byte	regtemp_klap_voda_close;		// Закрыть клапан регулятора температуры воды

extern	byte	bak_level_critical_low;		// уровень в баке низкий критический [22]
extern	byte	bak_level_warning_low;		// уровень в баке низкий предупредительный [23]
extern	byte	bak_level_work_low;			// уровень в баке низкий рабочий [24]
extern	byte	bak_level_critical_high;	// уровень в баке высокий критический [25]
extern	byte	bak_level_warning_high;		// уровень в баке высокий предупредительный [26]
extern	byte	bak_level_work_high;		// уровень в баке высокий рабочий [27]
//206
extern	byte	voda_temp_critical_low;		// температура воды низкий критический [28]
extern	byte	voda_temp_warning_low;		// температура воды низкий предупредительный [29]
extern	byte	voda_temp_work_low;			// температура воды низкий рабочий [30]
extern	byte	voda_temp_warning_high;		// температура воды высокий предупредительный [31]
extern	byte	voda_temp_critical_high;	// температура воды высокий критический [32]
extern	byte	voda_temp_work_high;		// температура воды высокий рабочий [33]

extern	byte	gvs_temp_potr_low;			// температура воды на потребителей низкий [34]
extern	byte	gvs_temp_potr_high;			// температура воды на потребителей высокий [35]
extern	byte	voda_potr_high;				// давление воды на потребителей высокий [36]
extern	byte	voda_potr_stop;				// нет разбора - остановлен М2 [37]
extern	uint	timer_Ppotr_high;			// таймер высокого давления воды на потребителей [38]

// [0][MAI1.1] i-87017RW
extern	float	aP_par_tech;			// Давление пара на технологию
extern	float	aP_par_in_heater;		// Давление пара на входе в теплообменник
extern	float	aP_water_in_heater;		// Давление воды на входе в теплообменник
extern	float	aP_water_out_heater;	// Давление воды на выходе из теплообменника
extern	float	aP_water_gvs_accum;		// Давление воды на подогрев ГВС за баком-аккумулятором
extern	float	aL_water_bak_accum;		// Уровень воды в баке-аккумуляторе
extern	float	aP_water_potreb;		// Давление воды на потребителей

// [1][MAI1.2] i-87017RW
extern	float	aT_par_in_heater;		// Температура пара на входе в теплообменник
extern	float	aT_water_in_heater;		// Температура воды на входе в теплообменник
extern	float	aT_water_out_heater;	// Температура воды на выходе из теплообменника
extern	float	aT_water_out_gvs;		// Температура ГВС на потребителей
extern	float	aT_water_podp_hvs;		// Температура подпиточной воды ХВС
extern	float	aT_water_bak_accum;		// Температура воды в баке-аккумуляторе
extern	float	aT_water_prach;			// Температура воды в прачечной
extern	float	aT_water_stolv;			// Температура воды в столовой

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