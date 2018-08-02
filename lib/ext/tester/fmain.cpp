//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fmain.h"
#include "..\..\common\classes\cqmextension_def.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainF *MainF;
//---------------------------------------------------------------------------
__fastcall TMainF::TMainF(TComponent* Owner)
    : TForm(Owner)
{
    hModule = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainF::BOpenModuleClick(TObject *Sender)
{
    if (OpenDialog->Execute())
    {
        this->EModul->Text = OpenDialog->FileName;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainF::BLoadClick(TObject *Sender)
{
    hModule = LoadLibrary(EModul->Text.c_str());

    if (hModule)
    {
        M->Lines->Append(EModul->Text+" loaded.");
        BLoad->Enabled = false;
        BFree->Enabled = true;
        BStart->Enabled = true;
        BStop->Enabled = true;
        BProc->Enabled = true;
    }
    else
    {
        M->Lines->Append("loader error: "+IntToStr(GetLastError));
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainF::BFreeClick(TObject *Sender)
{
    if (FreeLibrary(hModule))
    {
        M->Lines->Append("Library is free");
        BLoad->Enabled = true;
        BFree->Enabled = false;
        BStart->Enabled = false;
        BStop->Enabled = false;
        BProc->Enabled = false;
    }
    else
    {
        M->Lines->Append("free error: "+IntToStr(GetLastError));
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainF::BStartClick(TObject *Sender)
{
    H_CQM_EXTENSION_START_PROC hProc;
    int ret;
    char msg[255] = "";

    M->Lines->Append("cqm_extension_start:");
    hProc = (H_CQM_EXTENSION_START_PROC) GetProcAddress(hModule, CQM_EXTENSION_START_PROC_NAME);
    if (hProc)
    {
        M->Lines->Append("proc address: "+AnsiString().sprintf("%X", hProc));
        ret = (*hProc)(4, msg);
        M->Lines->Append("cqm_extension_start return : "+IntToStr(ret));
        M->Lines->Append("cqm_extension_start message: "+AnsiString(msg));
    }
    else
    {
        M->Lines->Append("GetProcAddress _cqm_extension_start error: "+IntToStr(GetLastError));
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainF::BStopClick(TObject *Sender)
{
    H_CQM_EXTENSION_STOP_PROC hProc;
    int ret;
    char msg[255] = "";

    M->Lines->Append("cqm_extension_stop:");
    hProc = (H_CQM_EXTENSION_STOP_PROC) GetProcAddress(hModule, CQM_EXTENSION_STOP_PROC_NAME);
    if (hProc)
    {
        M->Lines->Append("proc address: "+AnsiString().sprintf("%X", hProc));
        ret = (*hProc)(5, msg);
        M->Lines->Append("cqm_extension_stop  return : "+IntToStr(ret));
        M->Lines->Append("cqm_extension_stop  message: "+AnsiString(msg));
    }
    else
    {
        M->Lines->Append("GetProcAddress _cqm_extension_stop error: "+IntToStr(GetLastError));
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainF::BProcClick(TObject *Sender)
{
    H_CQM_EXTENSION_PROC hProc;
    int ret;
    char msg[255] = "";

    M->Lines->Append("cqm_extension_proc:");
    hProc = (H_CQM_EXTENSION_PROC) GetProcAddress(hModule, EProc->Text.c_str());
    if (hProc)
    {
        M->Lines->Append("proc address: "+AnsiString().sprintf("%X", hProc));
        ret = (*hProc)(6, msg, NULL);
        M->Lines->Append("cqm_extension_proc  return : "+IntToStr(ret));
        M->Lines->Append("cqm_extension_proc  message: "+AnsiString(msg));
    }
    else
    {
        M->Lines->Append("GetProcAddress "+EProc->Text+" error: "+IntToStr(GetLastError));
    }
}
//---------------------------------------------------------------------------
