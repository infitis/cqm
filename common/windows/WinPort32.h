#ifndef WINPORT_32
#define WINPORT_32

#include <windows.h>
#include <winioctl.h>


//---------------------------------------------------------------------------
class TWinPort
{
protected:
bool WinNT;
HANDLE hDriver;
bool error;
bool GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize);
bool SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize);
public:

TWinPort();
~TWinPort();

bool Installed() {return !WinNT || hDriver;}

bool Install();
bool Remove();

byte ReadByte(WORD adr);
WORD ReadWord(WORD adr);
DWORD ReadDWord(WORD adr);

void WriteByte(WORD adr, byte);
void WriteWord(WORD adr,WORD);
void WriteDWord(WORD adr,DWORD);


bool Error() {return error;}
void ErrorMessage(char *buffer, int maxlen);
};
//---------------------------------------------------------------------------
#endif	//WINPORT32
