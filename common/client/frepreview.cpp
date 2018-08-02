//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "frepreview.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TRepPreviewF *RepPreviewF;

//---------------------------------------------------------------------------
void ReportPreview(TQuickRep* qr)
{
    RepPreviewF = new TRepPreviewF(Application);
    try
    {
        qr->Prepare();
        RepPreviewF->QRP->QRPrinter = qr->QRPrinter;
        RepPreviewF->ShowCaptionAndPages();
        RepPreviewF->ShowModal();
        delete qr->QRPrinter;
        qr->QRPrinter = NULL;
    }
    __finally
    {
        delete RepPreviewF;
    }
}

//---------------------------------------------------------------------------
__fastcall TRepPreviewF::TRepPreviewF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBCloseClick(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBZoomInClick(TObject *Sender)
{
    if (QRP->Zoom < 400)
        QRP->Zoom *= 1.2;
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBZoomOutClick(TObject *Sender)
{
    if (QRP->Zoom > 30)
    QRP->Zoom /= 1.2;
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBPrevClick(TObject *Sender)
{
    if (QRP->PreviewImage->PageNumber > 1)
    {
        QRP->PreviewImage->PageNumber = QRP->PreviewImage->PageNumber-1;
        ShowCaptionAndPages();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBNextClick(TObject *Sender)
{
    if (QRP->PreviewImage->PageNumber < QRP->QRPrinter->PageCount)
    {
        QRP->PreviewImage->PageNumber = QRP->PreviewImage->PageNumber+1;
        ShowCaptionAndPages();
    }
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::ShowCaptionAndPages(void)
{
    Caption = "Просмотр отчёта. Страницa : "+IntToStr(QRP->PreviewImage->PageNumber)+
              " из "+IntToStr(QRP->QRPrinter->PageCount);

    if (QRP->QRPrinter->PageCount == 1)
    {
        SBNext->Enabled = false;
        SBPrev->Enabled = false;
    }
    else
    if (QRP->PreviewImage->PageNumber == QRP->QRPrinter->PageCount)
    {
        SBNext->Enabled = false;
        SBPrev->Enabled = true;
    }
    else
    if (QRP->PreviewImage->PageNumber == 1)
    {
        SBNext->Enabled = true;
        SBPrev->Enabled = false;
    }
    else
    {
        SBNext->Enabled = true;
        SBPrev->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBPrinterTuneClick(TObject *Sender)
{
    QRP->QRPrinter->PrintSetup();
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::SBPrintClick(TObject *Sender)
{
    QRP->QRPrinter->Print();
}

//---------------------------------------------------------------------------
void __fastcall TRepPreviewF::ECChange(TObject *Sender)
{
    QRP->QRPrinter->Copies = StrToInt(EC->Text);
}

//---------------------------------------------------------------------------
