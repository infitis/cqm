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
    TQRDBText *QRDBText1;
    TQRLabel *QRLabel1;
    TQRLabel *QRLabel8;
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel10;
    TQRDBText *QRDBText5;
    TQRDBText *QRDBText6;
    TQRDBText *QRDBText8;
    TQRLabel *QRLabel11;
    TQRLabel *QRLabel12;
    TQRLabel *QRLabel13;
    TZReadOnlyQuery *q;
    TDataSource *dsq;
    TQRGroup *QRGroup;
    TQRDBText *QRDBText7;
    TQRDBText *QRDBText9;
    TQRShape *QRShape2;
    TQRShape *QRShape3;
    TQRBand *QRBand1;
    TQRShape *QRShape1;
    void __fastcall QRDBText4Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText6Print(TObject *sender, AnsiString &Value);
private:
public:
   __fastcall TRepPos::TRepPos(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepPos *RepPos;

//----------------------------------------------------------------------------
void MakeRepPos(void);
void MakeRepPosMonth(void);

//----------------------------------------------------------------------------
#endif