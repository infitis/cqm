/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: signals.h

    Описание абстрактных классов для работы с дискретными
    и частотными сигналами

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef signalsH
#define signalsH

//---------------------------------------------------------------------------
#include <iostream.h>
#include <stdio.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "device.h"

//---------------------------------------------------------------------------
//абстрактный сигнал
class Signal
{
public:
    Signal(void);//constructor

    char name[MAX_NAME_LEN];//signal name
    char title[MAX_NAME_LEN];//signal caption
    int type;     //signal type
    int method;   //analysis method

	char devname[MAX_NAME_LEN];	//i/o device name
    Device* dev;  //i/o device handle

    int offset;   //offset address in i/o device
    int bit;      //bit number in i/o byte(word)
    int inverse;  //need inverse bit
    int active;   //active or default value use
    int defaultvalue; //data = default value if active = 0

    int data;     //signal value
    int result;   //method processing result

    //initialize i/o parameters
    virtual void Init(const char* name_, int type_, const char* devname_,
                      int offset_, int bit_, int inverse_, int active_, int defaultvalue_);
    void FindDevice(Device** devs, int devscount);//найти устройство по devname из массива устройств

    virtual void Out(void);                 //out to i/o port
    virtual void In (void);                 //out from i/o port
    virtual istream& Input(istream& s);     //get data from istream
    virtual ostream& Print(ostream& s);     //print to ostream

    char str[MAX_NAME_LEN];
    int flen;
    virtual char* format(void);
};

extern ostream& operator<< (ostream& s, Signal& d);
extern istream& operator>> (istream& s, Signal& d);

//---------------------------------------------------------------------------
//дискретный сигнал
class DiscreteSignal : public Signal
{
public:
    DiscreteSignal(void);//constructor

    virtual void Out(void);                 //out to i/o port
    virtual void In (void);                 //out from i/o port

    virtual char* format(void);
};

//---------------------------------------------------------------------------
//частотный сигнал
class FreqSignal : public Signal
{
public:
    FreqSignal(void);//constructor

    virtual void Out(void);                 //out to i/o port
    virtual void In (void);                 //out from i/o port

    virtual char* format(void);
};

//---------------------------------------------------------------------------
#endif
