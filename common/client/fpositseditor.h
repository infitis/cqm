//---------------------------------------------------------------------------
#ifndef fpositseditorH
#define fpositseditorH

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
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"

//---------------------------------------------------------------------------
class TPositsEditorF : public TForm
{
__published:	// IDE-managed Components
    TDataSource *DS;
    TDBGrid *G;
    TToolBar *ToolBar;
    TSpeedButton *SBNewP;
    TToolButton *ToolButton1;
    TSpeedButton *SBDelP;
    TToolButton *ToolButton2;
    TSpeedButton *SBFindV;
    TEdit *EF;
    TDBNavigator *DBNavigator;
    TToolButton *ToolButton3;
    TSpeedButton *SBRefresh;
    TToolButton *ToolButton4;
    TZTable *t;
    TIntegerField *tid;
    TStringField *tname;
    TStringField *tstation;
    TFloatField *ta;
    TFloatField *tw;
    void __fastcall SBRefreshClick(TObject *Sender);
    void __fastcall SBDelPClick(TObject *Sender);
    void __fastcall SBNewPClick(TObject *Sender);
    void __fastcall tAfterPost(TDataSet *DataSet);
    void __fastcall SBFindVClick(TObject *Sender);
    void __fastcall EFKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TPositsEditorF(TComponent* Owner);
    void __fastcall Init(void);
    void __fastcall Stop(void);
    void __fastcall Refresh(void);
    
};

//---------------------------------------------------------------------------
extern PACKAGE TPositsEditorF *PositsEditorF;

//---------------------------------------------------------------------------
#endif
