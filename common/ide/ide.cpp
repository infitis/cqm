//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <registry.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ide.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
extern AnsiString AppIniFileName;

//---------------------------------------------------------------------------
AnsiString GetHDSN ()
{
   for (int controller = 0; controller < 2; controller++)
   {
      HANDLE hScsiDriveIOCTL;
      char   driveName [256];

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      sprintf (driveName, "\\\\.\\Scsi%d:", controller);

         //  Windows NT, Windows 2000, any rights should do
      hScsiDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
      /*if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
        throw Exception (AnsiString("").sprintf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
            controller, GetLastError ()));*/

      if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         unsigned int drive;

         for (drive = 0; drive < 2; drive++)
         {
            char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
            SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
            SENDCMDINPARAMS *pin =
                   (SENDCMDINPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
            DWORD dummy;

            memset (buffer, 0, sizeof (buffer));
            p -> HeaderLength = sizeof (SRB_IO_CONTROL);
            p -> Timeout = 10000;
            p -> Length = SENDIDLENGTH;
            p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
            strncpy ((char *) p -> Signature, "SCSIDISK", 8);

            pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
            pin -> bDriveNumber = drive;

            BOOL Result =
                DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT,
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) +
                                         sizeof (SENDCMDINPARAMS) - 1,
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
                                 &dummy, NULL);
            if (Result)
            {
               SENDCMDOUTPARAMS *pOut =
                    (SENDCMDOUTPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
               IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
               if (pId -> sModelNumber [0])
               {
                  DWORD diskdata [256];
                  USHORT *pIdSector = (USHORT *) pId;
                  for (int ijk = 0; ijk < 256; ijk++)
                     diskdata [ijk] = pIdSector [ijk];

                  CloseHandle (hScsiDriveIOCTL);
                  return ConvertToString (diskdata, 10, 19);

               }
            }
         }
         CloseHandle (hScsiDriveIOCTL);
      }
   }
   throw Exception ("Внутренняя ошибка E000: свяжитесь с разработчиком.");
}
//---------------------------------------------------------------------------
AnsiString ConvertToString (DWORD diskdata [256], int firstIndex, int lastIndex)
{
    char s [1024];
    int position = 0;

     //  each integer has two characters stored in it backwards
    for (int index = firstIndex; index <= lastIndex; index++)
    {
          //  get high byte for 1st character
       s [position] = (char) (diskdata [index] / 256);
       position++;

          //  get low byte for 2nd character
       s [position] = (char) (diskdata [index] % 256);
       position++;
    }

       //  end the string
    s [position] = '\0';

       //  cut off the trailing blanks
    for (int index = position - 1; index > 0 && ' ' == s [index]; index--)
       s [index] = '\0';

    return AnsiString(s);
}
//---------------------------------------------------------------------------
unsigned long getHardDriveComputerID ()
{
    unsigned __int64 id = 0;

      //  this should work in WinNT or Win2K if previous did not work
      //  this is kind of a backdoor via the SCSI mini port driver into
      //     the IDE drives
    AnsiString HDSerialNumber = GetHDSN();

    char cHDSN[1024];
    strcpy (cHDSN, HDSerialNumber.c_str());
    char *p = cHDSN;

       //  ignore first 5 characters from western digital hard drives if
       //  the first four characters are WD-W
    if ( ! strncmp (cHDSN, "WD-W", 4)) p += 5;
    for ( ; p && *p; p++)
    {
       //if ('-' == *p) continue;
       if (!isdigit(*p) && !isalpha(*p)) continue;
       id *= 36;
       switch (*p)
       {
          case '0': id += 0; break;
          case '1': id += 1; break;
          case '2': id += 2; break;
          case '3': id += 3; break;
          case '4': id += 4; break;
          case '5': id += 5; break;
          case '6': id += 6; break;
          case '7': id += 7; break;
          case '8': id += 8; break;
          case '9': id += 9; break;
          case 'a': case 'A': id += 10; break;
          case 'b': case 'B': id += 11; break;
          case 'c': case 'C': id += 12; break;
          case 'd': case 'D': id += 13; break;
          case 'e': case 'E': id += 14; break;
          case 'f': case 'F': id += 15; break;
          case 'g': case 'G': id += 16; break;
          case 'h': case 'H': id += 17; break;
          case 'i': case 'I': id += 18; break;
          case 'j': case 'J': id += 19; break;
          case 'k': case 'K': id += 20; break;
          case 'l': case 'L': id += 21; break;
          case 'm': case 'M': id += 22; break;
          case 'n': case 'N': id += 23; break;
          case 'o': case 'O': id += 24; break;
          case 'p': case 'P': id += 25; break;
          case 'q': case 'Q': id += 26; break;
          case 'r': case 'R': id += 27; break;
          case 's': case 'S': id += 28; break;
          case 't': case 'T': id += 29; break;
          case 'u': case 'U': id += 30; break;
          case 'v': case 'V': id += 31; break;
          case 'w': case 'W': id += 32; break;
          case 'x': case 'X': id += 33; break;
          case 'y': case 'Y': id += 34; break;
          case 'z': case 'Z': id += 35; break;
       }
    }
      //   make sure no bigger than 16^8-1
    if (id > 0xffffffffu) id %= 0x100000000u;
    return (unsigned long)id;
}
//---------------------------------------------------------------------------
bool CheckCId(bool canQuery)
{
    unsigned long realCId = getHardDriveComputerID();
    AnsiString CIdS("");
    unsigned long CId=0;
    //ищем в ини
    TIniFile *IniFile;

    try {
    IniFile = new TIniFile(AppIniFileName);

    if (IniFile->ValueExists ("CID", "CIDValue"))
    {
        CIdS = IniFile->ReadString ("CID", "CIDValue", "");
        sscanf (CIdS.c_str(), "%lu", &CId);
        if (CId == realCId)
            return true;
    }
    CIdS="";
    //в ини нет, ищем в windir\\cid.key
    char WinDir[144];
    int FileHandle;

    GetWindowsDirectory(WinDir, sizeof(WinDir));
    AnsiString FileName = AnsiString(WinDir)+CIDKEYFILENAME;
    if (FileExists(FileName))
    {
        FileHandle = FileOpen(FileName, fmOpenRead);
        char buf[32];
        FileRead(FileHandle, buf, sizeof(buf));
        FileClose(FileHandle);
        sscanf (buf, "%lu", &CId);
        if (CId == realCId)
        {
            AnsiString S("");
            S.printf("%lu", CId);
            IniFile->WriteString ("CID", "CIDValue", S);
            return true;
        }
    }

    if (!canQuery)
        return false;
    if (!InputQuery ("МКУ Сервер", "Введите ключ:", CIdS))
        return false;
    sscanf (CIdS.c_str(), "%lu", &CId);
    if (CId != realCId)
        return false;
    AnsiString S("");
    S.printf("%lu", CId);
    IniFile->WriteString ("CID", "CIDValue", S);
    } __finally { delete IniFile;}
    return true;
}
//---------------------------------------------------------------------------

