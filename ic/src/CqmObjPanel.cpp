//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "CqmObjPanel.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
/*
static inline void ValidCtrCheck(TCqmObjPanel *)
{
    new TCqmObjPanel(NULL);
}
*/

//---------------------------------------------------------------------------
__fastcall TCqmObjPanel::TCqmObjPanel(TComponent* Owner)
    : TPanel(Owner)
{
    //Panel
    Color = TColor(0xf0f0f0);
    Font->Name = "Tahoma";
    Caption = " ";
    Height = 44;
    Align = alTop;

    //LabelTitle
    LabelTitle = new TLabel(this);
    LabelTitle->Parent = this;
    LabelTitle->Top = 8;
    LabelTitle->Left= 8;
    LabelTitle->Cursor = crHandPoint;
    LabelTitle->Font->Color = clNavy;
    LabelTitle->Font->Style = TFontStyles() << fsUnderline;
    LabelTitle->OnMouseEnter = LabelTitleMouseEnter;
    LabelTitle->OnMouseLeave = LabelTitleMouseLeave;
    LabelTitle->OnClick      = LabelTitleClick;

    //LabelUpdateText
    LabelUpdateText = new TLabel(this);
    LabelUpdateText->Parent = this;
    LabelUpdateText->Top = 36;
    LabelUpdateText->Left= 8;
    LabelUpdateText->Visible = false;
    LabelUpdateText->Caption = "Обновление:";

    //LabelUpdateTime
    LabelUpdateTime = new TLabel(this);
    LabelUpdateTime->Parent = this;
    LabelUpdateTime->Top = 36;
    LabelUpdateTime->Left= 80;
    LabelUpdateTime->Visible = false;
    LabelUpdateTime->Caption = "";

    SetObjTitle("Имя объекта");
    SetObjActive(false);
}

//---------------------------------------------------------------------------
__fastcall TCqmObjPanel::~TCqmObjPanel()
{
    delete LabelUpdateTime;
    delete LabelUpdateText;
    delete LabelTitle;
}

//---------------------------------------------------------------------------
AnsiString __fastcall TCqmObjPanel::GetObjTitle()
{
    return LabelTitle->Caption;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::SetObjTitle(AnsiString s)
{
    LabelTitle->Caption = s;
}

//---------------------------------------------------------------------------
AnsiString __fastcall TCqmObjPanel::GetObjUpdateTime()
{
    return LabelUpdateTime->Caption;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::SetObjUpdateTime(AnsiString s)
{
    LabelUpdateTime->Caption = s;
}

//---------------------------------------------------------------------------
bool __fastcall TCqmObjPanel::GetObjActive()
{
    return FObjActive;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::SetObjActive(bool a)
{
    if (a == FObjActive)
        return;
    if (a)
    {
        ObjActivate(this);
    }
    else
    {
        ObjDeActivate(this);
    }
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::LabelTitleMouseEnter(TObject *Sender)
{
    LabelTitle->Font->Color = clBlue;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::LabelTitleMouseLeave(TObject *Sender)
{
    LabelTitle->Font->Color = clNavy;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::LabelTitleClick(TObject *Sender)
{
    ObjActive = !ObjActive;
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::ObjActivate(TObject *Sender)
{
    if (NextCqmObjPanel)
        NextCqmObjPanel->ObjFindDeActivate(this);

    LabelUpdateText->Visible = true;
    LabelUpdateTime->Visible = true;
    Height = 64;
    LabelTitle->Font->Style = LabelTitle->Font->Style << fsBold;
    Color = clWhite;
    Update();

    FObjActive = true;

    if (FOnObjActivate)
        FOnObjActivate(Sender);

}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::ObjDeActivate(TObject *Sender)
{
    LabelUpdateText->Visible = false;
    LabelUpdateTime->Visible = false;
    Height = 44;
    LabelTitle->Font->Style = LabelTitle->Font->Style >> fsBold;
    Color = TColor(0xf0f0f0);
    Update();

        FObjActive = false;

    if (FOnObjDeActivate)
        FOnObjDeActivate(Sender);

}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::ObjFindDeActivate(TCqmObjPanel* FirstCqmObjPanel)
{
    if (FirstCqmObjPanel == this)
        return;
    if (ObjActive)
    {
        ObjActive = false;
    }
    else
    {
        if (NextCqmObjPanel)
           NextCqmObjPanel->ObjFindDeActivate(FirstCqmObjPanel);
    }
}

//---------------------------------------------------------------------------
void __fastcall TCqmObjPanel::Update(void)
{
    TPanel::Update();

    TControl* p = NULL;
    p = dynamic_cast<TControl*>(Parent);
    if (p)
    {
        p->Update();
    }
}

//---------------------------------------------------------------------------
/*
namespace Cqmobjpanel
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TCqmObjPanel)};
         RegisterComponents("Samples", classes, 0);
    }
}
*/
//---------------------------------------------------------------------------
