/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmfuncs.h

    Описание класса CqmFunction, который обеспечивает
    выполнение huru-скриптов

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmfuncsH
#define cqmfuncsH

//---------------------------------------------------------------------------
#include <iostream.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"

//---------------------------------------------------------------------------
class huru;

//---------------------------------------------------------------------------
#define MAX_SCRIPT_LEN 255

//---------------------------------------------------------------------------
class CqmFunction
{
  public:

    CqmFunction(void);
    ~CqmFunction(void);

    char name[MAX_NAME_LEN];
    char script[MAX_SCRIPT_LEN];
    int errors;
    char errors_msg[MAX_SCRIPT_LEN];

    void Prepare(void);
    void setScript(char* s);
    void addVariable(char* n, double val);
    double Solve(void);
    void Finish(void);

    virtual istream& Input(istream& s);     //get data from istream
    virtual ostream& Print(ostream& s);     //print to ostream

  private:

    huru* h;
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmFunction& f);
extern istream& operator>> (istream& s, CqmFunction& f);

//---------------------------------------------------------------------------
#endif
