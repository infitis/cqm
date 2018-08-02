//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "fmainic.h"
#include "faboutic.h"
#include "stuffic.h"
#include "fmsgs.h"

#include "rhours.h"
#include "rashgraph.h"
#include "rvagons.h"
#include "rpos.h"
#include "rmin.h"
#include "rintervals.h"
#include "rmonth.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainICF *MainICF;
//---------------------------------------------------------------------------
__fastcall TMainICF::TMainICF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NAboutClick(TObject *Sender)
{
    AboutFormShow();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NExitClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::FormClose(TObject *Sender, TCloseAction &Action)
{
    Stop();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NRefreshClick(TObject *Sender)
{
    RefreshActions();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NMinClick(TObject *Sender)
{
    ShowMinutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NWorkPositopnClick(TObject *Sender)
{
    ShowWorkPosition();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NMsgsClick(TObject *Sender)
{
    MsgsF->WindowState = wsMaximized;
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrDayPointClick(TObject *Sender)
{
    MakeRepDayPoints();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrDayRouteClick(TObject *Sender)
{
    MakeRepDayRoutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrIntervalRouteClick(TObject *Sender)
{
    MakeRepIntervalsRoutes();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrMonthPointClick(TObject *Sender)
{
    MakeRepPointsMonth();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrMonthRouteClick(TObject *Sender)
{
    MakeRepRoutesMonth();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrVagonClick(TObject *Sender)
{
    MakeRepVagons();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrPosClick(TObject *Sender)
{
    MakeRepPos();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrMinuteClick(TObject *Sender)
{
    MakeRepMin();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrGraphPointClick(TObject *Sender)
{
    MakeAshGraph();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NrGraphRouteClick(TObject *Sender)
{
    MakeRouteGraph();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NaConnectClick(TObject *Sender)
{
    Action_Connect();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NaDisconnectClick(TObject *Sender)
{
    Action_Disconnect();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NaRefrshClick(TObject *Sender)
{
    Action_Update();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NaDBRestoreFromFileClick(TObject *Sender)
{
    Action_RestoreDB();
}

//---------------------------------------------------------------------------
void __fastcall TMainICF::NaDBBackupClick(TObject *Sender)
{
    Action_BackupDB();
}

//---------------------------------------------------------------------------

