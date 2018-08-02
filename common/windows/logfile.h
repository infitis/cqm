//---------------------------------------------------------------------------
#ifndef LogFileH
#define LogFileH

//---------------------------------------------------------------------------
extern AnsiString LogDir;

//---------------------------------------------------------------------------
#define MAX_LOG_LENGTH 3000000

//---------------------------------------------------------------------------
class TLogFile
{
protected:
    AnsiString FileDir;
    AnsiString FileName;
    AnsiString FileExt;
    AnsiString iFileName;
    AnsiString FileHeader;
    int FileSize;
public:
    __fastcall TLogFile (AnsiString Dir, AnsiString Name, AnsiString Ext, char *Header=NULL);
    __fastcall ~TLogFile ();
    void __fastcall Add (AnsiString S);
    inline void __fastcall AddWithoutTime (AnsiString S);
    int iFileHandle;
    bool Active;
private:
    inline void __fastcall CreateLogFile();
    inline void __fastcall CheckSize(int MsgSize);
};

//---------------------------------------------------------------------------
#endif
