//---------------------------------------------------------------------------

#ifndef floaderH
#define floaderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TLoaderF : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel;
    TLabel *LNow;
    TLabel *Label1;
    TLabel *LWhat;
    TImage *Image;
    TProgressBar *PB;
private:	// User declarations
public:		// User declarations
    __fastcall TLoaderF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoaderF *LoaderF;
void CreateProgressForm(int ASteps, AnsiString AWhat);
void StepProgressForm(AnsiString ANow);
void KillProgressForm(void);
//---------------------------------------------------------------------------
#endif
