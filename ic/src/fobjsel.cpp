//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "fobjsel.h"
#include "stuffic.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TObjSelF *ObjSelF;

//---------------------------------------------------------------------------
__fastcall TObjSelF::TObjSelF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
__fastcall TObjSelF::~TObjSelF()
{
    for (int i=0; i<CqmObjectCount; i++)
    {
        delete CqmObjects[i];
    }
}

//---------------------------------------------------------------------------
void TObjSelF::Init(void)
{
    CqmObjectCount = IC->countObjects;

    for (int i=0; i<CqmObjectCount; i++)
    {
        TCqmObjPanel* P = new TCqmObjPanel(this);
        P->Parent = this;
        P->ObjTitle = IC->Objects[i]->Title;
        P->Tag = i;
        P->OnObjActivate = ObjActivated;
        P->OnObjDeActivate = ObjDeActivated;
        CqmObjects[i] = P;
    }

    for (int i=1; i<CqmObjectCount; i++)
    {
        CqmObjects[i-1]->NextCqmObjPanel = CqmObjects[i];
    }
    CqmObjects[IC->countObjects-1]->NextCqmObjPanel = CqmObjects[0];

    Width = 200;
    if (IC->countObjects)
        Height = IC->countObjects * CqmObjects[0]->Height + 60;
    else
        Height = 60;
    Top = 0;
    Left = 0;
}

//---------------------------------------------------------------------------
void TObjSelF::Refresh()
{
    if (IC->curObjectId >= 0)
    {
        CqmObjects[IC->curObjectId]->ObjUpdateTime =
            FormatDateTime("dd.mm.yyyy hh:nn:ss", IC->curObject->LastUpdate);
    }
}

//---------------------------------------------------------------------------
void __fastcall TObjSelF::ObjActivated(TObject * Sender)
{
    TCqmObjPanel* p = NULL;
    p = dynamic_cast<TCqmObjPanel*>(Sender);
    if (p)
    {
        CqmObjActivated(p->Tag);
    }
}

//---------------------------------------------------------------------------
void __fastcall TObjSelF::ObjDeActivated(TObject * Sender)
{
    if (IC->curObjectId < 0)
        return;

    TCqmObjPanel* p = NULL;
    p = dynamic_cast<TCqmObjPanel*>(Sender);
    if (p)
    {
        CqmObjDeActivated(p->Tag);
    }
}

//---------------------------------------------------------------------------

