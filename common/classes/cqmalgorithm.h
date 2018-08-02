/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmalgorithm.h

    Описание класса CqmAlgorithm - реализация алгоритма рассчета
    нагрузки и зольности по результатам измерения дискретных и
    частотных сигналов за минуту, анализ этих сигналов, диагностика
    датчиков и источника.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmalgorithmH
#define cqmalgorithmH

//---------------------------------------------------------------------------
#include <map>
#include <string>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"

//---------------------------------------------------------------------------
#define MAX_MAKE_ORDER_STR 128
#define MAX_FA_STR         128

//---------------------------------------------------------------------------
class CqmControlPoint;

//---------------------------------------------------------------------------
class CqmAlgorithm
{
public:
    CqmAlgorithm(CqmControlPoint *Par);
    ~CqmAlgorithm(void);

    virtual void Make(void);

    int    n;//количество итераций всего
    int    k;//количество отобранных итераций для FA

    //При рабочем конвейере:

    //ВЕС
    int    mpn;//количество итераций
    int    mpL, mp, mpR, mpW;//количество итераций в каждом частотном интервале
    double Fpn;//среднее значение частоты
    double FpL, Fp, FpR, FpW;//средние значения частот по интервалам
    double Spn, SpL, Sp, SpR, SpW;//суммы средних значений частот по интервалам
    double sigmaFpn;//среднеквадратичное отклонение Fan

    //ЗОЛА
    int FA[DATA_SIZE], CONV[DATA_SIZE];
    int    man;//количество итераций
    int    maL, ma, maR, maW;//количество итераций в каждом частотном интервале
    int    laL, la, laR, laW;//количество итераций в каждом частотном интервале после чистки
    double Fan;//среднее значение частоты
    double FaL, Fa, FaR, FaW;//средние значения частот по интервалам
    double dFaL, dFa, dFaR, dFaW;//допуски средних значений частот по интервалам
    double San, SaL, Sa, SaR, SaW;//суммы средних значений частот по интервалам
    double sigmaFan;//среднеквадратичное отклонение Fan
    double dFpP;//отклонения значений
    double dFaP;//пустых конвейеров

    virtual inline double c (char * calibrname);
    virtual inline void s   (char * calibrname, double val);
    virtual inline void sall(char * calibrname, double val);

protected:
    virtual void MakeLimits(void);
    virtual void MakeAvgFP(void);
    virtual void MakeAvgFA(void);
    virtual void MakeAvgFA1(void);
    virtual void MakeAvgFA2(void);
    virtual void MakeP(void);
    virtual void MakeP0(void);
    virtual void MakeP1(void);
    virtual void MakeP2(void);
    virtual void MakeP3(void);
    virtual void MakeP4(void);
    virtual void MakeA(void);
    virtual void MakeAA(void);
    virtual void MakeAB(void);
    virtual void MakeAC(void);
    virtual void MakeAD(void);
    virtual void MakeAE(void);

    std::map<std::string, double> calibration;

    char MakeOrderStr[MAX_MAKE_ORDER_STR];
    char FADebugStr[MAX_FA_STR];

private:
    CqmControlPoint *P; //родительская точка контроля
    Coal C;
    int diag;
};

//---------------------------------------------------------------------------
bool inInterval(double what, double base, double delta);

//---------------------------------------------------------------------------
#endif
