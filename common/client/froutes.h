//---------------------------------------------------------------------------
#ifndef froutesH
#define froutesH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
#include "clientdata.h"

//---------------------------------------------------------------------------
typedef struct
{
    TLabel*   L;
    TEdit*    EA;
} TRouteViewItem;

//---------------------------------------------------------------------------
class TRoutesF : public TForm
{
__published:	// IDE-managed Components
    TLabel *LAsh;
private:	// User declarations
    TRouteViewItem R[MAX_CLIENT_ROUTES];
public:		// User declarations
    __fastcall TRoutesF(TComponent* Owner);
    void Refresh(void);
    void BuildRoutes(void);
    void ResetRoutes(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TRoutesF *RoutesF;
extern int RoutesFEnabled;
int RoutesFInit(void);
void RoutesFKill(void);

//---------------------------------------------------------------------------
#endif
