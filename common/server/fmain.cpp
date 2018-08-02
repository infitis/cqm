//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fmain.h"
#include "globsrv.h"
#include "fpromku.h"
#include "cqmcore.h"
#include "fsignals.h"
#include "fmsgs.h"
#include "stuff.h"
#include "ftableviewer.h"
#include "faboutsrv.h"
#include "fpswd.h"
#include "fclock.h"
#include "fenterdata.h"
#include "fcteditor.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMainF *MainF;

//---------------------------------------------------------------------------
__fastcall TMainF::TMainF(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NExitClick(TObject *Sender)
{
	Close();
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
void __fastcall TMainF::NSigsClick(TObject *Sender)
{
	SignalsF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NMsgsClick(TObject *Sender)
{
	MsgsF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NStartClick(TObject *Sender)
{
	StartLoop();
    NStart->Enabled = false;
    NStop->Enabled  = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NStopClick(TObject *Sender)
{
	StopLoop();
    NStop->Enabled  = false;
    NStart->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainF::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    StopActions();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::MKickServer(TMessage &Message)
{
    //DoMsg("kick server at " + IntToStr(Message.WParam));
    KickActions(Message.WParam);
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NPointsViewClick(TObject *Sender)
{
    TableViewer->SetTable("points");
    TableViewer->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCalibrViewClick(TObject *Sender)
{
    TableViewer->SetTable("calibration");
    TableViewer->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NVagonsViewClick(TObject *Sender)
{
    TableViewer->SetTable("vagons");
    TableViewer->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRoutesViewClick(TObject *Sender)
{
    TableViewer->SetTable("routes");
    TableViewer->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NAccumViewClick(TObject *Sender)
{
    TableViewer->SetTable("accumulators");
    TableViewer->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCreditsClick(TObject *Sender)
{
    TAboutF *AboutF = new TAboutF(this);
    AboutF->ShowModal();
    delete AboutF;
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NPbyVagWeiClick(TObject *Sender)
{
    MakePbyVagWei();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NSaveCalibrClick(TObject *Sender)
{
    SaveCalbrFile();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::TrayIconRestore(TObject *Sender)
{
    if (!usePassword) return;
    int chkpassw = CheckPassword("Авторизация на МКУ Сервере", ServerPassword);
    if (chkpassw == PASSWORD_SUCCESS)
        return;
    if (chkpassw == PASSWORD_NOT_SUCCESS)
        ShowMessage("Неверный пароль. Работа невозможна.");

    TrayIcon->Minimize();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ApplicationEventsRestore(TObject *Sender)
{
    if (!is_nShell) return;
    if (!usePassword) return;

    int chkpassw = CheckPassword("Авторизация на МКУ Сервере", ServerPassword);
    if (chkpassw == PASSWORD_SUCCESS)
        return;
    if (chkpassw == PASSWORD_NOT_SUCCESS)
        ShowMessage("Неверный пароль. Работа невозможна.");

    Application->Minimize();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ApplicationEventsDeactivate(TObject *Sender)
{
    if (!is_nShell) return;
    Application->Minimize();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRestoreClick(TObject *Sender)
{
    TrayIcon->Restore();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NByeByeClick(TObject *Sender)
{
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NExecClick(TObject *Sender)
{
    AnsiString command, answer;
    if (InputData("МКУ Сервер", "Выполнить команду", command))
    {
        DoMsg("Команда: "+command);
        ExecCommand(command, &answer);
        if (answer.Pos('\n'))
        {
            DoMsg2Buf("Ответ  :\n"+answer);
        }
        else
        {
            DoMsg("Ответ  : "+answer);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NBetterAshClick(TObject *Sender)
{
    BetterAsh();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NBetterRoutesClick(TObject *Sender)
{
    BetterRoutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NBetterVagonsClick(TObject *Sender)
{
    BetterVagons();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NDateTimeClick(TObject *Sender)
{
    ClockF->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NShowConnectionsClick(TObject *Sender)
{
    int c = ServerSocket->Socket->ActiveConnections;
    DoMsg2Buf("Активных соединений: "+IntToStr(c));
    for (int i=0; i<c; i++)
    {
        DoMsg2Buf(AnsiString("Клиент: ")+IntToStr(ServerSocket->Socket->Connections[i]->SocketHandle)
                 +"; ip: "+ServerSocket->Socket->Connections[i]->RemoteAddress);
    }
    DoFlushBuf();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket)
{
    /*
    int ActiveConns = ServerSocket->Socket->ActiveConnections;
    if (ActiveConns > 2)
    {
        DoMsg("Активных подключений: "+IntToStr(ActiveConns));
        DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +"; ip: "+Socket->RemoteAddress
         +"; запрос на подключение отвергнут");
        ServerSocket->Socket->Connections[ActiveConns-1]->Close();
        //Socket->Close();
    }
    else
    {
        DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +"; ip: "+Socket->RemoteAddress
         +"; запрос на подключение");
    }
    DoFlushBuf();
    */
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +"; ip: "+Socket->RemoteAddress
         +"; подключен");
    DoFlushBuf();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +"; ip: "+Socket->RemoteAddress
         +"; отключен");
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    AnsiString command, answer;
    int ok;
    command = Socket->ReceiveText();

    command = command.TrimLeft();
    command = command.TrimRight();
    if (command.Pos("ping") == 1)
    {
        //просто ping
        Socket->SendText("ok\n");
        return;
    }

    ok = ExecCommand(command, &answer);
  //answer = IntToStr(ok)+" "+answer+"\n";
    answer = IntToStr(ok)+" "+answer;
    Socket->SendText(answer);

    if (!ok || (core.vi("debug") & CORE_DEBUG_CQML))
    {
        DoMsg2Buf("Клиент: "+IntToStr(Socket->SocketHandle)
                 +"; Запрос: "+command);
        DoMsg2Buf("Клиент: "+IntToStr(Socket->SocketHandle)
                 +"; Ответ : "+answer);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainF::ServerSocketClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    DoMsg("Клиент: "+IntToStr(Socket->SocketHandle)
         +"; ошибка: "+IntToStr(ErrorCode));
}

//---------------------------------------------------------------------------
int StartCmqNet(void)
{
    MainF->ServerSocket->Port = CqmNetPort;
    try
    {
        MainF->ServerSocket->Open();
    }
    catch(...)
    {
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void StopCqmNet(void)
{
    try
    {
        MainF->ServerSocket->Close();
    }
    catch(...){}
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NCoaltypesEditorClick(TObject *Sender)
{
    ShowCtEditor();
}

//---------------------------------------------------------------------------
void __fastcall TMainF::NRestartClick(TObject *Sender)
{
    DoOffCommand(OFF_RESTART);
}

//---------------------------------------------------------------------------

