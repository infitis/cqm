//----------------------------------------------------------------------------
#ifndef rashgraphH
#define rashgraphH

//----------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\QuickRpt.hpp>
#include <vcl\QRCtrls.hpp>
#include <Db.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QrTee.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>

//---------------------------------------------------------------------------
#include "..\windows\fdm.h"
#include <DbChart.hpp>
#include <QRTEE.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//----------------------------------------------------------------------------
class TRepAshGraph : public TQuickRep
{
__published:
    TQRBand *QRBandTitle;
    TQRLabel *QRLTitle;
    TQRLabel *QRLMKU;
    TQRDBChart *QRDBChart1;
    TQRChart *QRChart;
    TPointSeries *Series1;
    TPointSeries *Series2;
    TZReadOnlyQuery *q;
    TZReadOnlyQuery *qvag;
private:
public:
   __fastcall TRepAshGraph::TRepAshGraph(TComponent* Owner);
};

//----------------------------------------------------------------------------
extern TRepAshGraph *RepAshGraph;

//----------------------------------------------------------------------------
void MakeAshGraph(void);
void MakeRouteGraph(void);

//----------------------------------------------------------------------------
#endif