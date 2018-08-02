//---------------------------------------------------------------------------
#ifndef fcustomvagonseditorH
#define fcustomvagonseditorH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ToolWin.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"

//---------------------------------------------------------------------------
class TCustomVagonsEditorF : public TForm
{
__published:	// IDE-managed Components
    TDataSource *DS;
    TToolBar *ToolBar;
    TDBGrid *G;
    TDBNavigator *DBNavigator;
    TPopupMenu *PopupMenu;
    TMenuItem *N2days;
    TMenuItem *N1month;
    TMenuItem *N1year;
    TSpeedButton *SBNewV;
    TSpeedButton *SBMergeV;
    TStatusBar *Status;
    TSpeedButton *SBMergeCust;
    TPanel *PMergeCust;
    TLabel *LN1;
    TLabel *LN2;
    TEdit *E1;
    TEdit *E2;
    TSpeedButton *SBDelV;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TSpeedButton *SBFindV;
    TEdit *EF;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton5;
    TToolBar *ToolBarVB;
    TSpeedButton *SBNewBatch;
    TToolButton *ToolButton6;
    TSpeedButton *SpeedButton1;
    TZQuery *q;
    TIntegerField *qID;
    TDateTimeField *qMOMENT;
    TStringField *qVNAME;
    TIntegerField *qCOALTYPE;
    TFloatField *qP;
    TFloatField *qA;
    TIntegerField *qMP;
    TFloatField *qLNFP;
    TFloatField *qWEI;
    TFloatField *qW;
    TDateField *qRWDATE;
    TIntegerField *qNUMBER;
    TIntegerField *qPOS;
    TIntegerField *qCERT;
    TIntegerField *qCOALRANK;
    TStringField *qCOALRANK_L;
    TZReadOnlyQuery *qcoalranks;
    void __fastcall N2daysClick(TObject *Sender);
    void __fastcall N1monthClick(TObject *Sender);
    void __fastcall N1yearClick(TObject *Sender);
    void __fastcall tAfterPost(TDataSet *DataSet);
    void __fastcall tAfterScroll(TDataSet *DataSet);
    void __fastcall SBNewVClick(TObject *Sender);
    void __fastcall SBMergeVClick(TObject *Sender);
    void __fastcall GDblClick(TObject *Sender);
    void __fastcall SBMergeCustClick(TObject *Sender);
    void __fastcall SBFindVClick(TObject *Sender);
    void __fastcall EFKeyPress(TObject *Sender, char &Key);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SBNewBatchClick(TObject *Sender);
    void __fastcall SBDelVMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall GKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
    AnsiString qWhereFilter;
    AnsiString qSortedFields;
    inline void __fastcall LocateVagon(int wasid);
public:		// User declarations
    __fastcall TCustomVagonsEditorF(TComponent* Owner);
    int myvagonindex;
    TDateTime dt;
    void __fastcall Refresh(int rid = 0);
    void __fastcall Init(int vid);
    void __fastcall LoadPosition(void);
    void __fastcall ShowStatus(void);
    void __fastcall AddVagon(void);
    void __fastcall MergeVagons(int id1, int id2);
};
//---------------------------------------------------------------------------
extern PACKAGE TCustomVagonsEditorF *CustomVagonsEditorF;

//---------------------------------------------------------------------------
extern TCustomVagonsEditorF* VagonsEditors[MAX_CLIENT_VAGONS];

//---------------------------------------------------------------------------
#endif
