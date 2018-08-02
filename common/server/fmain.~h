//---------------------------------------------------------------------------

#ifndef fmainH
#define fmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#include "../common/windows/global.h"
#include "Trayicon.h"
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TMainF : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *NServer;
	TMenuItem *NStart;
	TMenuItem *NStop;
	TMenuItem *Ndiv01;
	TMenuItem *NExit;
	TMenuItem *NHelp;
	TMenuItem *NAbout;
	TImageList *ImageList;
	TMenuItem *NWindows;
    TMenuItem *NSigs;
	TMenuItem *NMsgs;
    TMenuItem *NPointsView;
    TMenuItem *NCalibrView;
    TMenuItem *Ndiv02;
    TTrayIcon *TrayIcon;
    TMenuItem *NVagonsView;
    TMenuItem *NCredits;
    TMenuItem *N2;
    TMenuItem *NForMethodist;
    TMenuItem *NPbyVagWei;
    TMenuItem *NSaveCalibr;
    TPopupMenu *PopUpTray;
    TMenuItem *NRestore;
    TMenuItem *N3;
    TMenuItem *NByeBye;
    TMenuItem *NExec;
    TMenuItem *NBetterAsh;
    TMenuItem *NBetterVagons;
    TMenuItem *NDateTime;
    TServerSocket *ServerSocket;
    TMenuItem *NShowConnections;
    TMenuItem *NRoutesView;
    TMenuItem *NAccumView;
    TMenuItem *Ndiv03;
    TMenuItem *NCoaltypesEditor;
    TMenuItem *NBetterRoutes;
    TMenuItem *NRestart;
    TMenuItem *N1;
    TApplicationEvents *ApplicationEvents;
	void __fastcall NExitClick(TObject *Sender);
	void __fastcall NAboutClick(TObject *Sender);
	void __fastcall NSigsClick(TObject *Sender);
	void __fastcall NMsgsClick(TObject *Sender);
	void __fastcall NStartClick(TObject *Sender);
	void __fastcall NStopClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall NPointsViewClick(TObject *Sender);
    void __fastcall NCalibrViewClick(TObject *Sender);
    void __fastcall NVagonsViewClick(TObject *Sender);
    void __fastcall NCreditsClick(TObject *Sender);
    void __fastcall NPbyVagWeiClick(TObject *Sender);
    void __fastcall NSaveCalibrClick(TObject *Sender);
    void __fastcall TrayIconRestore(TObject *Sender);
    void __fastcall NRestoreClick(TObject *Sender);
    void __fastcall NByeByeClick(TObject *Sender);
    void __fastcall NExecClick(TObject *Sender);
    void __fastcall NBetterAshClick(TObject *Sender);
    void __fastcall NBetterVagonsClick(TObject *Sender);
    void __fastcall NDateTimeClick(TObject *Sender);
    void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall NShowConnectionsClick(TObject *Sender);
    void __fastcall NRoutesViewClick(TObject *Sender);
    void __fastcall NAccumViewClick(TObject *Sender);
    void __fastcall NCoaltypesEditorClick(TObject *Sender);
    void __fastcall NBetterRoutesClick(TObject *Sender);
    void __fastcall NRestartClick(TObject *Sender);
    void __fastcall ApplicationEventsRestore(TObject *Sender);
    void __fastcall ApplicationEventsDeactivate(TObject *Sender);
   void __fastcall ServerSocketAccept(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
public:		// User declarations
	__fastcall TMainF(TComponent* Owner);
protected:
    void __fastcall MKickServer(TMessage &Message);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_KICK_SERVER, TMessage, MKickServer)
END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TMainF *MainF;
//Открываем сокет cqmnet (1 - удачно)
int StartCmqNet(void);
//Закрываем сокет cqmnet
void StopCqmNet(void);
//---------------------------------------------------------------------------
#endif
