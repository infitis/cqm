//---------------------------------------------------------------------------
#ifndef falarmH
#define falarmH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TAlarmF : public TForm
{
__published:	// IDE-managed Components
    TSpeedButton *SBClose;
    TTimer *Timer;
    TLabel *LWhat;
    TLabel *LPar;
    TLabel *Label1;
    TLabel *Label2;
    TCheckBox *CBStop;
    void __fastcall SBCloseClick(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAlarmF(TComponent* Owner);
};

//---------------------------------------------------------------------------
#endif
