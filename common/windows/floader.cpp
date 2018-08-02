//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "floader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoaderF *LoaderF = NULL;

//---------------------------------------------------------------------------
void CreateProgressForm(int ASteps, AnsiString AWhat)
{
    if (LoaderF == NULL)
    {
        LoaderF = new TLoaderF(Application);
        LoaderF->LWhat->Caption = AWhat;
        LoaderF->PB->Step = 100/ASteps;
        LoaderF->Show();
#ifdef CQM_CLIENT_APPLICATION
        LoaderF->Top -= 10;
#else
        LoaderF->Top -= 150;
#endif
        LoaderF->Update();
    }
}

//---------------------------------------------------------------------------
void StepProgressForm(AnsiString ANow)
{
    if (LoaderF)
    {
        LoaderF->LNow->Caption = ANow;
        LoaderF->PB->StepIt();
        LoaderF->Update();
        //Sleep(700);
    }
}

//---------------------------------------------------------------------------
void KillProgressForm(void)
{
    if (LoaderF)
    {
        delete LoaderF;
    }
    LoaderF = NULL;
}

//---------------------------------------------------------------------------
__fastcall TLoaderF::TLoaderF(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
