//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ftableviewer.h"
#include "dbacts.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmroute.h"
#include "cqmdiag.h"
#include "coalheap.h"
#include "global.h"
#include "globsrv.h"
#include "fmsgs.h"
#include "fdm.h"

//---------------------------------------------------------------------------
void InitTableViewers(void)
{
    TableViewer->SetTable("calibration");
}

//---------------------------------------------------------------------------
void RefreshTableViewers(void)
{
    if (NeedRefresh)
    {
        TableViewer->RefreshGrid();
    }
}

//---------------------------------------------------------------------------
void StorePoints(void)
{
    char buf[512];
    for (int i=0; i<core.compute->PointCount; i++)
	{
        if (core.compute->points[i]->diag == D_IDLE)
        {
            continue;
        }
        sprintf(buf,
        "insert into points(moment, point, coaltype, p, a, diag) values('now', '%s', %i, %s, %s, %u)"
        ,
        core.compute->points[i]->name, core.compute->points[i]->getCoaltype(),
        core.compute->points[i]->getCoal().P.format("%4.2f"),
        core.compute->points[i]->getCoal().A.format("%4.2f"),
        core.compute->points[i]->diag);
        DoSql(AnsiString(buf));
	}
    for (int i=0; i<core.compute->RouteCount; i++)
	{
        if (core.compute->routes[i]->getCoal().empty())
        {
            continue;
        }
        sprintf(buf,
        "insert into routes(moment, route, p, a) values('now', '%s', %s, %s)"
        ,
        core.compute->routes[i]->name,
        core.compute->routes[i]->getCoal().P.format("%4.2f"),
        core.compute->routes[i]->getCoal().A.format("%4.2f") );
        DoSql(AnsiString(buf));
	}
}

//---------------------------------------------------------------------------
void getCqmCalibration(std::map<std::string, double> * m, char * point, int coaltype)
{
    if (OpenSql(AnsiString().sprintf(
    "select * from calibration where point='%s' and coaltype='%i' order by param"
    ,point, coaltype)))
    {
        std::string name;
        while(!DM->q->Eof)
        {
            name = DM->q->FieldByName("param")->AsString.c_str();
            double val = GETFIELD("val")->AsFloat;
            (*m)[name] = val;
            DM->q->Next();
        }
    }
}

//---------------------------------------------------------------------------
void setCqmCalibration(char * point, int coaltype, char * param, double val)
{
    DoSql(AnsiString().sprintf(
    "update calibration set val=%10.5f where point='%s' and coaltype=%i and param='%s'"
    , val, point, coaltype, param));
}

//---------------------------------------------------------------------------
void setAllCqmCalibration(char * point, char * param, double val)
{
    DoSql(AnsiString().sprintf(
    "update calibration set val=%10.5f where point='%s' and param='%s'"
    , val, point, param));
}

