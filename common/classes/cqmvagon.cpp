//---------------------------------------------------------------------------
#include <strstream>
#include <math.h>

//---------------------------------------------------------------------------
#include "cqmvagon.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmalgorithm.h"

//---------------------------------------------------------------------------
CqmVagon::CqmVagon(void) : CqmCustomVagon()
{
    classid = CQM_VAGON;
    strcpy(name, "noname");
    strcpy(title, "notitle");
    strcpy(pointname, "nopoint");
    strcpy(eovsigname, "noeovsignal");
    P = 0; pid = -1;
    strcpy(mytype, "вагоны");
}

//---------------------------------------------------------------------------
CqmVagon::~CqmVagon(void)
{
}

//---------------------------------------------------------------------------
void CqmVagon::Start(void)
{
    CqmCustomVagon::Start();
    pid = core.compute->getPointId(pointname);
    P = core.compute->points[pid];

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
    np = 0; F = 0; lnFp = 0;
    coaltype = -2;
}

//---------------------------------------------------------------------------
void CqmVagon::Make(void)
{
    vnp = 0;
    F=0;

    for (int i=0; i<P->a->n; i++)
    {
        if (P->s[i][P->convName] != 0)
        {
            if (P->s[i][P->fpName] >= P->a->c("Fpm"))
            {
                vnp++;
                //np++;
                F = (F*(vnp-1) + P->s[i][P->fpName]) / vnp;
            }
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
    }
    StoreVagon();
}

//---------------------------------------------------------------------------
void CqmVagon::OnPressEov(void)
{
    time_t now = time(0);
    if (now-teov >= core.vi("minteov"))
    {
        if (core.vi("debug") & CORE_DEBUG_ALGO)
            sprintf(debugstr, "Конец Вагона; Последнее было %i сек назад.", now-teov);
        teov = now;
        m(debugstr);
        StoreVagon();
        id = AddVagon();
    }
}

//---------------------------------------------------------------------------
void CqmVagon::StoreVagon(void)
{
    int mp = 0;
    double p = 0;
    /*not used*///double a = P->C.A.val;
    Coal newCoal = P->getCoal();
    Coal PCoal   = P->getCoal();
    if (PCoal.P.val == 0 || PCoal.P.isNull)
    {
        //это можно и не делать
        p = 0;
    }
    else
    {
        mp = P->a->mp + P->a->mpR;
        if (mp && vnp)
        {
            p = double(vnp) / mp * PCoal.P.val;
            if (F > 0.1 && F < 100000)
                lnFp = (lnFp*np + log(F)*vnp) / (np + vnp);
        }
        np += vnp;
    }
    newCoal.P.val = p;

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss; char tmpstr[MAX_NAME_LEN] = "";
        ss<<" прибавляем:"<<newCoal;
        ss.getline(tmpstr, MAX_NAME_LEN);
        sprintf(debugstr, "vnp=%i, mp=%i, np=%i, %s", vnp, mp, np, tmpstr);
        m(debugstr);
    }

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"до____:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }
    if (vnp > 0)
    {
        h.addCoal(newCoal);
    }
    else
    {
        if (core.vi("debug") & CORE_DEBUG_ALGO)
        {
            m("ничего не прибавили; vnp = 0.");
        }
    }

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"после_:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }
    //определим тип угля
    if (coaltype == -2)
    {
        coaltype = P->getCoaltype();
    }
    else
    if (coaltype != P->getCoaltype())
    {
        //смесь типов
        coaltype = 0/*-1*/;
    }

    setvagon(id, coaltype, h.c.P.val, h.c.A.val, np, lnFp);
}

//---------------------------------------------------------------------------
int CqmVagon::AddVagon(void)
{
    h.setEmpty();
    np = 0; F = 0; lnFp = 0;
    vnp = 0;
    coaltype = -2;
    int thisid = addvagon(name);
    if (thisid == -1)
    {
        sprintf(debugstr, "На %s addvagon error: id=%i", title, thisid);
        m(debugstr);
    }
    else
    {
        if (core.vi("debug") & CORE_DEBUG_ALGO)
            sprintf(debugstr, "На %s добавлен вагон: id=%i", title, thisid);
        m(debugstr);
    }
    return thisid;
}

//---------------------------------------------------------------------------
istream& CqmVagon::Input(istream& s)
{
    return s>>name>>title>>pointname>>eovsigname;
}

//---------------------------------------------------------------------------
ostream& CqmVagon::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title<<"\t"<<pointname<<"\t"<<eovsigname;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmVagon& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmVagon& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

