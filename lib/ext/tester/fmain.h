//---------------------------------------------------------------------------

#ifndef fmainH
#define fmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CustomizeDlg.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMainF : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *EModul;
    TOpenDialog *OpenDialog;
    TSpeedButton *BOpenModule;
    TMemo *M;
    TSpeedButton *BLoad;
    TSpeedButton *BFree;
    TSpeedButton *BStart;
    TSpeedButton *BStop;
    TLabeledEdit *EProc;
    TSpeedButton *BProc;
    void __fastcall BOpenModuleClick(TObject *Sender);
    void __fastcall BLoadClick(TObject *Sender);
    void __fastcall BFreeClick(TObject *Sender);
    void __fastcall BStartClick(TObject *Sender);
    void __fastcall BStopClick(TObject *Sender);
    void __fastcall BProcClick(TObject *Sender);
private:	// User declarations
    HINSTANCE hModule;
public:		// User declarations
    __fastcall TMainF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainF *MainF;
//---------------------------------------------------------------------------
#endif
