//---------------------------------------------------------------------------
#include "cqmpointg.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmtraffic.h"

//---------------------------------------------------------------------------
CqmControlPointG::CqmControlPointG(void) : CqmControlPoint()
{
    classid = CQM_POINT_GENERAL;
}

//---------------------------------------------------------------------------
CqmControlPointG::~CqmControlPointG(void)
{
}

//---------------------------------------------------------------------------
void CqmControlPointG::Start(void)
{
    CqmControlPoint::Start();

    if (coaltype_delay >= MAX_COALTYPE_DELAY)
        coaltype_delay = MAX_COALTYPE_DELAY - 1;
    if (coaltype_delay < 0)
        coaltype_delay = 0;
    for (int i=0; i<coaltype_delay; i++)
    {
        coaltype_stack[i] = DEFAULT_COALTYPE;
    }

    if (feeding_delay >= MAX_FEEDING_DELAY)
        feeding_delay = MAX_FEEDING_DELAY - 1;
    if (feeding_delay < 0)
        feeding_delay = 0;
    for (int i=0; i<feeding_delay; i++)
    {
        feeding_stack[i] = 0;
    }

    ftid = core.compute->getTrafficId(feeding_traffic);
}

//---------------------------------------------------------------------------
void CqmControlPointG::Stop(void)
{
    CqmControlPoint::Stop();
}

//---------------------------------------------------------------------------
void CqmControlPointG::Prepare(void)
{
    for (int i=0; i<feeding_delay; i++)
    {
        feeding_stack[i+1] = feeding_stack[i];
    }

    if (ftid >= 0)
    {
        if (core.compute->traffics[ftid]->active > 0)
            feeding_stack[0] = 1;
        else
            feeding_stack[0] = 0;
    }
    else
    {
        feeding_stack[0] = 0;
    }

    runningFeeder = feeding_stack[feeding_delay];
}

//---------------------------------------------------------------------------
void CqmControlPointG::MakeCoaltype(void)
{
    for (int i=0; i<coaltype_delay; i++)
    {
        coaltype_stack[i+1] = coaltype_stack[i];
    }

    CqmEntity::MakeCoaltype();

    coaltype_stack[0] =coaltype;
    coaltype = coaltype_stack[coaltype_delay];
}

//---------------------------------------------------------------------------
void CqmControlPointG::Make(void)
{
    CqmControlPoint::Make();
}

//---------------------------------------------------------------------------
void CqmControlPointG::Complete(void)
{
}

//---------------------------------------------------------------------------
istream& CqmControlPointG::Input(istream& s)
{
    CqmControlPoint::Input(s);
    return s>>what_coaltype>>coaltype_delay
            >>feeding_traffic>>feeding_delay;
}

//---------------------------------------------------------------------------
ostream& CqmControlPointG::Print(ostream& s)
{
    CqmControlPoint::Print(s);
    return s<<"\t"<<what_coaltype<<"\t"<<coaltype_delay
            <<"\t"<<feeding_traffic<<"\t"<<feeding_delay;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmControlPointG& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmControlPointG& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

