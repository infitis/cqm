//---------------------------------------------------------------------------
#include <strstream>
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmroute.h"
#include "cqmtraffic.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmstreamparse.h"
#include "cqmfuncs.h"
#include "coalheap.h"

//---------------------------------------------------------------------------
CqmRoute::CqmRoute() : CqmEntity()
{
    strcpy(name, "noname");
    strcpy(title, "notitle");
    swCount = 0;
    coaltype = -1;
    strcpy(mytype, "маршрут");
}

//---------------------------------------------------------------------------
CqmRoute::~CqmRoute()
{
}

//---------------------------------------------------------------------------
void CqmRoute::Start(void)
{
    //!!!
    //действия по созданию динамических объектов
    //происходят в Input
    //
}

//---------------------------------------------------------------------------
void CqmRoute::Stop(void)
{
    for (int i=0; i<swCount; i++)
    {
        for (int j=0; j<sw[i].argCount; j++)
        {
            delete[] sw[i].argNames[j];
            delete[] sw[i].argValues[j];
        }
    }
    swCount = 0;

    CqmEntity::Stop();
}

//---------------------------------------------------------------------------
void CqmRoute::MakeCoaltype(void)
{
    CqmEntity::MakeCoaltype();

    bool known_coaltype = false;
    for (int i=0; i<swCount; i++)
    {
        //посчитаем coaltype
        if (core.compute->entitys[sw[i].eid]->active > 0)
        {
            int fcoaltype = core.compute->entitys[sw[i].eid]->getCoaltype();
            if (!known_coaltype)
            {
                coaltype = fcoaltype;
                known_coaltype = true;
                continue;
            }
            if (fcoaltype != coaltype)
                coaltype = DEFAULT_COALTYPE;
        }
    }
    if (!known_coaltype)
    {
        coaltype = DEFAULT_COALTYPE;
    }
}

//---------------------------------------------------------------------------
void CqmRoute::Make(void)
{
    double part;
    CoalHeap h;
    h.setEmpty();
    active = 0;
    for (int i=0; i<swCount; i++)
    {
        //подготовим переменные
        core.compute->functions[sw[i].fid]->Prepare();
        for (int j=0; j<sw[i].argCount; j++)
        {
            char*  var = sw[i].argNames[j];
            int aeid = core.compute->getEntityId(sw[i].argValues[j]);
            double val = core.compute->entitys[aeid]->active;
            core.compute->functions[sw[i].fid]->addVariable(var, val);
        }
        //посчитаем
        part = core.compute->functions[sw[i].fid]->Solve();
        core.compute->functions[sw[i].fid]->Finish();

        if (part > 0)
        {
            Coal c;
            c = core.compute->entitys[sw[i].eid]->getCoal();
            c.P.val *= part;
            if (sw[i].sign == SW_DIVIDER_MINUS)
            {
                h.subCoal(c);
            }
            else //SW_DIVIDER_PLUS
            {
                h.addCoal(c);
            }
        }

        if (core.compute->entitys[sw[i].eid]->active > 0)
        {
            active += part;
        }
    }
    if (h.empty)
    {
        C.setempty();
    }
    else
    {
        C = h.c;
    }
    //debug
    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        char b[MAX_NAME_LEN] = "", db[MAX_NAME_LEN];
        strstream ss; ss<<C;
        ss.getline(b, MAX_NAME_LEN);
        sprintf(db, "%4.3f %s", active, b);
        m(db);
    }
}

//---------------------------------------------------------------------------
void CqmRoute::InitArgs(int& count, char* b)
{
    sw[count].argCount = 0;
    if (strlen(b) == 0)
    {
        return;
    }
    std::istrstream* s = new istrstream(b);
    while (!s->eof() && count<MAX_FUNC_ARGS)
    {
        char * var = new char[MAX_NAME_LEN];
        char * val = new char[MAX_NAME_LEN];
        GetPair((*s), MAX_NAME_LEN, var, val, '=');
        sw[count].argNames[sw[count].argCount] = var;
        sw[count].argValues[sw[count].argCount] = val;
        sw[count].argCount++;
    }
    delete s;
}

//---------------------------------------------------------------------------
istream& CqmRoute::Input(istream& s)
{
    char buf[MAX_NAME_LEN];
    char c;
    char my_sign = SW_DIVIDER_PLUS;
    bool ready = false;
    s>>name>>title>>what_coaltype;
    do
    {
        sw[swCount].sign = my_sign;
        SkipSpacesAndComments(s);
        s>>buf;
        sw[swCount].eid = core.compute->getEntityId(buf);
        s>>buf;
        sw[swCount].fid = core.compute->getFunctionId(buf);
        GetQuote(s, buf, MAX_NAME_LEN, '(', ')');
        InitArgs(swCount, buf);
        swCount++;
        if (swCount == MAX_SOURCE_WARES)
        {
            ready = true;
        }

        SkipSpacesAndComments(s);
        s.get(c);
        if (c == SW_DIVIDER_PLUS || c == SW_DIVIDER_MINUS)
        {
            my_sign = c;
        }
        else
        {
            ready = true;
            s.putback(c);
        }
    }
    while (!ready);
    return s;
}

//---------------------------------------------------------------------------
ostream& CqmRoute::Print(ostream& s)
{
    s<<name<<"\t"<<title<<"\t"<<what_coaltype<<"\t";
    for (int i=0; i<swCount; i++)
    {
        s<<core.compute->entitys[sw[i].eid]->name<<"\t"
         <<core.compute->functions[sw[i].fid]->name<<"\t"
         <<"(";
        for (int j=0; j<sw[i].argCount; j++)
        {
           s<<sw[i].argNames[j]<<"="<<sw[i].argValues[j]<<" ";
        }
        s<<")";
        if (i != swCount-1)
        {
           s<<" + ";
        }
    }
    return s;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmRoute& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmRoute& f)
{
	return f.Input(s);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
