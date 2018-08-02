//---------------------------------------------------------------------------
#include "cqmpoint003.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmio.h"
#include "signals.h"

//---------------------------------------------------------------------------
CqmControlPoint003::CqmControlPoint003(void) : CqmControlPoint()
{
    classid = CQM_POINT_003;
    strcpy(name, "cqmpoint003noname");
    n_f1 = 0;
}

//---------------------------------------------------------------------------
CqmControlPoint003::~CqmControlPoint003(void)
{
    //
}

//---------------------------------------------------------------------------
void CqmControlPoint003::Start(void)
{
    CqmControlPoint::Start();

    //find our feeders
    for (int i=0; i<core.io->SignalCount; i++)
    {
        if (!strcmp(core.io->signals[i]->name, name_f1))
        {
            n_f1 = i;
        }
    }
}

//---------------------------------------------------------------------------
void CqmControlPoint003::Prepare(void)
{
    //нопедекемхе runningFeeder
    if ( core.io->signals[n_f1]->result == 1)
    {
        runningFeeder = 1;
    }
    else
    {
        runningFeeder = 0;
    }

}

//---------------------------------------------------------------------------
istream& CqmControlPoint003::Input(istream& s)
{
    return s>>name>>title>>convName>>fpName>>faName>>name_f1;
}

//---------------------------------------------------------------------------
ostream& CqmControlPoint003::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title<<"\t"
            <<convName<<"\t"<<fpName<<"\t"<<faName<<"\t"
            <<name_f1;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmControlPoint003& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmControlPoint003& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

