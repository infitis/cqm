//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "cqmpoint.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h"

//---------------------------------------------------------------------------
CqmControlPoint::CqmControlPoint(void) : CqmEntity()
{
    classid = CQM_POINT;
    strcpy(name, "cqmpointnoname");
    strcpy(title, "cqmpointnotitle");
    dataCount = 0;
    a = 0;
    coaltype = 0;
    diag = 0;
    runningFeeder = 0;
    strcpy(mytype, "точка");
}

//---------------------------------------------------------------------------
void CqmControlPoint::Start(void)
{
    CqmEntity::Start();

    a = new CqmAlgorithm(this);
    dataCount = &(core.compute->dataCount);
    s = core.compute->s;
}

//---------------------------------------------------------------------------
void CqmControlPoint::Stop(void)
{
    delete a;

    CqmEntity::Stop();
}

//---------------------------------------------------------------------------
void CqmControlPoint::Prepare(void)
{
    runningFeeder = 0;
}

//---------------------------------------------------------------------------
void CqmControlPoint::Make(void)
{
    if (a)
    {
        a->Make();
    }
}

//---------------------------------------------------------------------------
istream& CqmControlPoint::Input(istream& s)
{
    return s>>name>>title>>convName>>fpName>>faName;
}

//---------------------------------------------------------------------------
ostream& CqmControlPoint::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title<<"\t"
            <<convName<<"\t"<<fpName<<"\t"<<faName;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmControlPoint& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmControlPoint& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------



