//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "cqmsecurity.h"
#include "ide.h"

//---------------------------------------------------------------------------
//���������� cid � ������� ����� �������� ���� ����
#define HIGH_SECURITY_CID 2354733609
//���������� ���� �� ������� ����� ��������� ������
#define HIGH_SECURITY_LAST_DATE 20041001

//---------------------------------------------------------------------------
int CheckServerSecurity()
{
    unsigned long cid = getHardDriveComputerID();
    if (cid != HIGH_SECURITY_CID)
    {
        ShowMessage("����������� ����������� �������� �� �����������. ������ �� ��������.");
        return 0;
    }
    int d = StrToInt(FormatDateTime("yyyymmdd", Now()));
    if (d>=HIGH_SECURITY_LAST_DATE || d<20040720)
    {
        ShowMessage("���� ���� ���� ������. ������ �� ��������.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
