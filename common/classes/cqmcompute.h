/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmcompute.h

    Описание класса Compute, который осуществляет начальную загрузку
    описания сущностей из входного потока, их иницализацию, содержит
    указатели на все сущности; накапливает значения сигналов за минуту,
    подготавливает и запускает процесс обработки сигналов.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmcomputeH
#define cqmcomputeH

//---------------------------------------------------------------------------
#include <fstream.h>
#include <exception>

//---------------------------------------------------------------------------
#include "cqmsys.h"

//---------------------------------------------------------------------------
class Signal;
class CqmEntity;
class CqmControlPoint;
class CqmCustomVagon;
class CqmFunction;
class CqmTraffic;
class CqmRoute;
class CqmAccum;
class CqmCoalQueue;
class CqmExtension;

//---------------------------------------------------------------------------
#define MAX_ENTITYS     144
//                       --
#define MAX_POINTS       16
#define MAX_VAGONS       16
#define MAX_FUNCTIONS    16
#define MAX_TRAFFICS     16
#define MAX_ROUTES       16
#define MAX_ACCUMULATORS 16
#define MAX_COALQUEUES   16
#define MAX_AUTOEXECS    16
#define MAX_EXTENSIONS   16

//---------------------------------------------------------------------------
class Compute
{
public:
	Compute(void);
    ~Compute(void);

    char name[MAX_NAME_LEN];

    CqmEntity* entitys[MAX_ENTITYS];//Массив с указателями на все сущности
    int EntityCount;//Количество сущностей

    CqmControlPoint* points[MAX_POINTS];//Массив с указателями на точки контроля
    int PointCount;//Количество точек контроля

    CqmCustomVagon* vagons[MAX_VAGONS];//Массив с указателями на вагоны
    int VagonCount;//Количество вагонов

    CqmFunction*  functions[MAX_FUNCTIONS];//Массив с указателями на функции
    int FunctionCount;//Количество функций

    CqmTraffic* traffics[MAX_TRAFFICS];//Массив с указателями
    int TrafficCount;//Количество

    CqmRoute* routes[MAX_TRAFFICS];//Массив с указателями
    int RouteCount;//Количество

    CqmAccum* accumulators[MAX_ACCUMULATORS];//Массив с указателями
    int AccumulatorCount;//Количество

    CqmCoalQueue* coalqueues[MAX_COALQUEUES];//Массив с указателями
    int CoalQueueCount;//Количество

    CqmExtension* extensions[MAX_EXTENSIONS];//Массив с указателями
    int ExtensionCount;//Количество

    //порядок вызова MakeCoaltype для сущностей
    int MakeCoaltypeOrder[MAX_ENTITYS];
    int MakeCoaltypeCount;

    //autoexec command
    char autoexecs[MAX_AUTOEXECS][MAX_NAME_LEN];
    int AutoexecCount;

    //номер по названию
    int getEntityId     (char* name);
    int getPointId      (char* name);
    int getFunctionId   (char* name);
    int getTrafficId    (char* name);
    int getRouteId      (char* name);
    int getAccumulatorId(char* name);
    int getCoalQueueId  (char* name);
    int getExtensionId  (char* name);

    void Load(const char* filename);//load control points data from stream
    void Clear(void);

    void StartCompute(void);//start point function before compute
    void StopCompute (void);//stop  point function after compute


    int dataCount;//count of time interval where setting signals
    NamedData s[DATA_SIZE];

    void FillSignals(Signal** sigs, int SignalCount);//Set signals data for each control point
    void ProcessSignals(Signal** sigs, int SignalCount);//process signals with own method
    void ClearSignals(void);

    void Make(void);

private:
	std::ifstream f;

    int LoadPoints(void);
    int LoadVagons(void);
    int LoadFunctions(void);
    int LoadTraffics(void);
    int LoadRoutes(void);
    int LoadAccumulators(void);
    int LoadCoalQueues(void);
    int LoadMakeCoaltypeOrder(void);
    int LoadExtensions(void);
    int LoadAutoexecs(void);
    void addEntity(CqmEntity* e);

    char exctext[1023];//для сообщение при исключениях

};

//---------------------------------------------------------------------------
#endif
