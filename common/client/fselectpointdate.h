//---------------------------------------------------------------------------
#ifndef fselectpointdateH
#define fselectpointdateH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"

//---------------------------------------------------------------------------
class TSelectPointDateF : public TForm
{
__published:	// IDE-managed Components
    TComboBox *CB;
    TLabel *L1;
    TGroupBox *GBDate;
    TDateTimePicker *DateP;
    TGroupBox *GBDateTime;
    TDateTimePicker *DateP1;
    TLabel *L2;
    TLabel *L3;
    TDateTimePicker *TimeP1;
    TDateTimePicker *TimeP2;
    TDateTimePicker *DateP2;
    TButton *BOk;
    TButton *BCancel;
private:	// User declarations
public:		// User declarations
    __fastcall TSelectPointDateF(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TSelectPointDateF *SelectPointDateF;

//---------------------------------------------------------------------------
bool SelectDate(TDate& d);
bool SelectClientDate(AnsiString title, clidata* data, int count, int& pointindex, TDate& d);
bool SelectClientDateTimeInterval
                     (AnsiString title, clidata* data, int count, int& pointindex, TDateTime& dt1, TDateTime& dt2);

//---------------------------------------------------------------------------
/*
bool SelectPointDate(int* pointindex, TDate* d);
bool SelectPointDateTimeInterval(int* pointindex, TDateTime* dt1, TDateTime* dt2);
*/
//---------------------------------------------------------------------------
#endif
