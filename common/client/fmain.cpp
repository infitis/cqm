//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fmain.h"
#include "stuff.h"
#include "globcli.h"
#include "..\common\windows\fmsgs.h"
#include "..\common\windows\fclock.h"
#include "..\common\windows\fpromku.h"
#include "..\common\windows\fenterdata.h"
#include "..\common\client\rhours.h"
#include "..\common\client\rashgraph.h"
#include "..\common\client\rvagons.h"
#include "..\common\client\rpos.h"
#include "..\common\client\rmin.h"
#include "..\common\client\findic.h"
#include "..\common\client\fpositseditor.h"
#include "..\common\client\rcert.h"
#include "..\common\client\cqmnet.h"
#include "..\common\client\froutes.h"
#include "..\common\client\faccums.h"
#include "..\common\client\rintervals.h"
#include "..\common\client\rmonth.h"
#include "..\common\client\ravgash.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainF *MainF;

//---------------------------------------------------------------------------
__fastcall TMainF::TMainF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainF::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    StopActions();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::TimerTimer(TObject *Sender)
{
    static SYSTEMTIME prevst;
    SYSTEMTIME st;
    GetSystemTime(&st);
    if (st.wSecond>=2 && st.wSecond <=4 && prevst.wMinute != st.wMinute)
    {
        prevst = st;
        RefreshActions();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRefreshClick(TObject *Sender)
{
    RefreshActions();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NExitClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NWorkPositionClick(TObject *Sender)
{
    ShowWorkPosition();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NVagonsClick(TObject *Sender)
{
    ShowVagons();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRoutesClick(TObject *Sender)
{
    if (RoutesFEnabled)
        RoutesF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NAccumsClick(TObject *Sender)
{
    if (AccumsFEnabled)
        AccumsF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NMsgsClick(TObject *Sender)
{
    MsgsF->WindowState = wsNormal;
	MsgsF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NDateTimeClick(TObject *Sender)
{
    ClockF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::N4Click(TObject *Sender)
{
    ShowMinutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NAboutClick(TObject *Sender)
{
    TProMKUF *ProMKUF;
    ProMKUF = new TProMKUF(this);
    ProMKUF->ShowModal();
    delete ProMKUF;
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepDayPointsClick(TObject *Sender)
{
    MakeRepDayPoints();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepDayRoutesClick(TObject *Sender)
{
    MakeRepDayRoutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepIntervClick(TObject *Sender)
{
    MakeRepIntervalsRoutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NAshGraphClick(TObject *Sender)
{
    MakeAshGraph();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRouteGraphClick(TObject *Sender)
{
    MakeRouteGraph();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepVagonsClick(TObject *Sender)
{
    MakeRepVagons();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepPosClick(TObject *Sender)
{
    MakeRepPos();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepPosMonthClick(TObject *Sender)
{
    MakeRepPosMonth();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepMinClick(TObject *Sender)
{
    MakeRepMin();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepPointsMonthClick(TObject *Sender)
{
    MakeRepPointsMonth();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepRouteMonthClick(TObject *Sender)
{
    MakeRepRoutesMonth();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NPosEditorClick(TObject *Sender)
{
    ShowPosEditor();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRepCertClick(TObject *Sender)
{
    CertForBlank = true;
    MakeRepCert();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCertOnEmptyClick(TObject *Sender)
{
    CertForBlank = false;
    MakeRepCert();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCertFaceClick(TObject *Sender)
{
    //печатаем лицевую сторону удостоверения
    CertFaceShow();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NAvgAshClick(TObject *Sender)
{
   MakeAvgAshReport();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NOperHelperClick(TObject *Sender)
{
    ShowOperHelper();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ClientSocketConnecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
/*
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +". Открытие подключения...");
*/
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
/*
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +". Закрытие подключения...");
*/
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +". Ошибка: "+IntToStr(ErrorCode));
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCqmNetQueryClick(TObject *Sender)
{
    AnsiString command, answer;
    if (InputData("МКУ Клинет", "Выполнить запрос к МКУ Серверу", command))
    {
        DoMsg("Команда: "+command);
        CqmNetQuery(command, answer);
        if (answer.Pos('\n'))
        {
            DoMsg2Buf("Ответ  :\n"+answer);
        }
        else
        {
            DoMsg("Ответ  : "+answer);
        }
    }
    DoFlushBuf();
}

//---------------------------------------------------------------------------

