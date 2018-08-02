//----------------------------------------------------------------------------
#ifndef rintervalsH
#define rintervalsH

//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>

//----------------------------------------------------------------------------
#include "fdm.h"
#include <Db.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//----------------------------------------------------------------------------
class TRepIntervals : public TQuickRep
{
__published:
    TQRBand *QRBandTitle;
    TQRLabel *QRLTitle;
    TQRLabel *QRLMKU;
    TQRLabel *QRLMainTitle;
    TQRBand *QRBand2;
    TQRLabel *QRLabel1;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRBand *QRBand3;
    TQRDBText *QRDBdt1;
    TQRDBText *QRDBText2;
    TQRDBText *QRDBText3;
    TQRLabel *QRLabel4;
    TQRDBText *QRDBdt2;
    TZReadOnlyQuery *q;
    TQRShape *QRShape1;
    void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText3Print(TObject *sender, AnsiString &Value);
private:
public:
   __fastcall TRepIntervals::TRepIntervals(TComponent* Owner);
};

//----------------------------------------------------------------------------
void MakeRepIntervalsRoutes(void);

//----------------------------------------------------------------------------
#endif