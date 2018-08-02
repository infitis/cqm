/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmcoalqueue.h

    Описание класса CqmCoalQueue - программной абстракции конвейера,
    на котором двигается или лежит уголь.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmcoalqueueH
#define cqmcoalqueueH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"
#include "cqmentity.h"
#include "coalqueue.h"

//---------------------------------------------------------------------------
class CqmCoalQueue : public CqmEntity
{
public:
    CqmCoalQueue();
    ~CqmCoalQueue();

    void Start(void);
    void Make(void);
    void Stop(void);
    Coal getCoal(void);
    CoalHeap getCoalHeap(void);

    //выходная очередь угля
    Coal outputc[DATA_SIZE];

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

private:
    char conv_name[MAX_NAME_LEN];

    int coal_source_id;//ид источника угля
    int queue_source_id;//ид иточника, если она очередь
    int size;//размер очереди в тиках

    char coal_source_name[MAX_NAME_LEN];//имя источника угля
    char FunctionName[MAX_NAME_LEN];//имя функции
    char Args[MAX_NAME_LEN];//строка с аргументами функции
    int fid;//ид функции

    //аргументы функции после парсинга строки Args
    int argCount;
    char* argNames[MAX_FUNC_ARGS];
    char* argValues[MAX_FUNC_ARGS];

    CoalQueue* cq;//сама очередь
    int conv_worked;//количество тактов работающего конвейера

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmCoalQueue& f);
extern istream& operator>> (istream& s, CqmCoalQueue& f);

//---------------------------------------------------------------------------
#endif
