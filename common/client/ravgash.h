//---------------------------------------------------------------------------
#ifndef ravgashH
#define ravgashH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "..\windows\fdm.h"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>

//---------------------------------------------------------------------------
class TAvgAshF : public TForm
{
__published:	// IDE-managed Components
   TLabel *L1;
   TLabel *L2;
   TLabel *LPlace;
   TLabel *LTime;
   TLabel *L3;
   TLabel *Label1;
   TLabel *LP;
   TLabel *LA;
   TButton *BOk;
private:	// User declarations
public:		// User declarations
   __fastcall TAvgAshF(TComponent* Owner);
};

//---------------------------------------------------------------------------
//extern PACKAGE TAvgAshF *AvgAshF;
void MakeAvgAshReport();

//---------------------------------------------------------------------------
#endif
