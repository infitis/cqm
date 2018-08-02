//---------------------------------------------------------------------------
#ifndef fplotterH
#define fplotterH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Series.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TPlotF : public TForm
{
__published:	// IDE-managed Components
    TChart *C;
    TPointSeries *Series1;
    TPointSeries *Series2;
    TPointSeries *Series3;
    TOpenDialog *OD;
    TMainMenu *MainMenu;
    TMenuItem *NFile;
    TMenuItem *NOpen;
    TMenuItem *NPrint;
    TMenuItem *N1;
    TMenuItem *NExit;
    TMenuItem *NPl;
    TMenuItem *NBuildColumn;
    TMenuItem *N2;
    TMenuItem *NDelAllSer;
    TStringGrid *G;
    TSplitter *Splitter;
    TPointSeries *Series4;
    TMenuItem *NBuildScale;
    TMenuItem *NDelLastSer;
    TMenuItem *NHelp;
    TMenuItem *NAbout;
    TMenuItem *NBuildSlice;
    void __fastcall BLoadClick(TObject *Sender);
    void __fastcall GSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall BMakeClick(TObject *Sender);
    void __fastcall BResetClick(TObject *Sender);
    void __fastcall BPrintClick(TObject *Sender);
    void __fastcall NExitClick(TObject *Sender);
    void __fastcall GDblClick(TObject *Sender);
    void __fastcall NBuildScaleClick(TObject *Sender);
    void __fastcall NDelLastSerClick(TObject *Sender);
    void __fastcall NAboutClick(TObject *Sender);
    void __fastcall NBuildSliceClick(TObject *Sender);
private:	// User declarations
    double scale;
    double last_entered_scale;
public:		// User declarations
    int selCol;
    int curSer;
    __fastcall TPlotF(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TPlotF *PlotF;

//---------------------------------------------------------------------------
TDateTime ExtractDateTime(AnsiString s);

//---------------------------------------------------------------------------
#endif
