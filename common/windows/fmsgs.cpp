//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fmsgs.h"

//---------------------------------------------------------------------------
extern AnsiString LogDir;
extern AnsiString LogName;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMsgsF *MsgsF = NULL;

//---------------------------------------------------------------------------
void DoMsg(AnsiString m)
{
    if (MsgsF)
    {
        MsgsF->log->Add(m);
    	if (MsgsF->M->Lines->Count > MAX_LINE_IN_MSGS)
        {
        	MsgsF->M->Lines->Clear();
        }
    	MsgsF->M->Lines->Add(FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz ", Now()) + m);
    }
}

//---------------------------------------------------------------------------
void DoMiltiLineMsg(AnsiString m)
{
    AnsiString buf = "";

    if (MsgsF)
    {
        MsgsF->M->Visible = false;
        TStringList * L = new TStringList();
        L->Text = m;
        for (int i=0; i<L->Count; i++)
        {
            DoMsg(L->Strings[i]);
        }
        MsgsF->M->Visible = true;
        //MsgsF->M->SetFocus();
        SendMessage(MsgsF->M->Handle, WM_VSCROLL, SB_BOTTOM, 0);
    }
}

//---------------------------------------------------------------------------
void DoMsg2Buf(AnsiString m)
{
    MsgsF->Buf->Append(m);
    if (MsgsF->Buf->Count > MAX_LINE_IN_BUF)
    {
        DoFlushBuf();
    }
}

//---------------------------------------------------------------------------
void DoFlushBuf(void)
{
    if (MsgsF->Buf->Count == 0)
        return;

    DoMiltiLineMsg(MsgsF->Buf->Text);
    MsgsF->Buf->Clear();
}

//---------------------------------------------------------------------------
__fastcall TMsgsF::TMsgsF(TComponent* Owner)
	: TForm(Owner)
{
    Buf = new TStringList();
    Buf->Clear();
    log = new TLogFile(LogDir, LogName, "log");
}

//---------------------------------------------------------------------------
__fastcall TMsgsF::~TMsgsF(void)
{
    DoFlushBuf();
    delete log;
    delete Buf;
}

//---------------------------------------------------------------------------

