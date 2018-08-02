/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmcustomvagon.h

    Описание класса CqmCustomVagon, который описывает абстрактный вагон

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmcustomvagonH
#define cqmcustomvagonH

//---------------------------------------------------------------------------
#include <iostream.h>
#include <time.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "coalheap.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
class CqmCustomVagon : public CqmEntity
{
public:
    CqmCustomVagon(void);
    ~CqmCustomVagon(void);

    char eovsigname[MAX_NAME_LEN];//название сигнала КВ

    int id;//уникальный идентификатор вагона
    CoalHeap h;//куча с углём

    int eov;//счётчик сигналов КВ
    time_t teov;//время последенго КВ

    int pid;//номер родительской сущности

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmCustomVagon& p);
extern istream& operator>> (istream& s, CqmCustomVagon& p);

//---------------------------------------------------------------------------
#endif
