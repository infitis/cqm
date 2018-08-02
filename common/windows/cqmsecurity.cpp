//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "cqmsecurity.h"
#include "ide.h"

//---------------------------------------------------------------------------
//Определить cid с которым может работать этот билд
#define HIGH_SECURITY_CID 2354733609
//определить дату до которой можно запускать сервер
#define HIGH_SECURITY_LAST_DATE 20041001

//---------------------------------------------------------------------------
int CheckServerSecurity()
{
    unsigned long cid = getHardDriveComputerID();
    if (cid != HIGH_SECURITY_CID)
    {
        ShowMessage("Программное обеспечение защищено от копирования. Работа не возможна.");
        return 0;
    }
    int d = StrToInt(FormatDateTime("yyyymmdd", Now()));
    if (d>=HIGH_SECURITY_LAST_DATE || d<20040720)
    {
        ShowMessage("Истёк срок этой версии. Работа не возможна.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
