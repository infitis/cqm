//---------------------------------------------------------------------------

#ifndef fenterdataH
#define fenterdataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TEnterDataF : public TForm
{
__published:	// IDE-managed Components
    TButton *BOk;
    TLabel *L;
    TButton *BCancel;
    TComboBox *E;
private:	// User declarations
    AnsiString DataFileName;
public:		// User declarations
    __fastcall TEnterDataF(TComponent* Owner);
    __fastcall ~TEnterDataF();
};

bool __fastcall InputData(const AnsiString ACaption,
                          const AnsiString APrompt,
                                AnsiString &Value);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
