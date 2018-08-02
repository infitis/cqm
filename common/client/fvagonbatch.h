//---------------------------------------------------------------------------
#ifndef fvagonbatchH
#define fvagonbatchH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TCustomVagonsEditorF;

//---------------------------------------------------------------------------
class TVagonBatchF : public TForm
{
__published:	// IDE-managed Components
    TButton *BOk;
    TButton *BCancel;
    TLabel *LVBN;
    TEdit *EBatchNum;
    TLabel *LRWD;
    TLabel *Label1;
    TComboBox *CBPos;
    TLabel *LCR;
    TComboBox *CBRank;
    TLabel *LP;
    TLabel *LH;
    TEdit *EP;
    TEdit *EH;
    TLabel *LVN;
    TEdit *EVN;
    TSpeedButton *SBnoPos;
    TSpeedButton *SBnoRank;
    TLabel *L1;
    TLabel *L2;
    TDateTimePicker *ERWD;
    TSpeedButton *SpeedButton1;
    void __fastcall BOkClick(TObject *Sender);
    void __fastcall BCancelClick(TObject *Sender);
    void __fastcall SBnoPosClick(TObject *Sender);
    void __fastcall SBnoRankClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
private:
    AnsiString __fastcall CheckFields(void);	// User declarations
public:		// User declarations
    __fastcall TVagonBatchF(TComponent* Owner);
    void FillPos(int pos=-1);
    void FillRanks(AnsiString rank="");
    void FillFields(void);
    int batchNum;
    TDate rwDate;
    int posNum;
    int vagNum;
    AnsiString coalRank;
    double batchWei;
    double batchHum;
};

//---------------------------------------------------------------------------
extern PACKAGE TVagonBatchF *VagonBatchF;
int NewBatch(int& batchNumber, TCustomVagonsEditorF* editor);
int EditBatch(int batchNumber, TCustomVagonsEditorF* editor);

//---------------------------------------------------------------------------
#endif
