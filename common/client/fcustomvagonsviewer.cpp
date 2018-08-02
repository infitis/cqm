//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "globcli.h"
#include "fcustomvagonsviewer.h"
#include "clientdata.h"
#include "..\windows\fdm.h"
#include "..\windows\fmsgs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TCustomVagonsViewerF *CustomVagonsViewerF = NULL;
TCustomVagonsViewerF *VagonsViewers[MAX_CLIENT_VAGONS];

//---------------------------------------------------------------------------
__fastcall TCustomVagonsViewerF::TCustomVagonsViewerF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsViewerF::Refresh(void)
{
    q->Close();
    q->SQL->Text = AnsiString().sprintf(
    "select cast(moment as time) as vdate, id, P, A from vagons "
    "where vname='%s' and addday(moment, 1) >= current_timestamp order by moment, id"
  //"where vname='%s' and cast(current_timestamp - moment as decimal(17,4)) <= 1.0 order by moment, id"
    ,clivagons[myvagonindex].name);
    q->Open();
    q->Last();
    Status->SimpleText = "Количество вагонов: " + IntToStr(q->RecordCount);
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsViewerF::Init(int vid)
{
    myvagonindex = vid;
    Caption = clivagons[myvagonindex].title;
    LoadPosition();
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomVagonsViewerF::LoadPosition(void)
{
	Top =			    	ini->ReadInteger(AnsiString("VagViewer-")+IntToStr(myvagonindex), "Top", 10);
	Left =			    	ini->ReadInteger(AnsiString("VagViewer-")+IntToStr(myvagonindex), "Left", 10);
	Width =			    	ini->ReadInteger(AnsiString("VagViewer-")+IntToStr(myvagonindex), "Width", 200);
	Height = 		    	ini->ReadInteger(AnsiString("VagViewer-")+IntToStr(myvagonindex), "Height", 200);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
