//----------------------------------------------------------------------------
#ifndef fpswdH
#define fpswdH

//----------------------------------------------------------------------------
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ExtCtrls.hpp>

//----------------------------------------------------------------------------
class TPasswordDlg : public TForm
{
__published:
	TLabel *Label1;
	TEdit *Password;
	TButton *OKBtn;
	TButton *CancelBtn;
    TTimer *Timer;
    void __fastcall TimerTimer(TObject *Sender);
private:
public:
	virtual __fastcall TPasswordDlg(TComponent* AOwner);
};

//----------------------------------------------------------------------------
#define PASSWORD_SUCCESS     0
#define PASSWORD_NOT_SUCCESS 1
#define PASSWORD_TIMEOUT     2

int CheckPassword(AnsiString ACaption, AnsiString APassword);

//----------------------------------------------------------------------------
#endif    
