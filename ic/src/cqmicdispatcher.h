//---------------------------------------------------------------------------
#ifndef cqmicdispatcherH
#define cqmicdispatcherH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "cqmremoteobject.h"

//---------------------------------------------------------------------------
#define MAX_CQM_REMOTE_OBJECTS 32

//---------------------------------------------------------------------------
class CqmRemoteObjectShortItem
{
public:
    AnsiString Name;
    AnsiString Title;
    CqmRemoteObjectShortItem(const AnsiString AName,
                         const AnsiString ATitle);
};

//---------------------------------------------------------------------------
class CqmICDispatcher
{
public:
    CqmICDispatcher(AnsiString AIniFileName);
    ~CqmICDispatcher();

    AnsiString rasConnection;
    AnsiString rasUser;
    AnsiString rasPassword;

    AnsiString pathBackup;
    AnsiString pathCmd;
    AnsiString pathIni;

    AnsiString cmdDial;
    AnsiString cmdHang;
    AnsiString cmdUpdate;
    AnsiString cmdRestore;
    AnsiString cmdBackup;

    int cmdTimeout;

    CqmRemoteObjectShortItem* Objects[MAX_CQM_REMOTE_OBJECTS];
    int countObjects;
    int curObjectId;
    CqmRemoteObject* curObject;

    int Activate(int id);
    int DeActivate(int id);

    int Connect();
    int Disconnect();
    int Update();
    int Restore();
    int Backup();

    bool DBConnected;
    bool rasConnected;

};

//---------------------------------------------------------------------------
extern CqmICDispatcher* IC;

//---------------------------------------------------------------------------
#endif
