//---------------------------------------------------------------------------
#ifndef fcustomashgraphH
#define fcustomashgraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <Series.hpp>
#include <Menus.hpp>
#include <DbChart.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"

//---------------------------------------------------------------------------
class TCustomAshGraphF : public TForm
{
__published:	// IDE-managed Components
    TDBChart *DBChart;
    TPanel *P;
    TLabel *LabelAName;
    TLabel *LabelDName;
    TLabel *LA;
    TLabel *LD;
    TPopupMenu *PopupMenu;
    TMenuItem *N1hour;
    TMenuItem *N6hours;
    TMenuItem *N1Day;
    TMenuItem *N1;
    TMenuItem *NGeneral;
    TMenuItem *NSliding;
    TMenuItem *N2;
    TMenuItem *NPrint;
    TPointSeries *Series1;
    TLabel *LPerc;
    TPointSeries *Series2;
    TZReadOnlyQuery *q;
    TZReadOnlyQuery *qvag;
    TMenuItem *NSliding6;
    void __fastcall N1hourClick(TObject *Sender);
    void __fastcall N6hoursClick(TObject *Sender);
    void __fastcall N1DayClick(TObject *Sender);
    void __fastcall NGeneralClick(TObject *Sender);
    void __fastcall NSlidingClick(TObject *Sender);
    void __fastcall NPrintClick(TObject *Sender);
    void __fastcall NSliding6Click(TObject *Sender);
private:
protected:
    void __fastcall LoadIntervals(void);	// User declarations
    inline bool __fastcall GetCurrentAsh(AnsiString a);
    int smooth;
public:		// User declarations
    int mypointindex;
    int myvagonindex;
    AnsiString sqlwhat;
    AnsiString sqlwhen;
    TDateTime  chartinterval;
    double Amin;
    double Amax;
    int diag;
    __fastcall TCustomAshGraphF(TComponent* Owner);
    __fastcall virtual ~TCustomAshGraphF(void);
    void __fastcall Refresh(void);
    void __fastcall Init(int pid);
    void __fastcall LoadPosition(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TCustomAshGraphF *CustomAshGraphF;

//---------------------------------------------------------------------------
extern TCustomAshGraphF* AshGraphs[MAX_CLIENT_POINTS];

//---------------------------------------------------------------------------
#endif
