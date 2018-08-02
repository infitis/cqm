//---------------------------------------------------------------------------

#ifndef fpromkuH
#define fpromkuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TProMKUF : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo;
    TSpeedButton *SBOk;
    TImage *Image;
    TMemo *Main;
    void __fastcall ImageClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TProMKUF(TComponent* Owner);
};

//---------------------------------------------------------------------------
//extern PACKAGE TProMKUF *ProMKUF;

//---------------------------------------------------------------------------
#endif
