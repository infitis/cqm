//---------------------------------------------------------------------------
#ifndef faccumsH
#define faccumsH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"
#include <Menus.hpp>

//---------------------------------------------------------------------------
typedef struct
{
    TLabel*   L;
    TEdit*    EA;
    TEdit*    EP;
} TAccumViewItem;

//---------------------------------------------------------------------------
class TAccumsF : public TForm
{
__published:	// IDE-managed Components
    TLabel *LAsh;
    TLabel *LWei;
    TPopupMenu *PM;
    TMenuItem *NSetEmpty;
    TMenuItem *NSet;
    void __fastcall NSetEmptyClick(TObject *Sender);
    void __fastcall NSetClick(TObject *Sender);
private:	// User declarations
    TAccumViewItem R[MAX_CLIENT_ACCUMULATORS];
public:		// User declarations
    __fastcall TAccumsF(TComponent* Owner);
    void Refresh(void);
    void BuildAccums(void);
    void ResetAccums(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TAccumsF *AccumsF;
extern int AccumsFEnabled;
int AccumsFInit(void);
void AccumsFKill(void);


//---------------------------------------------------------------------------
#endif
