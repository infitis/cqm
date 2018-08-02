//---------------------------------------------------------------------------

#ifndef fmainH
#define fmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ScktComp.hpp>
#include <QRPrntr.hpp>
//---------------------------------------------------------------------------
class TMainF : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *NCli;
    TTimer *Timer;
    TMenuItem *NView;
    TMenuItem *NRefresh;
    TMenuItem *NHelp;
    TMenuItem *NAbout;
    TMenuItem *NWorkPosition;
    TMenuItem *NVagons;
    TMenuItem *N1;
    TMenuItem *NMsgs;
    TMenuItem *NReports;
    TMenuItem *N2;
    TMenuItem *NExit;
    TMenuItem *NDateTime;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *NRepDayPoints;
    TMenuItem *NAshGraph;
    TMenuItem *N5;
    TImageList *ImageList;
    TMenuItem *NRepVagons;
    TMenuItem *NRepPos;
    TMenuItem *NRepCert;
    TMenuItem *N6;
    TMenuItem *NRepMin;
    TMenuItem *NPosEditor;
    TMenuItem *NCertFace;
    TMenuItem *NCertOnBlank;
    TMenuItem *NOperHelper;
    TClientSocket *ClientSocket;
    TMenuItem *NCqmNetQuery;
    TMenuItem *NRoutes;
    TMenuItem *N9;
    TMenuItem *NRepDayRoutes;
    TMenuItem *NAccums;
    TMenuItem *NRepInterv;
    TMenuItem *NRouteGraph;
    TMenuItem *NCertOnEmpty;
    TMenuItem *NRepPointsMonth;
    TMenuItem *NRepRouteMonth;
    TMenuItem *NRepPosMonth;
   TMenuItem *N7;
   TMenuItem *NAvgAsh;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall NRefreshClick(TObject *Sender);
    void __fastcall NExitClick(TObject *Sender);
    void __fastcall NWorkPositionClick(TObject *Sender);
    void __fastcall NVagonsClick(TObject *Sender);
    void __fastcall NMsgsClick(TObject *Sender);
    void __fastcall NDateTimeClick(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall NAboutClick(TObject *Sender);
    void __fastcall NRepDayPointsClick(TObject *Sender);
    void __fastcall NAshGraphClick(TObject *Sender);
    void __fastcall NRepVagonsClick(TObject *Sender);
    void __fastcall NRepPosClick(TObject *Sender);
    void __fastcall NRepMinClick(TObject *Sender);
    void __fastcall NPosEditorClick(TObject *Sender);
    void __fastcall NRepCertClick(TObject *Sender);
    void __fastcall NCertFaceClick(TObject *Sender);
    void __fastcall NOperHelperClick(TObject *Sender);
    void __fastcall ClientSocketConnecting(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
    void __fastcall NCqmNetQueryClick(TObject *Sender);
    void __fastcall NRoutesClick(TObject *Sender);
    void __fastcall NRepDayRoutesClick(TObject *Sender);
    void __fastcall NAccumsClick(TObject *Sender);
    void __fastcall NRepIntervClick(TObject *Sender);
    void __fastcall NRouteGraphClick(TObject *Sender);
    void __fastcall NCertOnEmptyClick(TObject *Sender);
    void __fastcall NRepPointsMonthClick(TObject *Sender);
    void __fastcall NRepRouteMonthClick(TObject *Sender);
    void __fastcall NRepPosMonthClick(TObject *Sender);
   void __fastcall NAvgAshClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMainF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainF *MainF;

//---------------------------------------------------------------------------
#endif
