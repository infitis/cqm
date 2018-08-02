/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmvagon.h

    Описание класса CqmVagon, который реализует анализ загрузки угля
    в вагоны с помощью одного питателя

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmvagon_qH
#define cqmvagon_qH

//---------------------------------------------------------------------------
#include "cqmcustomvagon.h"

//---------------------------------------------------------------------------
class CqmControlPoint;

//---------------------------------------------------------------------------
class CqmVagonQueue : public CqmCustomVagon
{
public:
    CqmVagonQueue(void);
    ~CqmVagonQueue(void);

    void Start(void);
    void Make(void);
    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

protected:
    CoalHeap hi;//пришедший уголь

    char coalqueue_name[MAX_NAME_LEN];//имя очереди
    int coalqueue_id;//ид очереди

    char FunctionName[MAX_NAME_LEN];//имя функции
    char Args[MAX_NAME_LEN];//строка с аргументами функции
    int fid;//ид функции

    //аргументы функции после парсинга строки Args
    int argCount;
    char* argNames[MAX_FUNC_ARGS];
    char* argValues[MAX_FUNC_ARGS];

    virtual void OnPressEov(void);
    virtual void StoreVagon(void);
    virtual int  AddVagon(void);

    CqmControlPoint * P; // Родительская точка контроля
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmVagonQueue& p);
extern istream& operator>> (istream& s, CqmVagonQueue& p);

//---------------------------------------------------------------------------
#endif
