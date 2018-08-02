//---------------------------------------------------------------------------

#ifndef fmsgsH
#define fmsgsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "logfile.h"
//---------------------------------------------------------------------------
#define MAX_LINE_IN_MSGS	1024
#define MAX_LINE_IN_BUF 	1024
//---------------------------------------------------------------------------
class TMsgsF : public TForm
{
__published:	// IDE-managed Components
	TMemo *M;
private:	// User declarations
public:		// User declarations
	__fastcall TMsgsF(TComponent* Owner);
    __fastcall ~TMsgsF(void);
    TLogFile * log;
    TStringList * Buf;
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgsF *MsgsF;

//---------------------------------------------------------------------------
//��������� ����� �������
void DoMsg(AnsiString m);
//��������� ����������� �� ������ �� '\n';
void DoMiltiLineMsg(AnsiString m);
//��������� ����������� �� ������ �� '\n' � ����������� � ������;
void DoMsg2Buf(AnsiString m);
//����� ������
void DoFlushBuf(void);


//---------------------------------------------------------------------------
#endif
