//---------------------------------------------------------------------------

#ifndef fclockH
#define fclockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TClockF : public TForm
{
__published:	// IDE-managed Components
    TLabel *L;
    TTimer *Timer;
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall LMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall LMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall LMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    int x, y;
    TColor c;
    bool moved;
public:		// User declarations
    __fastcall TClockF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClockF *ClockF;
//---------------------------------------------------------------------------
#endif
