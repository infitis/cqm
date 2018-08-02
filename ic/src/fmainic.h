//---------------------------------------------------------------------------

#ifndef fmainicH
#define fmainicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMainICF : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *NHelp;
    TMenuItem *NAbout;
    TMenuItem *NIC;
    TMenuItem *Ndiv1;
    TMenuItem *NExit;
    TMenuItem *Na;
    TMenuItem *NWindows;
    TMenuItem *Nr;
    TMenuItem *NWorkPositopn;
    TMenuItem *NMsgs;
    TMenuItem *NRefresh;
    TMenuItem *Ndiv2;
    TMenuItem *Ndiv3;
    TMenuItem *NrDayPoint;
    TMenuItem *NrDayRoute;
    TMenuItem *NrIntervalRoute;
    TMenuItem *NrMonthPoint;
    TMenuItem *NrMonthRoute;
    TMenuItem *NrVagon;
    TMenuItem *NrPos;
    TMenuItem *Ndiv4;
    TMenuItem *NrMinute;
    TMenuItem *NrGraphPoint;
    TMenuItem *NrGraphRoute;
    TMenuItem *NMin;
    TMenuItem *NaRefrsh;
    TMenuItem *Ndiv5;
    TMenuItem *NaConnect;
    TMenuItem *NaDisconnect;
    TMenuItem *Ndiv6;
    TMenuItem *NaDBRestoreFromFile;
    TMenuItem *NaDBBackup;
    void __fastcall NAboutClick(TObject *Sender);
    void __fastcall NExitClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall NRefreshClick(TObject *Sender);
    void __fastcall NMinClick(TObject *Sender);
    void __fastcall NWorkPositopnClick(TObject *Sender);
    void __fastcall NMsgsClick(TObject *Sender);
    void __fastcall NrDayPointClick(TObject *Sender);
    void __fastcall NrDayRouteClick(TObject *Sender);
    void __fastcall NrIntervalRouteClick(TObject *Sender);
    void __fastcall NrMonthPointClick(TObject *Sender);
    void __fastcall NrMonthRouteClick(TObject *Sender);
    void __fastcall NrVagonClick(TObject *Sender);
    void __fastcall NrPosClick(TObject *Sender);
    void __fastcall NrMinuteClick(TObject *Sender);
    void __fastcall NrGraphPointClick(TObject *Sender);
    void __fastcall NrGraphRouteClick(TObject *Sender);
    void __fastcall NaConnectClick(TObject *Sender);
    void __fastcall NaDisconnectClick(TObject *Sender);
    void __fastcall NaRefrshClick(TObject *Sender);
    void __fastcall NaDBRestoreFromFileClick(TObject *Sender);
    void __fastcall NaDBBackupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMainICF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainICF *MainICF;
//---------------------------------------------------------------------------
#endif
