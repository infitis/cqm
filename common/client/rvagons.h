//----------------------------------------------------------------------------
#ifndef rvagonsH
#define rvagonsH

//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <Db.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>

//---------------------------------------------------------------------------
#include "..\windows\fdm.h"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//----------------------------------------------------------------------------
class TRepVagons : public TQuickRep
{
__published:
    TQRBand *QRBandTitle;
    TQRLabel *QRLTitle;
    TQRLabel *QRLMKU;
    TQRBand *QRBandCH;
    TQRLabel *QRLDT;
    TQRLabel *QRLW;
    TQRLabel *QRLA;
    TQRLabel *QRLrwD;
    TQRLabel *QRLVN;
    TQRLabel *QRLP;
    TQRLabel *QRLC;
    TQRLabel *QRLabel1;
    TQRBand *QRBandSummary;
    TQRLabel *QRLCount;
    TQRSysData *QRSysDataCount;
    TQRExpr *QRExprWeiSum;
    TQRExpr *QRExprAvgAsh;
    TQRDBText *QRDBCert;
    TQRDBText *QRDBpos;
    TQRDBText *QRDBvnum;
    TQRDBText *QRDBrwdate;
    TQRDBText *QRDBText3;
    TQRDBText *QRDBText2;
    TQRDBText *QRDBplace;
    TQRDBText *QRDBdt;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRDBText *QRDBText1;
    TQRDBText *QRDBText4;
    TQRExpr *QRExpr1;
    TZReadOnlyQuery *q;
    void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
private:
public:
   __fastcall TRepVagons::TRepVagons(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepVagons *RepVagons;

//----------------------------------------------------------------------------
void MakeRepVagons(void);

//----------------------------------------------------------------------------
#endif