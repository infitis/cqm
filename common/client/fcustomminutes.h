//---------------------------------------------------------------------------
#ifndef fcustomminutesH
#define fcustomminutesH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
#include "..\windows\fdm.h"
#include <DB.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"

//---------------------------------------------------------------------------
class TMinutesF : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel;
    TDBGrid *G;
    TDataSource *DS;
    TComboBox *CB;
    TLabel *L;
    TStatusBar *StatusBar;
    TPopupMenu *PopupMenu;
    TMenuItem *N1hour;
    TMenuItem *N6hours;
    TMenuItem *N1day;
    TZReadOnlyQuery *q;
    TMenuItem *N3day;
    TDateTimeField *qMOMENT;
    TFloatField *qP;
    TFloatField *qA;
    TIntegerField *qDIAG;
    void __fastcall N1hourClick(TObject *Sender);
    void __fastcall N6hoursClick(TObject *Sender);
    void __fastcall N1dayClick(TObject *Sender);
    void __fastcall qAfterScroll(TDataSet *DataSet);
    void __fastcall CBChange(TObject *Sender);
    void __fastcall N3dayClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TMinutesF(TComponent* Owner);
    AnsiString sqlwhere;
    AnsiString point;
    virtual void __fastcall Init(void);//в потомках метод заполнит строки в
                                       //комбобоксе.
    virtual void __fastcall Refresh(void);
    void __fastcall ShowStatus(void);//в потомках метод в зависимости
                                          //от значения комбобоса выберет
                                          //значения нужной точки коетроля
};
//---------------------------------------------------------------------------
extern PACKAGE TMinutesF *MinutesF;
//---------------------------------------------------------------------------
#endif
