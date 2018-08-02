//---------------------------------------------------------------------------
#include <ctype>
#include <stdexcept>

//---------------------------------------------------------------------------
#include "cqmcompute.h"
#include "ctrlpntclass.h"
#include "ioclass.h"
#include "signals.h"
#include "cqmcore.h"
#include "cqmstreamparse.h"
#include "cqmentity.h"
//points
#include "cqmpoint.h"
#include "cqmpoint003.h"
#include "cqmpointg.h"
//vagons
#include "cqmvagon.h"
#include "cqmvagon_cn.h"
#include "cqmvagontipper.h"
#include "cqmvagon_q.h"
//functions
#include "cqmfuncs.h"
//traffics
#include "cqmtraffic.h"
//routes
#include "cqmroute.h"
//accumulators
#include "cqmaccumulator.h"
//stacks
#include "cqmcoalqueue.h"
//extesions
#include "cqmextensions.h"

//---------------------------------------------------------------------------
Compute::Compute(void)
{
    PointCount = 0;
    VagonCount = 0;
    FunctionCount = 0;
    TrafficCount = 0;
    RouteCount = 0;
    AccumulatorCount = 0;
    CoalQueueCount = 0;
    AutoexecCount = 0;
    ExtensionCount = 0;
    MakeCoaltypeCount = 0;
    EntityCount = 0;

    dataCount = 0;
}

//---------------------------------------------------------------------------
Compute::~Compute(void)
{
}

//---------------------------------------------------------------------------
void Compute::Load(const char* filename)
{
	//открыть файл
    f.open(filename);

    if (!f)
    {
		char msg[MAX_NAME_LEN] = "Can`t open file ";
		throw runtime_error(strcat(msg, filename));
    }
    while (!f.eof())
    {
        //найти раздел (points или vagons)
        //загрузить данные из раздела
        //найти другой раздел
        try{

     	char str[MAX_NAME_LEN];

        SkipSpacesAndComments(f);

        f>>str;
        if (!strcmp(str, "points"))
			LoadPoints();
        else
        if (!strcmp(str, "vagons"))
			LoadVagons();
        else
        if (!strcmp(str, "functions"))
			LoadFunctions();
        else
        if (!strcmp(str, "traffics"))
			LoadTraffics();
        else
        if (!strcmp(str, "routes"))
			LoadRoutes();
        else
        if (!strcmp(str, "accumulators"))
			LoadAccumulators();
        else
        if (!strcmp(str, "coalqueues"))
			LoadCoalQueues();
        else
        if (!strcmp(str, "makecoaltypeorder"))
			LoadMakeCoaltypeOrder();
        else
        if (!strcmp(str, "extensions"))
			LoadExtensions();
        else
        if (!strcmp(str, "autoexecs"))
			LoadAutoexecs();
        else
        if (!strcmp(str, "end"))
			break;
        }
        catch(const std::exception& e)
        {
            sprintf(exctext, "in Compute::Load , what: %s", e.what());
            msg(exctext);
            throw runtime_error(exctext);
        }
    }
    //закрыть файл
    f.close();

}

