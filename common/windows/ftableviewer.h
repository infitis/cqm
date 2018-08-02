//---------------------------------------------------------------------------

#ifndef ftableviewerH
#define ftableviewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
class TTableViewer : public TForm
{
__published:	// IDE-managed Components
    TDBGrid *G;
    TImageList *IL;
    TToolBar *ToolBar;
    TToolButton *TBRefresh;
    TToolButton *TBS2;
    TToolButton *TBFilter;
    TToolButton *TBRFilter;
    TToolButton *TBSort;
    TToolButton *TBRSort;
    TToolButton *TBTimeSort;
    TToolButton *TBFind;
    TToolButton *TBS6;
    TToolButton *TBCancel;
    TDBNavigator *Navigator;
    TToolButton *TBS7;
    TDataSource *DS;
    TActionList *ActionList;
    TAction *ActionRefreshGrid;
    TAction *ActionFilter;
    TAction *ActionRFilter;
    TAction *ActionSort;
    TAction *ActionRSort;
    TAction *ActionTimeFind;
    TAction *ActionFind;
    TAction *ActionCancel;
    TStatusBar *StatusBar;
    TPopupMenu *PopupMenu;
    TMenuItem *N1hour;
    TMenuItem *N6hours;
    TMenuItem *N1day;
    TMenuItem *NAll;
    TZQuery *t;
    void __fastcall TBRefreshClick(TObject *Sender);
    void __fastcall TBFilterClick(TObject *Sender);
    void __fastcall TBCancelClick(TObject *Sender);
    void __fastcall TBRFilterClick(TObject *Sender);
    void __fastcall TBSortClick(TObject *Sender);
    void __fastcall TBRSortClick(TObject *Sender);
    void __fastcall TBFindClick(TObject *Sender);
    void __fastcall TBTimeSortClick(TObject *Sender);
    void __fastcall N1hourClick(TObject *Sender);
    void __fastcall N6hoursClick(TObject *Sender);
    void __fastcall N1dayClick(TObject *Sender);
    void __fastcall NAllClick(TObject *Sender);
private:	// User declarations
    AnsiString tTableName;
    AnsiString tWhereFilter;
    AnsiString tIntervalFilter;
    AnsiString tSortedFields;
    AnsiString FloatFieldDisplayFormat;
public:		// User declarations
    __fastcall TTableViewer(TComponent* Owner);
    virtual void RefreshGrid(void);
    int intervaltype;
    void SetIntervalFilter(int it);
    void SetTable(AnsiString name);
};

//---------------------------------------------------------------------------
extern PACKAGE TTableViewer *TableViewer;

//---------------------------------------------------------------------------
#endif
