/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmaccumulator.h

    Описание класса CqmAccum - абстракции накопительной ёмкости
    в технологической схеме объекта. Конкретные экземпляры -
    бункеры, банки, склады.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmaccumulatorH
#define cqmaccumulatorH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "coalheap.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
class CqmAccum : public CqmEntity
{
public:
    CqmAccum(void);
    ~CqmAccum(void);

    int inentity_id;
    int outentity_id;

    double size;

    CoalHeap h;

    void Start(void);
    void MakeCoaltype(void);
    void Make(void);

    void setEmpty();
    void getFormatHeap(char* s);
    void setFormatHeap(char* s);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

private:
    char inr[MAX_NAME_LEN];
    char outr[MAX_NAME_LEN];
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmAccum& f);
extern istream& operator>> (istream& s, CqmAccum& f);

//---------------------------------------------------------------------------
#endif
