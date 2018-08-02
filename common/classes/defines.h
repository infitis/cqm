/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: defines.h

    Определение базовых классов : вес, зольность, влажность, уголь.

---------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
#ifndef CommonDefines
#define CommonDefines

//------------------------------------------------------------------------------
#include <iostream.h>

//------------------------------------------------------------------------------
#define MAX_STR_LEN 10

//------------------------------------------------------------------------------
extern const double P_MIN;
extern const double N_MIN;

extern const double A_MIN;
extern const double A_MAX;

extern const double H_MIN;
extern const double H_MAX;

extern const double PARAM_DEVIATION;

extern const double P_DEVIATION;
extern const double A_DEVIATION;
extern const double H_DEVIATION;

//------------------------------------------------------------------------------
class CoalParameter
{
    public:
    CoalParameter(void);      //конструктор
    CoalParameter(const double V);//инициализирующий конструктор
    CoalParameter(const CoalParameter &A);//копирующий конструктор
    CoalParameter& operator = (const CoalParameter &A);//оператор присваивания
    virtual bool   operator ==(const CoalParameter &A);//оператор присваивания
    double val;     //значение
    void setNull(void);//установка в Null
    bool isNull;  //признак отсутствия значения
    char* format(void);//вернуть отформатированное значение
    char* format(char *fmt);//вернуть отформатированное значение

    protected:
    char str[MAX_STR_LEN];//отформатированное значение
};
ostream& operator<<(ostream& s, CoalParameter& a);
istream& operator>>(istream& s, CoalParameter& a);

//------------------------------------------------------------------------------
class Ash : public CoalParameter  //зола
{
    public:
    Ash(void);      //конструктор
    Ash(const double V);//инициализирующий конструктор
    Ash(const Ash &A);//копирующий конструктор
};

//------------------------------------------------------------------------------
class Weight : public CoalParameter //вес
{
    public:
    Weight(void);   //конструктор
    Weight(const double V);//инициализирующий конструктор
    Weight(const Weight &W);//копирующий конструктор
};

//------------------------------------------------------------------------------
class Humidity : public CoalParameter //влажность
{
    public:
    Humidity(void);   //конструктор
    Humidity(const double V);//инициализирующий конструктор
    Humidity(const Humidity &H);//копирующий конструктор
};

//------------------------------------------------------------------------------
class Coal    //уголь
{
    public:
    Coal(void);         //конструктор
    Coal(const Coal &C);//копирующий конструктор
    Coal(const double P_, const double A_, const double H_=0);//ини-конструктор
    Coal& operator =(const Coal &C);//оператор присваивания
    bool operator ==(const Coal &C);//оператор присваивания
    bool empty(void);//true если p=a=h=0;
    void setempty(void);//set p=a=h=0;
    Weight P;//вес угля
    Ash    A;//зольность угля
    Humidity H;//влажность угля
};
ostream& operator<<(ostream& s, Coal& c);
istream& operator>>(istream& s, Coal& c);

//------------------------------------------------------------------------------
#endif

