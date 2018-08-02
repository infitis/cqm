/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmextensions.h

    Описание класса CqmExtension, который обеспечивает
    выполнение внешних расширений.
    Реализация системно-зависимая.

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmextensionsH
#define cqmextensionsH

//---------------------------------------------------------------------------
#include <iostream.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmentity.h"
#include "cqmextension_def.h"

//---------------------------------------------------------------------------
class CqmExtension : public CqmEntity
{
public:

    CqmExtension(void);
    ~CqmExtension(void);

    char path[MAX_NAME_LEN];
    char proc[MAX_NAME_LEN];
    int  loaded;

    void Start(void);
    void Make(void);
    void Stop(void);

    virtual istream& Input(istream& s);     //get data from istream
    virtual ostream& Print(ostream& s);     //print to ostream

    private:
#ifdef CQM_ON_WINDOWS
    HMODULE hModule;
    H_CQM_EXTENSION_START_PROC hStartProc;
    H_CQM_EXTENSION_STOP_PROC  hStopProc;
    H_CQM_EXTENSION_PROC       hProc;

    inline void GetProcs(void);
#endif
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmExtension& f);
extern istream& operator>> (istream& s, CqmExtension& f);
//---------------------------------------------------------------------------
#endif
