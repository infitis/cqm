//---------------------------------------------------------------------------
#ifndef foperhelpH
#define foperhelpH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TOperHelpF : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBoxNeed;
    TGroupBox *GroupBoxCur;
    TLabel *LNA;
    TLabel *LNP;
    TEdit *EAN;
    TEdit *EPN;
    TLabel *LCA;
    TLabel *LCP;
    TEdit *EAC;
    TEdit *EPC;
    TLabel *LNV;
    TLabel *L2;
    TLabel *L3;
    TLabel *L4;
    TPanel *PDiv;
    TEdit *EAK;
    TLabel *L5;
    TLabel *L6;
    TEdit *EPK;
    TEdit *EAP;
    TLabel *L7;
    TLabel *L8;
    TEdit *EPP;
    TLabel *LNAP;
    TLabel *L1;
    TLabel *L10;
    TLabel *L11;
    TLabel *L12;
    TLabel *L13;
    TLabel *L14;
    TLabel *L15;
    TSpeedButton *BFind;
    TSpeedButton *BCalc;
    TLabel *L9;
    void __fastcall BCalcClick(TObject *Sender);
    void __fastcall BFindClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int Kcoaltype;
    int Pcoaltype;
    int pid;
    bool autocalc;
    bool autogetvagon;
    bool vis;
    __fastcall TOperHelpF(TComponent* Owner);
    void __fastcall Refresh(void);
    void __fastcall Init(void);
    void __fastcall LoadPosition(void);
    void __fastcall Calc(bool autoc);
    void __fastcall Find(void);
    void __fastcall GetVagon(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TOperHelpF *OperHelpF;
extern int OperHelpFEnabled; 
void OperHelpFInit(void);
void OperHelpFKill(void);

//---------------------------------------------------------------------------
#endif
