//---------------------------------------------------------------------------
/*
#include <string.h>
#include <locale>
*/
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmentity.h"
#include "cqmcore.h"
#include "cqmcompute.h"

//---------------------------------------------------------------------------
CqmEntity::CqmEntity(void)
{
    strcpy(name, "cqm_entity_noname");
    strcpy(title,"cqm_entity_notitle");
    classid = NO_CLASS_ID;
    C.setempty();
    coaltype = 0;
    what_coaltype[0] = 0;
    myCoaltype = -1;
    ctpid = NO_CQM_ENTITY;
    strcpy(mytype, "entity");
    active = 0; 
}

//---------------------------------------------------------------------------
CqmEntity::~CqmEntity(void)
{
}

//---------------------------------------------------------------------------
void CqmEntity::Start(void)
{
    //определим coaltype parent из what_coaltype
    //если цифра - definedCoaltype
    int ok=1;
    for (unsigned int i=0; i<strlen(what_coaltype); i++)
    {
        if (!isdigit(what_coaltype[i]))
        {
            ok = 0;
            break;
        }
    }
    if (ok)
    {
        ctpid = NO_CQM_ENTITY;
        /*
        std::istrstream s(what_coaltype, strlen(what_coaltype));
        s >> myCoaltype;
        */
        myCoaltype = atof(what_coaltype);
        return;
    }
    myCoaltype = -1;

    //если SELF - то сущность сама в функции MakeCoaltype считает coaltype
    if (!strcmp(what_coaltype, SELF_CQM_ENTITY))
    {
        ctpid = NO_CQM_ENTITY;
        return;
    }

    //если всё не прошло - то это имя другой сущности у которой нужно брать colatype
    ctpid = core.compute->getEntityId(what_coaltype);
    if (ctpid == NO_CQM_ENTITY)
        coaltype = DEFAULT_COALTYPE;
}

//---------------------------------------------------------------------------
void CqmEntity::Stop(void)
{
}

//---------------------------------------------------------------------------
void CqmEntity::Prepare(void)
{
}

//---------------------------------------------------------------------------
void CqmEntity::Make(void)
{
}

//---------------------------------------------------------------------------
void CqmEntity::MakeCoaltype(void)
{
    if (myCoaltype >= 0)
    {
        coaltype = myCoaltype;
        return;
    }
    if (ctpid >= 0)
    {
        coaltype = core.compute->entitys[ctpid]->getCoaltype();
        return;
    }
    //coaltype = DEFAULT_COALTYPE;
}

//---------------------------------------------------------------------------
void CqmEntity::Complete(void)
{
}

//---------------------------------------------------------------------------
Coal CqmEntity::getCoal(void)
{
    return C;
}

//---------------------------------------------------------------------------
void CqmEntity::setCoal(Coal fC)
{
    C = fC;
}

//---------------------------------------------------------------------------
int CqmEntity::getCoaltype(void)
{
    return coaltype;
}

//---------------------------------------------------------------------------
void CqmEntity::m(char *t)
{
    char buf[MSG_LEN];
    sprintf(buf, "%-7s %-12s: %s", mytype, title, t);
    msg(buf);
}

//---------------------------------------------------------------------------
istream& CqmEntity::Input(istream& s)
{
    return s>>name>>title;
}

//---------------------------------------------------------------------------
ostream& CqmEntity::Print(ostream& s)
{
    return s<<name<<"\t"<<title;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmEntity& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmEntity& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