//---------------------------------------------------------------------------
int Compute::LoadPoints(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];
    int cpc;

    CqmControlPoint * cp;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
			(f)>>cpc;
			if (f.eof())
            {
            	char msg[MAX_NAME_LEN] = "LoadPoints: a few params for device";
				throw logic_error(msg);
                //return 1;
            }
			switch (cpc)
			{
				case CQM_POINT:
                {
					cp = new CqmControlPoint();
					break;
                }
				case CQM_POINT_GENERAL:
                {
					cp = new CqmControlPointG();
					break;
                }
				case CQM_POINT_003:
                {
					cp = new CqmControlPoint003();
					break;
                }
				default:
                {
    	        	char msg[MAX_NAME_LEN] = "LoadPoints: unknown ctrlpoint class";
					throw logic_error(msg);
        	        //return 1;
                }
        	}
            f>>(*cp);
            if (PointCount < MAX_POINTS-1)
            {
                points[PointCount++] = cp;
                addEntity(cp);
            }
            else
            {
                delete cp;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadVagons(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];
    int cpc;

    CqmCustomVagon * cp;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
			(f)>>cpc;
			if (f.eof())
            {
            	char msg[MAX_NAME_LEN] = "LoadVagons: a few params for device";
				throw logic_error(msg);
                //return 1;
            }
			switch (cpc)
			{
				case CQM_VAGON:
                {
					cp = new CqmVagon();
					break;
                }
				case CQM_VAGON_CURNEXT:
                {
					cp = new CqmVagonCurNext();
					break;
                }
				case CQM_VAGON_TIPPER:
                {
					cp = new CqmVagonTipper();
					break;
                }
				case CQM_VAGON_QUEUE:
                {
					cp = new CqmVagonQueue();
					break;
                }
				default:
                {
    	        	char msg[MAX_NAME_LEN] = "LoadVagonss: unknown cqmvagon class";
					throw logic_error(msg);
        	        //return 1;
                }
        	}
            f>>(*cp);
            if (VagonCount < MAX_VAGONS-1)
            {
                vagons[VagonCount++] = cp;
                addEntity(cp);
            }
            else
            {
                delete cp;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadFunctions(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmFunction * fp;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            fp = new CqmFunction();
            f>>(*fp);
            if (FunctionCount < MAX_FUNCTIONS-1)
            {
                functions[FunctionCount++] = fp;
            }
            else
            {
                delete fp;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadRoutes(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmRoute * tp;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            tp = new CqmRoute();
            f>>(*tp);
            if (RouteCount < MAX_ROUTES-1)
            {
                routes[RouteCount++] = tp;
                addEntity(tp);
            }
            else
            {
                delete tp;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadTraffics(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmTraffic * tp;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            tp = new CqmTraffic();
            f>>(*tp);
            if (TrafficCount < MAX_TRAFFICS-1)
            {
                traffics[TrafficCount++] = tp;
                addEntity(tp);
            }
            else
            {
                delete tp;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadAccumulators(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmAccum * ap;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            ap = new CqmAccum();
            f>>(*ap);
            if (AccumulatorCount < MAX_ACCUMULATORS-1)
            {
                accumulators[AccumulatorCount++] = ap;
                addEntity(ap);
            }
            else
            {
                delete ap;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadCoalQueues(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmCoalQueue * ap;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            ap = new CqmCoalQueue();
            f>>(*ap);
            if (CoalQueueCount < MAX_COALQUEUES-1)
            {
                coalqueues[CoalQueueCount++] = ap;
                addEntity(ap);
            }
            else
            {
                delete ap;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadMakeCoaltypeOrder(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}

        int eid = getEntityId(n);

        MakeCoaltypeOrder[MakeCoaltypeCount++] = eid;
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadExtensions(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

    CqmExtension * ap;

	while(!f.eof())
    {
        SkipSpacesAndComments(f);

		(f)>>n;
		if (!strcmp(n,"end")) {return 0;}
		else
        if (!strcmp(n,"item"))
        {
            ap = new CqmExtension();
            f>>(*ap);
            if (ExtensionCount < MAX_EXTENSIONS-1)
            {
                extensions[ExtensionCount++] = ap;
                addEntity(ap);
            }
            else
            {
                delete ap;
            }
		}
        else
        {
        	//unknown tag
        }
    }
	return 0;
}

//---------------------------------------------------------------------------
int Compute::LoadAutoexecs(void)
{
	//временные переменные дл€ считывани€ из потока
    char n[MAX_NAME_LEN];

	while(!f.eof())
    {
        SkipSpacesAndComments(f);
		f.getline(n, MAX_NAME_LEN);
		if (!strcmp(n,"end")) {return 0;}
		else
        {
            if (AutoexecCount < MAX_AUTOEXECS-1)
            {
                strcpy(autoexecs[AutoexecCount++], n);
            }
		}
    }
	return 0;
}

//---------------------------------------------------------------------------
void Compute::addEntity(CqmEntity* e)
{
    entitys[EntityCount++] = e;
}

//---------------------------------------------------------------------------
void Compute::Clear(void)
{
    //очистим сущности
	for (int i=0; i<EntityCount; i++)
	{
		delete entitys[i];
    }

    PointCount = 0;
    VagonCount = 0;
    TrafficCount = 0;
    RouteCount = 0;
    AccumulatorCount = 0;
    CoalQueueCount = 0;
    EntityCount = 0;
    ExtensionCount = 0;

    MakeCoaltypeCount = 0;

    //очистим функции
	for (int i=0; i<FunctionCount; i++)
	{
		delete functions[i];
    }
    FunctionCount = 0;

    AutoexecCount = 0;
}

//---------------------------------------------------------------------------
void Compute::StartCompute(void)
{
    //переменные €дра по умолчанию
    core.setvar("debug", 0);
    core.setvar("minteov", 180);
    core.setvar("eov", 1);

    dataCount = 0;
    ClearSignals();

    try{

    for (int i=0; i<EntityCount; i++)
    {
        entitys[i]->Start();
    }

    //AutoEcexs
    if (AutoexecCount)
    {
        msg("јвтокоманды:");
    }
    for (int i=0; i<AutoexecCount; i++)
    {
        msg(autoexecs[i]);
        char a[MAX_NAME_LEN];
        core.execute(autoexecs[i], a);
        msg(a);
    }

    }
    catch(const std::exception& e)
    {
        sprintf(exctext, "in Compute::Start , what: %s", e.what());
        msg(exctext);
        throw runtime_error(exctext);
    }
}

//---------------------------------------------------------------------------
void Compute::StopCompute (void)
{
    for (int i=0; i<EntityCount; i++)
    {
        entitys[i]->Stop();
    }
}

//---------------------------------------------------------------------------
void Compute::FillSignals(Signal** sigs, int SignalCount)
{

    if (dataCount >= DATA_SIZE) return;

    for (int i=0; i<SignalCount; i++)
	{
        s[dataCount][string(sigs[i]->name)] = sigs[i]->data;
	}

    dataCount++;
}

//---------------------------------------------------------------------------
void Compute::ClearSignals(void)
{
    dataCount = 0;
}

//---------------------------------------------------------------------------
void Compute::ProcessSignals(Signal** sigs, int SignalCount)
{
    for (int i=0; i<SignalCount; i++)
	{
        sigs[i]->result = 0;
        switch (sigs[i]->method)
        {
            //----------------------
            case METHOD_NONE:
            {
                break;
            }
            //----------------------
            case METHOD_WAS_0:
            {
                sigs[i]->result = 1;
                for (int j=0; j<dataCount; j++)
                {
                    if (s[j][string(sigs[i]->name)] == 0)
                    {
                        sigs[i]->result = 0;
                        break;
                    }
                }
                break;
            }
            //----------------------
            case METHOD_WAS_1:
            {
                for (int j=0; j<dataCount; j++)
                {
                    if (s[j][string(sigs[i]->name)] == 1)
                    {
                        sigs[i]->result = 1;
                        break;
                    }
                }
                break;
            }
            //----------------------
            case METHOD_MAJOR:
            {
                int d0=0, d1=0;
                for (int j=0; j<dataCount; j++)
                {
                    if (s[j][string(sigs[i]->name)] == 0)
                    {
                        d0++;
                    }
                    else
                    {
                        d1++;
                    }
                }
                if (d1 >= d0)
                {
                    sigs[i]->result = 1;
                }
                break;
            }

            //----------------------
            case METHOD_5ZEROS:
            {
                int d0=0;
                int prevd=0;
                for (int j=0; j<dataCount; j++)
                {
                    if (s[j][string(sigs[i]->name)] == 0)
                    {
                        if (prevd == 0)
                        {
                            d0++;
                        }
                    }
                    else if (d0 < 4)
                    {
                        d0 = 0;
                    }
                    prevd = s[j][string(sigs[i]->name)];
                }
                if (d0 >= 4)
                {
                    sigs[i]->result = 1;
                }
                else
                {
                    sigs[i]->result = 0;
                }
                break;
            }

            //----------------------
            default:
            {
                break;
            }
        }
	}
}

//---------------------------------------------------------------------------
void Compute::Make(void)
{
    if ((core.vi("debug") & CORE_DEBUG_ALGO) ||  (core.vi("debug") & CORE_DEBUG_ENTITYS))
    {
        msg("");
    }


    for (int i=0; i<EntityCount; i++)
    {
        try {
            entitys[i]->Prepare();
        }
        catch(const std::exception& e)
        {
            sprintf(exctext, "in Compute::Make on entity->Prepare exception, entity: %s, what: %s",
            entitys[i]->name, e.what());
            msg(exctext);
        }
    }

    for (int i=0; i<MakeCoaltypeCount; i++)
    {
        try {
            entitys[MakeCoaltypeOrder[i]]->MakeCoaltype();
        }
        catch(const std::exception& e)
        {
            sprintf(exctext, "in Compute::Make on entity->MakeCoaltype exception, entity: %s, what: %s",
            entitys[i]->name, e.what());
            msg(exctext);
        }
    }

    for (int i=0; i<EntityCount; i++)
    {
        try {
            entitys[i]->Make();
        }
        catch(const std::exception& e)
        {
            sprintf(exctext, "in Compute::Make on entity->Make exception, entity: %s, what: %s",
            entitys[i]->name, e.what());
            msg(exctext);
        }
    }
    for (int i=0; i<EntityCount; i++)
    {
        try {
            entitys[i]->Complete();
        }
        catch(const std::exception& e)
        {
            sprintf(exctext, "in Compute::Make on entity->Complete exception, entity: %s, what: %s",
            entitys[i]->name, e.what());
            msg(exctext);
        }
    }

    ClearSignals();
}

//---------------------------------------------------------------------------
int Compute::getEntityId(char* name)
{
    for (int i=0; i<EntityCount; i++)
    {
    	if (!strcmp(name, entitys[i]->name))
        {
            return i;
        }
    }

	//Ќет такой сущности
    sprintf(exctext, "can`t find entity id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getPointId(char* name)
{
    for (int i=0; i<PointCount; i++)
    {
    	if (!strcmp(name, points[i]->name))
        {
            return i;
        }
    }

	//Ќет такой точки контрол€
    sprintf(exctext, "can`t find point id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getFunctionId(char* name)
{
    for (int i=0; i<FunctionCount; i++)
    {
    	if (!strcmp(name, functions[i]->name))
        {
            return i;
        }
    }

	//Ќет такой точки контрол€
    sprintf(exctext, "can`t find function id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getTrafficId(char* name)
{
    for (int i=0; i<TrafficCount; i++)
    {
    	if (!strcmp(name, traffics[i]->name))
        {
            return i;
        }
    }

	//Ќет такой точки контрол€
    sprintf(exctext, "can`t find traffic id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getRouteId(char* name)
{
    for (int i=0; i<RouteCount; i++)
    {
    	if (!strcmp(name, routes[i]->name))
        {
            return i;
        }
    }

	//Ќет такой точки контрол€
    sprintf(exctext, "can`t find route id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getAccumulatorId(char* name)
{
    for (int i=0; i<AccumulatorCount; i++)
    {
    	if (!strcmp(name, accumulators[i]->name))
        {
            return i;
        }
    }

	//Ќет такой точки контрол€
    sprintf(exctext, "can`t find accumulator id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getCoalQueueId(char* name)
{
    for (int i=0; i<CoalQueueCount; i++)
    {
    	if (!strcmp(name, coalqueues[i]->name))
        {
            return i;
        }
    }

	//Ќет такого стэка
    sprintf(exctext, "can`t find coalqueue id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------
int Compute::getExtensionId(char* name)
{
    for (int i=0; i<ExtensionCount; i++)
    {
    	if (!strcmp(name, extensions[i]->name))
        {
            return i;
        }
    }

	//Ќет такого стэка
    sprintf(exctext, "can`t find extension id for name: %s", name);
    throw std::runtime_error(exctext);
}

//---------------------------------------------------------------------------

