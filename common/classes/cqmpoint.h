/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmpoint.h

    Описание класса CqmControlPoint - программная абстракция точки котроля
    на конвейере, которая использует сигналы от конвейера, 
    от датчика нагрузки и зольности. Содержит объект, реализующий алгоритм
    обработки этих сигналов.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmpointH
#define cqmpointH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmalgorithm.h"
#include "defines.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
class CqmControlPoint : public CqmEntity
{
public:
    CqmControlPoint(void);

    CqmAlgorithm * a; // compute algorithm

    int diag;//diagnostic code

    //Признак работы питателя конвейера точки контроля
    //(нужно для точного определения что конвейер пуст)
    int runningFeeder;

    void Prepare(void);
    void Make(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

    void Start(void);
    void Stop(void);

    int* dataCount;//point to count of time interval where setting signals
    NamedData* s;//point to signals data

    char convName[MAX_NAME_LEN];//conveyor signal name
    char fpName[MAX_NAME_LEN];//weight freq signal name
    char faName[MAX_NAME_LEN];//ash freq signal name

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmControlPoint& p);
extern istream& operator>> (istream& s, CqmControlPoint& p);

//---------------------------------------------------------------------------
#endif
