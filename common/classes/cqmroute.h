/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmroute.h

    Описание класса CqmRoute - программной абстракции маршрута (направления)
    движения угольной массы по технологическим линиям объекта

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmrouteH
#define cqmrouteH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
#define MAX_SOURCE_WARES 8
#define SW_DIVIDER_PLUS  '+'
#define SW_DIVIDER_MINUS '-'

//---------------------------------------------------------------------------
typedef struct _source_ware
{
    int eid;
    int fid;
    int argCount;
    char sign;
    char* argNames[MAX_FUNC_ARGS];
    char* argValues[MAX_FUNC_ARGS];
} source_ware;

//---------------------------------------------------------------------------
class CqmRoute : public CqmEntity
{
public:
    CqmRoute();
    ~CqmRoute();

    source_ware sw[MAX_SOURCE_WARES];
    int swCount;

    void Start(void);
    void MakeCoaltype(void);
    void Make(void);
    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

private:
    void InitArgs(int& count, char* b);
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmRoute& f);
extern istream& operator>> (istream& s, CqmRoute& f);

//---------------------------------------------------------------------------
#endif
