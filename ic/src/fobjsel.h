//---------------------------------------------------------------------------
#ifndef fobjselH
#define fobjselH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
#include "CqmObjPanel.h"
#include "cqmicdispatcher.h"

//---------------------------------------------------------------------------
class TObjSelF : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
    int CqmObjectCount;
public:		// User declarations
    TCqmObjPanel* CqmObjects[MAX_CQM_REMOTE_OBJECTS];
    __fastcall TObjSelF(TComponent* Owner);
    __fastcall ~TObjSelF();
    void Init(void);
    void Refresh(void);
    void __fastcall ObjActivated(TObject * Sender);
    void __fastcall ObjDeActivated(TObject * Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TObjSelF *ObjSelF;
//---------------------------------------------------------------------------
#endif
