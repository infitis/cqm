//---------------------------------------------------------------------------
#ifndef fcustomvagonsviewerH
#define fcustomvagonsviewerH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"
#include <ComCtrls.hpp>
#include <DB.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"

//---------------------------------------------------------------------------
class TCustomVagonsViewerF : public TForm
{
__published:	// IDE-managed Components
    TDBGrid *G;
    TDataSource *DS;
    TStatusBar *Status;
    TZReadOnlyQuery *q;
    TIntegerField *qID;
    TFloatField *qP;
    TFloatField *qA;
    TTimeField *qVDATE;
private:	// User declarations
public:		// User declarations
    __fastcall TCustomVagonsViewerF(TComponent* Owner);
    int myvagonindex;
    void __fastcall Refresh(void);
    void __fastcall Init(int vid);
    void __fastcall LoadPosition(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TCustomVagonsViewerF *CustomVagonsViewerF;

//---------------------------------------------------------------------------
extern TCustomVagonsViewerF* VagonsViewers[MAX_CLIENT_VAGONS];
//---------------------------------------------------------------------------
#endif
