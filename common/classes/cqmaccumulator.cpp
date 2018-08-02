//---------------------------------------------------------------------------
#include <string.h>
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmaccumulator.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmroute.h"
#include "coalheap.h"

//---------------------------------------------------------------------------
CqmAccum::CqmAccum(void)
{
    strcpy(name, "noname");
    strcpy(title, "notitle");
    inentity_id = outentity_id = NO_CQM_ENTITY;
    size = 0;
    strcpy(mytype, "ёмкость");
}

//---------------------------------------------------------------------------
CqmAccum::~CqmAccum(void)
{
}

//---------------------------------------------------------------------------
void CqmAccum::Start(void)
{
    CqmEntity::Start();
    inentity_id   = core.compute->getEntityId(inr);
    outentity_id  = core.compute->getEntityId(outr);
    h.setEmpty();
    //получить из внешнего источника
    getaccumulator(name, &h, &coaltype);
}

//---------------------------------------------------------------------------
void CqmAccum::MakeCoaltype(void)
{
    if (coaltype == NO_COALTYPE)
    {
        coaltype = core.compute->entitys[inentity_id]->getCoaltype();
    }
    else
    {
        int fcoaltype = core.compute->entitys[inentity_id]->getCoaltype();
        if (fcoaltype != coaltype)
        {
            coaltype = DEFAULT_COALTYPE;
        }
    }
}

//---------------------------------------------------------------------------
void CqmAccum::Make(void)
{
    // +/-
    h.addCoal(core.compute->entitys[inentity_id]->getCoal());
    h.subCoal(core.compute->entitys[outentity_id]->getCoal());

    if (size > 0)
    {
        if (h.c.P.val > size)
        {
            h.c.P.val = size;
        }
    }

    if (h.empty)
    {
        coaltype = NO_COALTYPE;
    }
    
    //сохранить во внешний источник
    setaccumulator(name, &h, &coaltype);

    //отладка
    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        char b[MAX_NAME_LEN] = "";
        std::strstream ss; ss<<h; ss.getline(b, MAX_NAME_LEN);
        m(b);
    }
}

//---------------------------------------------------------------------------
void CqmAccum::setEmpty()
{
    h.setEmpty();
    coaltype = NO_COALTYPE;
    //сохранить во внешний источник
    setaccumulator(name, &h, &coaltype);

    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        char db[MAX_NAME_LEN];
        sprintf(db, "accumulator %6s set empty.", title);
        msg(db);
    }
}

//---------------------------------------------------------------------------
void CqmAccum::getFormatHeap(char* s)
{
    std::strstream ss(s, MAX_NAME_LEN);
    ss<<h;
    char t[MAX_NAME_LEN];
    ss.getline(t, MAX_NAME_LEN);
    sprintf(s, "%s", t);
}

//---------------------------------------------------------------------------
void CqmAccum::setFormatHeap(char* s)
{
    std::istrstream sf(s);
    sf>>h;
    //
    h.setPa();

    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        char b[MAX_NAME_LEN] = "", db[MAX_NAME_LEN];
        std::strstream ss;
        ss<<h;
        ss.getline(b, MAX_NAME_LEN);
        sprintf(db, "accumulator %6s : set %s", title, b);
        msg(db);
    }
}

//---------------------------------------------------------------------------
istream& CqmAccum::Input(istream& s)
{
    s>>name>>title>>inr>>outr>>size;
    strcpy(what_coaltype, inr);
    return s;
}

//---------------------------------------------------------------------------
ostream& CqmAccum::Print(ostream& s)
{
    s<<name<<"\t"<<title<<"\t"<<core.compute->entitys[inentity_id]->name<<
                          "\t"<<core.compute->entitys[outentity_id]->name<<
                          "\t"<<size;
    return s;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmAccum& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmAccum& f)
{
	return f.Input(s);
}

//---------------------------------------------------------------------------