//---------------------------------------------------------------------------
int  addvagon(char* name)
{
    if (DoSql(AnsiString().sprintf(
    "insert into vagons (id, moment, vname) values(NULL, 'now', '%s')"
    , name)))
    {

        if (OpenSql("select first 1 gen_id(gen_vagons_id,0) as LID from vagons"))
        {
            return GETFIELD("LID")->AsInteger;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
int  setvagon(int id, int coaltype, double p, double a, int mp, double lnFp)
{
    if (DoSql(AnsiString().sprintf(
    "update vagons set moment='now', coaltype=%i, p=%3.1f, a=%3.1f, mp=%i, lnFp=%6.3f where id=%i"
    ,coaltype, p, a, mp, lnFp, id)))
    {
            return ROWSAFFECTED;
    }
    return -1;
}

//---------------------------------------------------------------------------
int  getvagon(int id, int* coaltype, double* p, double* a, int* mp, double* lnFp)
{
    if (OpenSql(AnsiString().sprintf(
    "select * from vagons where id=%i", id
    )))
    {
        if (EMPTYRESULT)
        {
            return 0;
        }
        else
        {
            *coaltype = GETFIELD("coaltype")->AsInteger;
            *p        = GETFIELD("p")->AsFloat;
            *a        = GETFIELD("a")->AsFloat;
            *mp       = GETFIELD("mp")->AsInteger;
            *lnFp     = GETFIELD("lnFp")->AsFloat;
        }
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------
int  getvagoncoaltype(int id, int* coaltype)
{
    if (OpenSql(AnsiString().sprintf(
    "select coaltype from vagons where id=%i", id
    )))
    {
        if (EMPTYRESULT)
        {
            return 0;
        }
        else
        {
            *coaltype = GETFIELD("coaltype")->AsInteger;
        }
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------
int  lastemptyvagon(char* name)
{
    if (OpenSql(AnsiString().sprintf(
    "select first 1 * from vagons where vname='%s' and moment <= 'now' order by moment desc",
    name
    )))
    {
        if (GETFIELD("p")->AsFloat < 0.1 && GETFIELD("p")->AsFloat < 0.1)
        {
            return GETFIELD("id")->AsInteger;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int  firstemptyvagon(char* name)
{
    if (OpenSql(AnsiString().sprintf(
    "select first 1 * from vagons where vname='%s' and p is null and a is null and mp=0 order by id"
    , name)))
    {
        if (EMPTYRESULT)
        {
            return 0;
        }
        else
        {
            return GETFIELD("id")->AsInteger;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int solvecoaltype4(int id)
{
    if (OpenSql(AnsiString().sprintf(
    "select pos, coalrank from vagons where id=%i", id
    )))
    {
        if (EMPTYRESULT)
        {
            return 0;
        }
        else
        {
            int pos_id      = GETFIELD("pos")->AsInteger;
            int coalrank_id = GETFIELD("coalrank")->AsInteger;
            if (OpenSql(AnsiString().sprintf(
            "select coaltype from get_coaltype(%d, %d)"
            , pos_id, coalrank_id
            )))
            {
                if (EMPTYRESULT)
                {
                    return 0;
                }
                else
                {
                    return GETFIELD("coaltype")->AsInteger;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}

//---------------------------------------------------------------------------
int getaccumulator(char* name, CoalHeap* h, int* coaltype)
{
    AnsiString s = AnsiString().sprintf(
    "select p,a,coaltype,empty,n from accumulators where name='%s'", name
    );
    if (OpenSql(s))
    {
        if (EMPTYRESULT) return 0;
        *coaltype = GETFIELD("coaltype")->AsInteger;
        if (GETFIELD("empty")->AsInteger)
        {
            h->setEmpty();
            return 1;
        }
        else
        {
            h->setNotEmpty();
        }
        if (GETFIELD("p")->IsNull)
        {
            h->c.P.setNull();
        }
        else
        {
            h->c.P.val = GETFIELD("p")->AsFloat;
        }
        if (GETFIELD("a")->IsNull)
        {
            h->c.A.setNull();
        }
        else
        {
            h->c.A.val = GETFIELD("a")->AsFloat;
        }
        h->n = GETFIELD("n")->AsFloat;
        //
        h->setPa();
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------
int setaccumulator(char* name, CoalHeap* h, int* coaltype)
{
    AnsiString s;
    if (h->empty)
    {
        s = AnsiString().sprintf(
        "execute procedure set_accum '%s', 0, 0, 0, %i, 1"
        ,name, NO_COALTYPE);
    }
    else
    {
        char tmpP[16], tmpA[16];
        strcpy(tmpP, h->c.P.format("%10.5f"));
        strcpy(tmpA, h->c.A.format("%10.5f"));
        s = AnsiString().sprintf(
        "execute procedure set_accum '%s', %s, %s, %10.5f, %i, 0"
        ,name, tmpP, tmpA, h->n, *coaltype);
    }

    if (DoSql(s))
    {
        return 1;
    }
    return -1;
}

//---------------------------------------------------------------------------
void FlushTables(void)
{
    DoSql("commit retain");
}

//---------------------------------------------------------------------------
#pragma package(smart_init)


