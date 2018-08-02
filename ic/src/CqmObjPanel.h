//---------------------------------------------------------------------------

#ifndef CqmObjPanelH
#define CqmObjPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TCqmObjPanel : public TPanel
{
private:
protected:
    TLabel* LabelUpdateText;
    TLabel* LabelTitle;
    TLabel* LabelUpdateTime;

    AnsiString __fastcall GetObjTitle ();
    void       __fastcall SetObjTitle (AnsiString);

    AnsiString __fastcall GetObjUpdateTime ();
    void       __fastcall SetObjUpdateTime (AnsiString);

    bool FObjActive;
    bool __fastcall       GetObjActive ();
    void __fastcall       SetObjActive (bool);

    void __fastcall       LabelTitleMouseEnter(TObject *Sender);
    void __fastcall       LabelTitleMouseLeave(TObject *Sender);
    void __fastcall       LabelTitleClick     (TObject *Sender);

    TNotifyEvent FOnObjActivate;
    TNotifyEvent FOnObjDeActivate;
    void __fastcall       ObjActivate(TObject *Sender);
    void __fastcall       ObjDeActivate(TObject *Sender);

    TCqmObjPanel* FNext;

    void __fastcall Update(void);    

public:
    __fastcall TCqmObjPanel(TComponent* Owner);
    __fastcall ~TCqmObjPanel();
    void __fastcall ObjFindDeActivate(TCqmObjPanel* FirstCqmObjPanel);

__published:
    __property AnsiString ObjTitle = {read=GetObjTitle, write=SetObjTitle};
    __property AnsiString ObjUpdateTime = {read=GetObjUpdateTime, write=SetObjUpdateTime};
    __property bool       ObjActive  = {default=false, read=GetObjActive, write=SetObjActive};
    __property TNotifyEvent OnObjActivate = {read=FOnObjActivate, write=FOnObjActivate};
    __property TNotifyEvent OnObjDeActivate = {read=FOnObjDeActivate, write=FOnObjDeActivate};
    __property TCqmObjPanel* NextCqmObjPanel  = {default=NULL, read=FNext, write=FNext};
};
//---------------------------------------------------------------------------
#endif
