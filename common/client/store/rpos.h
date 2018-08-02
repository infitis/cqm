//----------------------------------------------------------------------------
#ifndef rposH
#define rposH

//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <Db.hpp>

//---------------------------------------------------------------------------
#include "..\windows\fdm.h"
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//----------------------------------------------------------------------------
class TRepPos : public TQuickRep
{
__published:
    TQRBand *QRBandTitle;
    TQRLabel *QRLTitle;
    TQRLabel *QRLMKU;
    TQRBand *QRBandSummary;
    TQRLabel *QRLCount;
    TQRBand *QRBandCH;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRLabel *QRLabel7;
    TQRLabel *QRLabel5;
    TQRLabel *QRLabel6;
    TQRBand *DetailBand;
    TQRDBText *QRDBText2;
    TQRDBText *QRDBText3;
    TQRDBText *QRDBText4;
    TQRDBText *QRDBText7;
    TQRDBText *QRDBText1;
    TQRLabel *QRLAN;
    TQRLabel *QRLAP;
    TQRLabel *QRLAA;
    TQRLabel *QRLabel1;
    TQRLabel *QRLabel8;
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel10;
    TQRDBText *QRDBText5;
    TQRDBText *QRDBText6;
    TQRDBText *QRDBText8;
    TQRLabel *QRLAW;
    TQRLabel *QRLAQ;
    TQRLabel *QRLabel11;
    TQRLabel *QRLabel12;
    TQRLabel *QRLabel13;
    TQRLabel *QRLabel14;
    TQRLabel *QRLMN;
    TQRLabel *QRLMP;
    TQRLabel *QRLMA;
    TQRLabel *QRLMW;
    TZReadOnlyQuery *q;
    TQRShape *QRShape1;
    TZReadOnlyQuery *qpos;
    TDataSource *dsq;
    TQRDBText *QRDBText9;
private:
public:
   __fastcall TRepPos::TRepPos(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepPos *RepPos;

//----------------------------------------------------------------------------
void MakeRepPos(void);

//----------------------------------------------------------------------------
#endif