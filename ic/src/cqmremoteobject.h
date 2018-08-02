//---------------------------------------------------------------------------
#ifndef cqmremoteobjectH
#define cqmremoteobjectH

#include <vcl.h>
#pragma hdrstop

#include <time.h>

//---------------------------------------------------------------------------
class CqmRemoteObject
{
public:
    CqmRemoteObject(AnsiString AIniFileName);
    ~CqmRemoteObject();

    bool ready;

    AnsiString Name;
    AnsiString Title;
    AnsiString ClientData;
    TDateTime  LastUpdate;
    AnsiString PhoneNumber;
    AnsiString IPAddress;
    int        DBPort;
    AnsiString DBUser;
    AnsiString DBPassword;
    AnsiString IniFileName;

protected:
    TDateTime  oriLastUpdate;
    int LoadIni();
    int SaveIni();

};

//---------------------------------------------------------------------------
#endif
