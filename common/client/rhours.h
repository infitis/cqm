//----------------------------------------------------------------------------
#ifndef rhoursH
#define rhoursH

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
class TRepHours : public TQuickRep
{
__published:
    TQRBand *QRBandTitle;
    TQRLabel *QRLTitle;
    TQRBand *QRBand2;
    TQRLabel *QRLabel1;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRLabel *QRLMKU;
    TQRBand *QRBand3;
    TQRDBText *QRDBText1;
    TQRDBText *QRDBText2;
    TQRDBText *QRDBText3;
    TQRDBText *QRDBText4;
    TQRLabel *QRLMainTitle;
    TZReadOnlyQuery *q;
    TQRShape *QRShape1;
    void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText3Print(TObject *sender, AnsiString &Value);
private:
public:
   __fastcall TRepHours::TRepHours(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepHours *RepHours;

//----------------------------------------------------------------------------
void MakeRepDayPoints(void);
void MakeRepDayRoutes(void);
//----------------------------------------------------------------------------
#endif