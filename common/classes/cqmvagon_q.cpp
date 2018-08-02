//---------------------------------------------------------------------------
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmvagon_q.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmstreamparse.h"
#include "cqmfuncs.h"
#include "cqmcoalqueue.h"

//---------------------------------------------------------------------------
CqmVagonQueue::CqmVagonQueue(void) : CqmCustomVagon()
{
    classid = CQM_VAGON_QUEUE;
    strcpy(coalqueue_name, "noqueue");
    strcpy(mytype, "вагоны");

    coalqueue_name[0] = 0;
    coalqueue_id = NO_CQM_ENTITY;

    FunctionName[0] = 0;
    Args[0] = 0;
    argCount = 0;
    fid = NO_CQM_ENTITY;

    coaltype = DEFAULT_COALTYPE;
}

//---------------------------------------------------------------------------
CqmVagonQueue::~CqmVagonQueue(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonQueue::Start(void)
{
    CqmCustomVagon::Start();

    fid = core.compute->getFunctionId(FunctionName);
    coalqueue_id = core.compute->getCoalQueueId(coalqueue_name);

    std::istrstream* s = new istrstream(Args);
    argCount = 0;
    while (!s->eof() && argCount<MAX_FUNC_ARGS)
    {
        char * var = new char[MAX_NAME_LEN];
        char * val = new char[MAX_NAME_LEN];
        GetPair((*s), MAX_NAME_LEN, var, val, '=');
        argNames[argCount] = var;
        argValues[argCount] = val;
        argCount++;
    }
    delete s;

    id = lastemptyvagon(name);
    if (id == 0)
    {
        sprintf(debugstr, "Последний вагон не пустой.", id);
        m(debugstr);
        id = AddVagon();
    }
    else
    {
        sprintf(debugstr, "Последний вагон пустой; Грузим в него, id=%i.", id);
        m(debugstr);
    }
}

//---------------------------------------------------------------------------
void CqmVagonQueue::Stop(void)
{
    for (int i=0; i<argCount; i++)
    {
        delete[] argNames[i];
        delete[] argValues[i];
    }

    CqmCustomVagon::Stop();
}

//---------------------------------------------------------------------------
void CqmVagonQueue::Make(void)
{
    Coal ci;
    hi.setEmpty();

    //подготоим функцию питателя
    core.compute->functions[fid]->Prepare();
    for (int i=0; i<core.compute->dataCount; i++)
    {
        //проверим, было ли питание
        for (int j=0; j<argCount; j++)
        {
            char*  var = argNames[j];
            double val = core.compute->s[i][argValues[j]];
            core.compute->functions[fid]->addVariable(var, val);
        }
        //посчитаем
        double feeder = core.compute->functions[fid]->Solve();
        if (feeder > 0)
        {
            //получим значение угля за текущий тик из источника
             ci = core.compute->coalqueues[coalqueue_id]->outputc[i];
             ci.P.val *= feeder;
        }
        else
        {
            //питатель не работал
            ci.setempty();
        }
        //проверим кв
        if (eov == core.vi("eov") && core.compute->s[i][eovsigname])
        {
            OnPressEov();
        }

        if (core.compute->s[i][eovsigname])
            eov++;
        else
            eov = 0;

        hi.addCoal(ci);
    }
    core.compute->functions[fid]->Finish();

    StoreVagon();
}

//---------------------------------------------------------------------------
void CqmVagonQueue::OnPressEov(void)
{
    time_t now = time(0);
    if (now-teov >= core.vi("minteov"))
    {
        sprintf(debugstr, "Конец Вагона; Последнее было %i сек назад.", now-teov);
        teov = now;
        m(debugstr);
        StoreVagon();
        id = AddVagon();
    }
}

//---------------------------------------------------------------------------
void CqmVagonQueue::StoreVagon(void)
{
    char t[1024] = "";
    std::strstream s(t, 1024);

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        s<<"id="<<id<<" пришло: "<<hi<<endl;
        s.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
        s<<"id="<<id<<" было  : "<<h<<endl;
        s.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }

    h.setDeltaN(hi.n);
    h.addCoal(hi.c);

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        s<<"id="<<id<<" стало : "<<h<<endl;
        s.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }

    setvagon(id, coaltype, h.c.P.val, h.c.A.val, h.n, 1);

    hi.setEmpty();
}

//---------------------------------------------------------------------------
int CqmVagonQueue::AddVagon(void)
{
    h.setEmpty();
    int thisid = addvagon(name);
    if (thisid == -1)
    {
        sprintf(debugstr, "AddVagon error: id=%i", thisid);
        m(debugstr);
    }
    else
    {
        sprintf(debugstr, "добавлен вагон: id=%i", thisid);
        m(debugstr);
    }
    return thisid;
}

//---------------------------------------------------------------------------
istream& CqmVagonQueue::Input(istream& s)
{
    s>>name>>title>>coalqueue_name>>eovsigname>>FunctionName;

    //ищем аргументы
    GetQuote(s, Args, MAX_NAME_LEN, '(', ')');

    return s;
}

//---------------------------------------------------------------------------
ostream& CqmVagonQueue::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title<<"\t"<<coalqueue_name<<"\t"
            <<eovsigname<<"\t"<<FunctionName<<" ( "<<Args<<" )";
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmVagonQueue& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmVagonQueue& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

