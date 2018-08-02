//---------------------------------------------------------------------------

#ifndef faboutsrvH
#define faboutsrvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAboutF : public TForm
{
__published:	// IDE-managed Components
    TRichEdit *RE;
    TTimer *T;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TTimer(TObject *Sender);
    void __fastcall REMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
    int pos;
public:		// User declarations
    __fastcall TAboutF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutF *AboutF;
//---------------------------------------------------------------------------
#endif
