/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: pcl836.h

    Описание классов для работы с контроллером ввода/вывода
    Advantech PCL-836

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef pcl836H
#define pcl836H

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "device.h"
#include "signals.h"

//---------------------------------------------------------------------------
//defines for icl836
//Counter control register format
#define CCR_EXTRENAL_CLOCK_WITHOUT_FILTER   0x00
#define CCR_EXTERNAL_CLOCK_WITH_FILTER      0x01
#define CCR_INTERNAL_CLOCK                  0x02
#define CCR_PWM                             0x03
#define CCR_POSITIVE_EDGE                   0x00
#define CCR_NEGATIVE_EDGE                   0x04
//Counter control register
#define SELECT_COUNTER_0                    0x00
#define SELECT_COUNTER_1                    0x40
#define SELECT_COUNTER_2                    0x80
#define SELECT_COUNTER_READ_BACK            0xc0

#define RW_COUNTER_LATCH                    0x00
#define RW_LSB                              0x10
#define RW_MSB                              0x20
#define RW_LSB_MSB                          0x30

#define MODE_0                              0x00
#define MODE_1                              0x02
#define MODE_2                              0x04
#define MODE_3                              0x06
#define MODE_4                              0x08
#define MODE_5                              0x0a

#define BCD_16_BIT                          0x00
#define BCD_DECIMAL                         0x01

#define MAX_COUNTER_VALUE					0xffff

//from model
//#define WR_RD_836   						(0x80 & 0xbf)
//from real i/o
#define WR_RD_836							(0x40 & 0x7f)

//---------------------------------------------------------------------------
class Device_pcl836 : public Device
{
public:
	Device_pcl836(void);	//конструктор
};


//---------------------------------------------------------------------------
class Device_pcl836_counters : public Device_pcl836
{
private:

	void set_counter_clock_input_mode(int counter, unsigned char mode);
    void write_counter_control_word(int counter, unsigned char cw);
    void write_fout_control_word(int fout, unsigned char cw);

public:
	Device_pcl836_counters(void);	//конструктор

    virtual void Start(void);	//инициализация, открытие портов
    virtual void Stop(void);	//закрытие портов, завершающие действия

    virtual int Get(int offset, int bit);	//получить частотный сигнал
                                    /*
                                    offset - номер счётчика 0-5
                                    функция делает все необходимые действия
                                    возвращает WORD - состояние счётчика
                                    с момента последнего считывания;
                                    для получения частоты нужно делать
                                    freq = old - GetFI;
                                    а при переходе через ноль
                                    freq = old + MAX_COUNTER_VALUE - GetFI
                                    ЭТО ДЕЛАЕТ МЕТОД In класса FreqSignal836
                                    */
    virtual int Put(int offset, int bit, int data);//вывести частотный сигнал
    								/*
                                    Записывает значение WORD в счетчик.
                                    */
};

//---------------------------------------------------------------------------
class Device_pcl836_discrete : public Device_pcl836
{
public:
	Device_pcl836_discrete(void);	//конструктор

    virtual int Get(int offset, int bit);			//получить дисретный сигнал
    								/*
                                    offset в данном случае - это номер канала
                                    мультиплексора
                                    */

    virtual int Put(int offset, int bit, int data);	//вывести дискретный сигнал
    								/*
                                    а тут offset - смещение от базового адреса
                                    */
};

//---------------------------------------------------------------------------
//частотный сигнал
class FreqSignal836 : public FreqSignal
{
public:
    FreqSignal836(void);//constructor

    virtual void In (void); //out from i/o port
    virtual char* format(void);
private:
    int prev;
    int devotion;
};

//---------------------------------------------------------------------------
#endif
