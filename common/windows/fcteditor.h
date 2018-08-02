//---------------------------------------------------------------------------
#ifndef fcteditorH
#define fcteditorH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
#include "fdm.h"
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"

//---------------------------------------------------------------------------
class TCteF : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GBp;
    TGroupBox *GBr;
    TDataSource *dsp;
    TDBGrid *Gp;
    TDBNavigator *Np;
    TDataSource *dsr;
    TDBGrid *Gr;
    TDBNavigator *Nr;
    TGroupBox *GBt;
    TDataSource *dst;
    TDBGrid *Gt;
    TSpeedButton *SBDelete;
    TRadioGroup *RG1;
    TRadioButton *RBpos;
    TRadioButton *RBrank;
    TRadioButton *RBposrank;
    TSpeedButton *SpeedButton1;
    TRadioButton *RBall;
    TZTable *tp;
    TZTable *tr;
    TFloatField *tpa;
    TFloatField *tpw;
    TFloatField *trhhv;
    TFloatField *trk;
    TIntegerField *tpid;
    TStringField *tpname;
    TStringField *tpstation;
    TStringField *trname;
    TIntegerField *trID;
    TZQuery *tt;
    TStringField *ttPOSNAME;
    TStringField *ttCOALRANK;
    TIntegerField *ttCOALTYPE;
    TIntegerField *ttPOS_ID;
    TIntegerField *ttCOALRANK_ID;
    TGroupBox *GBAdd;
    TSpeedButton *SBAdd;
    TSpeedButton *SBAdd4r;
    TSpeedButton *SBAdd4p;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall tOnScroll(TDataSet *DataSet);
    void __fastcall RBposrankClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SBDeleteClick(TObject *Sender);
    void __fastcall SBAddClick(TObject *Sender);
    void __fastcall SBAdd4rClick(TObject *Sender);
    void __fastcall SBAdd4pClick(TObject *Sender);
    void __fastcall GtDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TCteF(TComponent* Owner);
    void __fastcall RefreshGrids(void);
    void __fastcall RefreshTypesGrid(void);
protected:
    bool __fastcall InputCoaltype(int &c);
};

//---------------------------------------------------------------------------
void ShowCtEditor(void);

//---------------------------------------------------------------------------
#endif
