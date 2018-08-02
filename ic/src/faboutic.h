//---------------------------------------------------------------------------

#ifndef fabouticH
#define fabouticH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAboutICF : public TForm
{
__published:	// IDE-managed Components
    TImage *I;
    TPanel *P;
    TLabel *L;
    TSpeedButton *SBClose;
    TMemo *M;
    void __fastcall SBCloseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAboutICF(TComponent* Owner);
};
//---------------------------------------------------------------------------
void SplashFormShow();
void SplashFormClose();
void AboutFormShow();

//---------------------------------------------------------------------------
#endif
