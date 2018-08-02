//----------------------------------------------------------------------------
#ifndef rminH
#define rminH

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
class TRepMin : public TQuickRep
{
__published:
    TQRBand *QRBand1;
    TQRLabel *QRLTitle;
    TQRLabel *QRLMKU;
    TQRBand *QRBCH;
    TQRLabel *QRLdt;
    TQRLabel *QRLp;
    TQRLabel *QRLa;
    TQRLabel *QRLdiag;
    TQRBand *QRBD;
    TQRDBText *QRDBdt;
    TQRDBText *QRDBp;
    TQRDBText *QRDBa;
    TQRDBText *QRDBdiag;
    TQRLabel *QRLTitle2;
    TZReadOnlyQuery *q;
    TQRShape *QRShape1;
    TDateTimeField *qMOMENT;
    TFloatField *qP;
    TFloatField *qA;
    TIntegerField *qDIAG;
private:
public:
   __fastcall TRepMin::TRepMin(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepMin *RepMin;

//----------------------------------------------------------------------------
void MakeRepMin(void);

//----------------------------------------------------------------------------
#endif