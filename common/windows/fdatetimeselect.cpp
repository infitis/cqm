//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "fdatetimeselect.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TDateTimeSelect::TDateTimeSelect(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
bool __fastcall InputDateTime(  const AnsiString ACaption,
                                bool interval,
                                TDateTime &Value1,
                                TDateTime &Value2)
{
    bool ok = false;
    TDateTimeSelect *DateTimeSelectF;

    try
    {
        DateTimeSelectF = new TDateTimeSelect(NULL);
        DateTimeSelectF->Caption = ACaption;
        DateTimeSelectF->DateTimePicker3->Visible = interval;
        DateTimeSelectF->DateTimePicker4->Visible = interval;
        DateTimeSelectF->DateTimePicker1->DateTime = floor(Value1);
        DateTimeSelectF->DateTimePicker2->DateTime = Value1 - floor(Value1);
        DateTimeSelectF->DateTimePicker3->DateTime = floor(Value2);
        DateTimeSelectF->DateTimePicker4->DateTime = Value2 - floor(Value2);

        if (DateTimeSelectF->ShowModal() == mrOk)
        {
            Value1 = DateTimeSelectF->DateTimePicker1->Date
                   + DateTimeSelectF->DateTimePicker2->Time;
            Value2 = DateTimeSelectF->DateTimePicker3->Date
                   + DateTimeSelectF->DateTimePicker4->Time;
            ok = true;
        }
    }
    __finally
    {
        delete DateTimeSelectF;
    }

    return ok;
}

//---------------------------------------------------------------------------

