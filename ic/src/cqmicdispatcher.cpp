//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <dialogs.hpp>
#pragma hdrstop
#include "cqmicdispatcher.h"
#include "global.h"
#include "fdm.h"
#include "fmsgs.h"
#include "cmdproc.h"

//---------------------------------------------------------------------------
CqmICDispatcher* IC;

//---------------------------------------------------------------------------
CqmRemoteObjectShortItem::CqmRemoteObjectShortItem(const AnsiString AName,
                                                   const AnsiString ATitle) :
    Name(AName), Title(ATitle)
{
}

//---------------------------------------------------------------------------
CqmICDispatcher::CqmICDispatcher(AnsiString AIniFileName)
{
    countObjects = 0;
    curObjectId = -1;
    curObject = NULL;
    DBConnected = false;
    rasConnected = false;
    cmdTimeout = 60000;

    TIniFile *ini;
    try{
        ini = new TIniFile(AIniFileName);

        //load objects
        TStringList* Names;
        try {
            Names = new TStringList;
            ini->ReadSection("objects", Names);
            for(int i=0; i<Names->Count && i<MAX_CQM_REMOTE_OBJECTS; i++)
            {
                AnsiString Value = ini->ReadString("objects", Names->Strings[i], "");
                if (Value != AnsiString(""))
                {

                    Objects[i] = new CqmRemoteObjectShortItem(Names->Strings[i],
                                                              Value);
                    countObjects++;
                }
            }
        }
        __finally
        {
            delete Names;
        }

        //load other data
        cmdTimeout    = ini->ReadInteger("ic",  "cmdtimeout", cmdTimeout);

        rasConnection = ini->ReadString("ras",  "connection", "no connection!");
        rasUser       = ini->ReadString("ras",  "user",       "no user!");
        rasPassword   = ini->ReadString("ras",  "password",   "");

        pathBackup    = ini->ReadString("paths","backup",      "");
        pathCmd       = ini->ReadString("paths","cmd",         "..\\cmd");
        pathIni       = ini->ReadString("paths","ini",         "..\\etc");

        cmdDial       = ini->ReadString("cmds","dial",         "dial.cmd");
        cmdHang       = ini->ReadString("cmds","hang",         "hang.cmd");
        cmdUpdate     = ini->ReadString("cmds","update",       "update.cmd");
        cmdRestore    = ini->ReadString("cmds","restore",      "restore.cmd");
        cmdBackup     = ini->ReadString("cmds","backup",       "backup.cmd");;

    }
    __finally
    {
        delete ini;
    }
}

//---------------------------------------------------------------------------
CqmICDispatcher::~CqmICDispatcher()
{
    for (int i=0; i<countObjects; i++)
    {
        delete Objects[i];
    }

    if (curObject != NULL)
        delete curObject;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Activate(int id)
{
    curObject = new CqmRemoteObject(pathIni+"\\"+Objects[id]->Name+".ini");
    if (!curObject->ready)
    {
        DeActivate(id);
        return 0;
    }
    curObjectId = id;
    ConnectionDataBase = curObject->Name;
    try
    {
        ConnectToDb();
    }
    catch(Exception &exception)
    {
        DoMsg("CqmICDispatcher::Activate : "+curObject->Title+" : "
              +exception.Message);
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::DeActivate(int id)
{
    Disconnect();
    DisconnectFromDb();
    delete curObject;
    curObjectId = -1;
    curObject = NULL;
    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Connect()
{
    if (rasConnected)
        return 1;
    AnsiString Params = "\""+ curObject->Title+"\" "
                       +rasConnection+" "+rasUser+" "+rasPassword+" "
                       +curObject->PhoneNumber;
    DoMsg("CqmICDispatcher::Connect : "+curObject->Title+" : попытка установить соединение.");
    int exitCode = CmdProc("МКУ Инфоцентр", pathCmd+"\\"+cmdDial, Params, cmdTimeout);
    if (exitCode != 0)
    {
        DoMsg("CqmICDispatcher::Connect : "+curObject->Title
             +" : соединение не установлено, код ошибки: "+IntToStr(exitCode));
        return 0;
    }
    rasConnected = true;
    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Disconnect()
{
    if (!rasConnected)
        return 1;
    AnsiString Params = "\""+ curObject->Title+"\" "+rasConnection;
    DoMsg("CqmICDispatcher::Disconnect : "+curObject->Title+" : попытка разорвать соединение.");
    int exitCode = CmdProc("МКУ Инфоцентр", pathCmd+"\\"+cmdHang, Params, cmdTimeout);
    if (exitCode != 0)
    {
        DoMsg("CqmICDispatcher::Disconnect : "+curObject->Title
             +" : соединение не разорвано, код ошибки: "+IntToStr(exitCode));
        return 0;
    }
    rasConnected = false;
    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Update()
{
    if (!Connect())
        return 0;

    AnsiString Params = "\""+ curObject->Title+"\" "
                      + curObject->IPAddress + " "
                      + curObject->Name + " "
                      + curObject->DBUser + " "
                      + FormatDateTimeToDB(curObject->LastUpdate, 2) + " "
                      + curObject->DBPassword;
    TDateTime BeginUpdate = Now();
    DoMsg("CqmICDispatcher::Update : "+curObject->Title+" : попытка обновить базу данных.");
    int exitCode = CmdProc("МКУ Инфоцентр", pathCmd+"\\"+cmdUpdate, Params, cmdTimeout);

    if (exitCode != 0)
    {
        DoMsg("CqmICDispatcher::Update : "+curObject->Title
             +" : обновление не удалось, код ошибки: "+IntToStr(exitCode));
        return 0;
    }

    curObject->LastUpdate = BeginUpdate-(1.0/24/60*3);

    if (!Disconnect())
        return 0;

    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Restore()
{
    if (curObject == NULL)
        return 0;
    TOpenDialog *OD = new TOpenDialog(Application);
    try
    {
        OD->Filter = "Sql files|*.sql;*.sql.gz|Any file|*.*";
        OD->InitialDir = pathBackup;
        OD->Options << ofNoChangeDir;
        if (OD->Execute())
        {
            AnsiString Params = "\""+ curObject->Title+"\" "
                               +OD->FileName;
            DoMsg("CqmICDispatcher::Restore : "+curObject->Title+" : попытка выполнить sql-скрипт.");
            int exitCode = CmdProc("МКУ Инфоцентр", pathCmd+"\\"+cmdRestore, Params, cmdTimeout);
            if (exitCode != 0)
            {
                DoMsg("CqmICDispatcher::Restore : "+curObject->Title
                     +" : sql-скрипт не выплолнен, код ошибки: "+IntToStr(exitCode));
                return 0;
            }
        }
    }
    __finally
    {
        delete OD;
    }
    return 1;
}

//---------------------------------------------------------------------------
int CqmICDispatcher::Backup()
{
    if (curObject == NULL)
        return 0;

    AnsiString Params = "\""+ curObject->Title+"\" "
                       +curObject->Name + " "
                       +pathBackup;
    DoMsg("CqmICDispatcher::Backup : "+curObject->Title+" : попытка сделать резервную копию базы данных.");
    int exitCode = CmdProc("МКУ Инфоцентр", pathCmd+"\\"+cmdBackup, Params, cmdTimeout);
    if (exitCode != 0)
    {
        DoMsg("CqmICDispatcher::Backup : "+curObject->Title
             +" : резервирование не выплолнено, код ошибки: "+IntToStr(exitCode));
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
