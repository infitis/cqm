//---------------------------------------------------------------------------
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmvagontipper.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h" 

//---------------------------------------------------------------------------
CqmVagonTipper::CqmVagonTipper(void) : CqmCustomVagon()
{
    classid = CQM_VAGON_TIPPER;
    strcpy(mytype, "вагоны");
}

//---------------------------------------------------------------------------
CqmVagonTipper::~CqmVagonTipper(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonTipper::Start(void)
{
    CqmCustomVagon::Start();
    pid = core.compute->getEntityId(parententity);

    AddVagon();
}

//---------------------------------------------------------------------------
void CqmVagonTipper::Prepare(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonTipper::MakeCoaltype(void)
{
    CqmEntity::MakeCoaltype();
    if (coaltype == -1)
    {
        coaltype = solvecoaltype4(id);
    }
}

//---------------------------------------------------------------------------
void CqmVagonTipper::Make(void)
{
    c = core.compute->entitys[pid]->getCoal();
    double v_tick = 0;//сколько интервалов в текущей минуте принадлежит текущему вагону

    for (int i=0; i<core.compute->dataCount; i++)
    {
        v_tick++;

        //проверим кв
        if (eov == core.vi("eov") && core.compute->s[i][eovsigname])
        {
          //OnPressEov(v_tick/core.compute->dataCount);
            OnPressEov(1);
            v_tick = 0;
            StoreVagon(0);
            return;
        }

        if (core.compute->s[i][eovsigname])
            eov++;
        else
            eov = 0;
    }

    StoreVagon(v_tick/core.compute->dataCount);
}

//---------------------------------------------------------------------------
void CqmVagonTipper::Complete(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonTipper::Stop(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonTipper::OnPressEov(double part_of_coalheap)
{
    time_t now = time(0);
    if (now-teov >= core.vi("minteov"))
    {
        teov = now;
        sprintf(debugstr, "КВ. доля = %6.3f", part_of_coalheap);
        m(debugstr);
        StoreVagon(part_of_coalheap);
        AddVagon();
    }
}


//---------------------------------------------------------------------------
void CqmVagonTipper::StoreVagon(double part_of_coalheap)
{
    Coal newc;

    if (c.P.val == 0 || c.P.isNull || part_of_coalheap < 0.034)
    {
        newc.setempty();
    }
    else
    {
        newc = c;
        newc.P.val *= part_of_coalheap;
    }

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"id    :"<<id<<endl<<"было__:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"плюс__:"<<newc;
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }

    if (!newc.empty())
    {
        h.addCoal(newc);
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
        ss<<"стало_:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }

    setvagon(id, coaltype, h.c.P.val, h.c.A.val, 1, 1);
}

//---------------------------------------------------------------------------
void CqmVagonTipper::AddVagon(void)
{
    h.setEmpty();
    coaltype = -1;

    id = firstemptyvagon(name);

    if (id)
    {
        //есть такой пустой вагон
        int ok = getvagoncoaltype(id, &coaltype);

        if (ok)
        {
            if (coaltype == -1)
            coaltype = solvecoaltype4(id);
        }
        else
        {
            sprintf(debugstr, "Отсутствует вагон: id=%i.", id);
            m(debugstr);
        }
    }
    else
    {
        //нет пустого вагона
        id = addvagon(name);
        coaltype = 0;
        h.setEmpty();
        sprintf(debugstr, "Пустой вагон не найден, вставлен новый: id=%i.", id);
        m(debugstr);
    }
}

//---------------------------------------------------------------------------
istream& CqmVagonTipper::Input(istream& s)
{
    CqmCustomVagon::Input(s);
    return s>>parententity>>what_coaltype>>eovsigname;
}

//---------------------------------------------------------------------------
ostream& CqmVagonTipper::Print(ostream& s)
{
    CqmCustomVagon::Print(s);
    return s<<"\t"<<parententity<<"\t"<<what_coaltype
            <<"\t"<<eovsigname;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmVagonTipper& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmVagonTipper& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

