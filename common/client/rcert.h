//----------------------------------------------------------------------------
#ifndef rcertH
#define rcertH

//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <Db.hpp>

//----------------------------------------------------------------------------
#include "..\windows\fdm.h"
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//----------------------------------------------------------------------------
class TRepCert : public TQuickRep
{
__published:
    TQRBand *QRBCH;
    TQRBand *QRBDet;
    TQRBand *QRBF;
    TQRMemo *QRMDate;
    TQRDBText *QRDBTextDate;
    TQRMemo *QRMemoRW;
    TQRMemo *QRMemoWei;
    TQRMemo *QRMemoVag;
    TQRMemo *QRMemoNakl;
    TQRDBText *QRDBTextNumber;
    TQRLabel *QRLabelEmpty1;
    TQRDBText *QRDBTextWei;
    TQRMemo *QRMemoNames;
    TQRMemo *QRMemoNPotr;
    TQRMemo *QRMemoNStat;
    TQRLabel *QRLabelEmpty2;
    TQRLabel *QRLabelEmpty3;
    TQRSysData *QRSysData1;
    TQRExpr *QRExpr1;
    TQRMemo *MemoPosName;
    TQRMemo *MemoPosStat;
    TQRMemo *QRMemoScript;
    TQRMemo *QRMemoVNo;
    TQRMemo *QRMemoSumWei;
    TQRLabel *QRLabelCopy;
    TQRShape *QRShape1;
    TQRShape *QRShape2;
    TQRShape *QRShape3;
    TZReadOnlyQuery *q;
private:
public:
   __fastcall TRepCert::TRepCert(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern void MakeRepCert(void);

//----------------------------------------------------------------------------
#endif