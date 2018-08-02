//---------------------------------------------------------------------------
#ifndef findicH
#define findicH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"

//---------------------------------------------------------------------------
typedef struct
{
    TPanel*    Panel;
    TImage*    Image;
    TLabel*    Label;
    int state;
} TSigs;

//---------------------------------------------------------------------------
class TIndicatorF : public TForm
{
__published:	// IDE-managed Components
    TImage *Image0;
    TImage *Image1;
    TTimer *Timer;
    void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
    TSigs s[MAX_CLIENT_SIGNALS];
public:		// User declarations
    bool vis;//видимость формы    
    __fastcall TIndicatorF(TComponent* Owner);
    void __fastcall LoadPosition(void);
    void __fastcall Init(void);
    void __fastcall Refresh(void);
    void __fastcall Stop(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TIndicatorF *IndicatorF;

//---------------------------------------------------------------------------
#endif
