//---------------------------------------------------------------------------
#ifndef frepreviewH
#define frepreviewH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <QRPrntr.hpp>
#include <QuickRpt.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class TRepPreviewF : public TForm
{
__published:	// IDE-managed Components
    TToolBar *ToolBar;
    TQRPreview *QRP;
    TSpeedButton *SBPrev;
    TToolButton *ToolButton1;
    TSpeedButton *SBNext;
    TToolButton *ToolButton2;
    TSpeedButton *SBZoomIn;
    TToolButton *ToolButton3;
    TSpeedButton *SBZoomOut;
    TToolButton *ToolButton4;
    TSpeedButton *SBPrinterTune;
    TToolButton *ToolButton5;
    TSpeedButton *SBPrint;
    TPanel *P;
    TToolButton *ToolButton6;
    TLabel *LCou;
    TEdit *EC;
    TUpDown *UpDown;
    TToolButton *ToolButton7;
    TSpeedButton *SBClose;
    void __fastcall SBCloseClick(TObject *Sender);
    void __fastcall SBZoomInClick(TObject *Sender);
    void __fastcall SBZoomOutClick(TObject *Sender);
    void __fastcall SBPrevClick(TObject *Sender);
    void __fastcall SBPrinterTuneClick(TObject *Sender);
    void __fastcall SBPrintClick(TObject *Sender);
    void __fastcall ECChange(TObject *Sender);
    void __fastcall SBNextClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TRepPreviewF(TComponent* Owner);
    void __fastcall ShowCaptionAndPages(void);
    
};

//---------------------------------------------------------------------------
extern PACKAGE TRepPreviewF *RepPreviewF;
void ReportPreview(TQuickRep* qr);

//---------------------------------------------------------------------------
#endif
