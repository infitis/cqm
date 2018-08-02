/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmvagontripper.h

    Описание класса CqmVagon, который реализует анализ разгрузки угля
    из вагонов с помощью вагоноопрокида

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmvagontipperH
#define cqmvagontipperH

//---------------------------------------------------------------------------
#include "cqmcustomvagon.h"

//---------------------------------------------------------------------------
class CqmVagonTipper : public CqmCustomVagon
{
public:
    CqmVagonTipper(void);
    ~CqmVagonTipper(void);

    void Start(void);

    void Prepare(void);
    void MakeCoaltype(void);
    void Make(void);
    void Complete(void);

    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

protected:
    char parententity[MAX_NAME_LEN];//title name

private:
    int mp;
    double lnFp;
    Coal c;

    void OnPressEov(double part_of_coalheap);
    void StoreVagon(double part_of_coalheap);
    void AddVagon(void);
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmVagonTipper& p);
extern istream& operator>> (istream& s, CqmVagonTipper& p);

//---------------------------------------------------------------------------
#endif
