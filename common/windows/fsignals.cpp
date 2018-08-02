//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fsignals.h"
#include "globsrv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
extern AnsiString SignalsLogDir;

//---------------------------------------------------------------------------
void __fastcall TSignalsF::AddSignals(AnsiString s)
{
	if (M->Lines->Count >= MAX_LINE_IN_SIGNALSWIN)
    {
    	M->Lines->Clear();
    }
    AnsiString fdt;
    if (DateTimeFormatForSignals == "")
        fdt = DateTimeToStr(Now());
    else
        fdt = FormatDateTime(DateTimeFormatForSignals, Now());
	M->Lines->Add(fdt + s);
    Buf = Buf + fdt + s + "\r\n";
}

//---------------------------------------------------------------------------
TSignalsF *SignalsF;

//---------------------------------------------------------------------------
__fastcall TSignalsF::TSignalsF(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

__fastcall TSignalsF::~TSignalsF()
{
    FlushSignals();
    delete log;
}

//---------------------------------------------------------------------------
void __fastcall TSignalsF::FlushSignals(void)
{
    log->AddWithoutTime(Buf);
    Buf = "";
}

//---------------------------------------------------------------------------
void TSignalsF::Init(AnsiString s)
{
    log = new TLogFile(SignalsLogDir, "signals", "csv", s.c_str());
    Buf = "";
    PSH->Caption = s;
	M->Lines->Add(s);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


