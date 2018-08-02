//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "LogFile.h"

//---------------------------------------------------------------------------
__fastcall TLogFile::TLogFile (AnsiString Dir, AnsiString Name, AnsiString Ext, char *Header)
:
    FileDir(Dir),FileName (Name),FileExt(Ext), FileHeader(Header)
{
    FileHeader.Trim();
    FileHeader += "\r\n";
    CreateLogFile();
}

//---------------------------------------------------------------------------
void __fastcall TLogFile::CreateLogFile()
{
	iFileName = FileDir + "\\"
    		 + ExtractFileName(FileName) + "_"
             + FormatDateTime("yyyy_mm_dd_hh_nn_ss", Now())
             + "." + FileExt;

    if (FileExists(iFileName))
    {
        DeleteFile (iFileName);
    }
    //Для возможности читать файл пока работает нить,
    //сначала создаём его,
    iFileHandle = FileCreate (iFileName);
    FileClose(iFileHandle);

    //а потом открываем для записи в него!
    iFileHandle = FileOpen (iFileName, fmOpenWrite|fmShareDenyWrite);
    FileSize = 0;
    if (iFileHandle)
        Active = true;
    if (FileHeader.Length() > 0)
        FileWrite (iFileHandle, FileHeader.c_str(), FileHeader.Length());
}

//---------------------------------------------------------------------------
void __fastcall TLogFile::CheckSize(int MsgSize)
{
    FileSize += MsgSize;
    if (FileSize > MAX_LOG_LENGTH)
    {
        FileClose (iFileHandle);
        Active = false;
        CreateLogFile();
    }
}

//---------------------------------------------------------------------------
__fastcall TLogFile::~TLogFile()
{
    FileClose (iFileHandle);
    Active = false;
}

//---------------------------------------------------------------------------
void __fastcall TLogFile::Add (AnsiString S)
{
    if (!Active) return;
    AddWithoutTime(FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz ", Now()) + S + "\r\n");
    //FileWrite (iFileHandle, Rec.c_str(), Rec.Length());
}

//---------------------------------------------------------------------------
void __fastcall TLogFile::AddWithoutTime (AnsiString S)
{
    if (!Active) return;
    FileWrite (iFileHandle, S.c_str(), S.Length());
    CheckSize(S.Length());
}

//---------------------------------------------------------------------------

