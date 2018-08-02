/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: ioclass.h

    Описывает идентификаторы классов устройст, сигналов и
    методов их обработки

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef IOCLASSH
#define IOCLASSH

//---------------------------------------------------------------------------

/***************************
   FOR DEVICES & SIGNALS

   4 high bits defines MASK
   4 low  bits defines CLASS
 ***************************/

/******************
 *    devices     *
 ******************/

 //MASKS
//unknown                           00000000
#define DEVICE_GENERAL_MASK         0
//discrete                          10000000
#define DEVICE_DISCRETE_MASK        128
//freq                              01000000
#define DEVICE_FREQ_MASK            64

//CLASSES
//no class                          00000000
#define DEVICE_UNKNOWN              0
//Device_pcl836                     00000001
#define DEVICE_PCL836               1

//Device_pcl836_discrete            10000001
#define DEVICE_PCL836_DISCRETE_IN   129
//Device_a10_discrete               10000010
#define DEVICE_A10_DISCRETE_IN      130

//Device_pcl836_counters            01000001
#define DEVICE_PCL836_COUNTERS_IN   65
//Device_a10_counters               01000010
#define DEVICE_A10_COUNTERS_IN      66

/******************
 *    signals     *
 ******************/

//MASKS

//mask                          111100000000
#define SIGNAL_MASK                 3840

//unknown                           00000000
#define SIGNAL_GENERAL_MASK         0
//discrete                          10000000
#define SIGNAL_DISCRETE_MASK        128
//freq                              01000000
#define SIGNAL_FREQ_MASK            64

//for client browse                100000000
#define SIGNAL_FOR_CLIENT           256

//CLASSES
//no class                          00000000
#define SIGNAL_NONE                 0
//discrete                          10000001
#define SIGNAL_DISCRETE             129
//frequency                         01000001
#define SIGNAL_FREQ                 65

//frequency from 836                01000010
#define SIGNAL_FREQ_836             66

//frequency from a10                01000011
#define SIGNAL_FREQ_A10             67


/******************
 *    methods     *
 ******************/

//method MASKS correspond signal MASKS

//CLASSES
//no method                         00000000
#define METHOD_NONE                 0
//was at least one time logical 0   10000001
#define METHOD_WAS_0                129
//was at least one time logical 1   10000010
#define METHOD_WAS_1                130
//more 0 or 1                       10000011
#define METHOD_MAJOR                131
//was 0 more 4 times                10000100
#define METHOD_5ZEROS               132


//---------------------------------------------------------------------------
#endif
