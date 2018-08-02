//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fdm.h"
#include "global.h"
extern void DoMsg(AnsiString);

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma link "ZConnection"
#pragma link "ZSqlMonitor"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TDM *DM;

//---------------------------------------------------------------------------
extern AnsiString LogDir;
extern AnsiString LogName;

//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
}

//---------------------------------------------------------------------------
void ConnectToDb(void)
{
    DM->db->Database    = ConnectionDataBase;
    DM->db->HostName    = ConnectionHost;
    DM->db->Port        = ConnectionPort;
    DM->db->User        = ConnectionLogin;
    DM->db->Password    = ConnectionPassword;

/*
#ifdef CQM_SERVER_APPLICATION
    DM->SqlMonitor->FileName = LogDir+"\\..\\sql\\server.sql.log";
#else
#ifdef CQM_CLIENT_APPLICATION
    DM->SqlMonitor->FileName = LogDir+"\\..\\sql\\client.sql.log";
#endif
#endif
*/
    DM->db->Connect();

    DM->SqlMonitor->FileName = LogDir+"\\..\\sql\\"+LogName+".sql.log";
    DM->SqlMonitor->Active = ConnectionSqlMonitor;
}

//---------------------------------------------------------------------------
void DisconnectFromDb(void)
{
    DM->SqlMonitor->Active = false;
    DM->db->Disconnect();
}

//---------------------------------------------------------------------------
int  DoSql(AnsiString s)
{
    try
    {
        DM->q->Close();
        DM->q->SQL->Text = s;
        DM->q->ExecSQL();
    }
    catch(Exception &e)
    {
        DoMsg("Ошибка при исполнении запроса. Sql: "+DM->q->SQL->Text+
              " | Exception: " + e.Message);
        return 0;
    }

    return 1;
}

//---------------------------------------------------------------------------
int  OpenSql(AnsiString s)
{
    try
    {
        DM->q->Close();
        DM->q->SQL->Text = s;
        DM->q->Open();
    }
    catch(Exception &e)
    {
        DoMsg("Ошибка при открытии дейтасета. SQL: "+DM->q->SQL->Text+
              " | Exception: " + e.Message);
        return 0;
    }

    return 1;
}

//---------------------------------------------------------------------------
int  LastInsertId()
{
    OpenSql("select first 1 GEN_ID(GEN_VAGONS_ID,0) as lii from vagons");
    return GETFIELD("lii")->AsInteger;
}

//---------------------------------------------------------------------------
AnsiString FormatDateTimeToDB(TDateTime s, int type)
{
    AnsiString ret;
    switch (type)
    {
        case 0: {
                    ret = FormatDateTime("yyyy-mm-dd hh:nn:ss", s);
                    break;
                }
        case 1: {
                    ret = FormatDateTime("yyyy-mm-dd", s);
                    break;
                }
        case 2: {
                    ret = FormatDateTime("yyyymmddhhnnss", s);
                    break;
                }
        default:{
                    ret = FormatDateTime("yyyy-mm-dd hh:nn:ss", s);
                    break;
                }
    }
    return ret;
}

//---------------------------------------------------------------------------
AnsiString FormatDateTimeStrToDB(AnsiString s, int type)
{
    AnsiString ret;
    switch (type)
    {
        case 0: {
                    ret = FormatDateTime("yyyy-mm-dd hh:nn:ss", StrToDateTime(s));
                    break;
                }
        default:{
                    ret = FormatDateTime("yyyy-mm-dd hh:nn:ss", StrToDateTime(s));
                    break;
                }
    }
    return ret;
}

//---------------------------------------------------------------------------
int getCoalrankData(AnsiString name, double &hhv, double &k)
{
    if (OpenSql(AnsiString().sprintf(
    "select * from coalranks where id='%s'"
    ,name.c_str() )))
    {
        if (EMPTYRESULT)
        {
            return 0;
        }
        hhv = GETFIELD("hhv")->AsFloat;
        k   = GETFIELD("k")->AsFloat;
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------


