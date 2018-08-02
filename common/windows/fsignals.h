//---------------------------------------------------------------------------

#ifndef fsignalsH
#define fsignalsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
#include "logfile.h"
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
#define MAX_LINE_IN_SIGNALSWIN 1024

//---------------------------------------------------------------------------
class TSignalsF : public TForm
{
__published:	// IDE-managed Components
	TMemo *M;
    TPanel *PSH;
private:	// User declarations
    AnsiString Buf;
public:		// User declarations
	__fastcall TSignalsF(TComponent* Owner);
    void __fastcall AddSignals(AnsiString s);
    TLogFile * log;
    __fastcall ~TSignalsF();
    void __fastcall FlushSignals(void);
    void Init(AnsiString s);
};
//---------------------------------------------------------------------------
extern PACKAGE TSignalsF *SignalsF;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
