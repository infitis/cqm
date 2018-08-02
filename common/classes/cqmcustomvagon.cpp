//---------------------------------------------------------------------------
#include "cqmcustomvagon.h"
#include "ctrlpntclass.h"

//---------------------------------------------------------------------------
CqmCustomVagon::CqmCustomVagon(void) : CqmEntity()
{
    classid = CQM_CUSTOM_VAGON;
    strcpy(name, "noname");
    strcpy(title, "notitle");
    strcpy(eovsigname, "noeovsignal");
    pid = NO_CQM_ENTITY;
    active = 0;
    eov = 0;
}

//---------------------------------------------------------------------------
CqmCustomVagon::~CqmCustomVagon(void)
{
}

//---------------------------------------------------------------------------
istream& CqmCustomVagon::Input(istream& s)
{
    return s>>name>>title;
}

//---------------------------------------------------------------------------
ostream& CqmCustomVagon::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmCustomVagon& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmCustomVagon& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------
 
