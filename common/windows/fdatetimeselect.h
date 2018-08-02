//---------------------------------------------------------------------------

#ifndef fdatetimeselectH
#define fdatetimeselectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TDateTimeSelect : public TForm
{
__published:	// IDE-managed Components
    TDateTimePicker *DateTimePicker1;
    TDateTimePicker *DateTimePicker2;
    TDateTimePicker *DateTimePicker3;
    TDateTimePicker *DateTimePicker4;
    TLabel *L1;
    TLabel *L2;
    TButton *BOk;
    TButton *BCancel;
private:	// User declarations
public:		// User declarations
    __fastcall TDateTimeSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
bool __fastcall InputDateTime(  const AnsiString ACaption,
                                bool interval,
                                TDateTime &Value1,
                                TDateTime &Value2);
//---------------------------------------------------------------------------
#endif
