#include <windows.h>
#include <winioctl.h>
//---------------------------------------------------------------------------
#pragma hdrstop

#include "WinPort32.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-32767, and 32768-65535 are reserved for use
// by customers.

#define FILE_DEVICE_WINIO 0x00008010

// Macro definition for defining IOCTL and FSCTL function control codes.
// Note that function codes 0-2047 are reserved for Microsoft Corporation,
// and 2048-4095 are reserved for customers.

#define WINIO_IOCTL_INDEX 0x810

// Define our own private IOCTL

#define IOCTL_WINIO_MAPPHYSTOLIN  CTL_CODE(FILE_DEVICE_WINIO,  \
                                  WINIO_IOCTL_INDEX,      \
                                  METHOD_BUFFERED,        \
                                  FILE_ANY_ACCESS)

#define IOCTL_WINIO_UNMAPPHYSADDR CTL_CODE(FILE_DEVICE_WINIO,  \
                                  WINIO_IOCTL_INDEX + 1,  \
                                  METHOD_BUFFERED,        \
                                  FILE_ANY_ACCESS)

#define IOCTL_WINIO_WRITEPORT     CTL_CODE(FILE_DEVICE_WINIO,  \
                                  WINIO_IOCTL_INDEX + 2,   \
                                  METHOD_BUFFERED,         \
                                  FILE_ANY_ACCESS)

#define IOCTL_WINIO_READPORT      CTL_CODE(FILE_DEVICE_WINIO,  \
                                  WINIO_IOCTL_INDEX + 3,   \
                                  METHOD_BUFFERED,         \
                                  FILE_ANY_ACCESS)

struct tagPhys32Struct
{
  HANDLE PhysicalMemoryHandle;
  ULONG dwPhysMemSizeInBytes;
  PVOID pvPhysAddress;
  PVOID pvPhysMemLin;
};

//extern struct tagPhys32Struct Phys32Struct;

struct tagPort32Struct
{
  USHORT wPortAddr;
  ULONG dwPortVal;
  UCHAR bSize;
};

/****************************************************************************
*
*    FUNCTION: InstallDriver( IN SC_HANDLE, IN LPCTSTR, IN LPCTSTR)
*
*    PURPOSE: Creates a driver service.
*
****************************************************************************/
BOOL InstallDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName, IN LPCTSTR ServiceExe )
{
    SC_HANDLE  schService;

    //
    // NOTE: This creates an entry for a standalone driver. If this
    //       is modified for use with a driver that requires a Tag,
    //       Group, and/or Dependencies, it may be necessary to
    //       query the registry for existing driver information
    //       (in order to determine a unique Tag, etc.).
    //

    schService = CreateService( SchSCManager,          // SCManager database
                                DriverName,           // name of service
                                DriverName,           // name to display
                                SERVICE_ALL_ACCESS,    // desired access
                                SERVICE_KERNEL_DRIVER, // service type
                                SERVICE_AUTO_START,	//SERVICE_DEMAND_START,  // start type
                                SERVICE_ERROR_NORMAL,  // error control type
                                ServiceExe,            // service's binary
                                NULL,                  // no load ordering group
                                NULL,                  // no tag identifier
                                NULL,                  // no dependencies
                                NULL,                  // LocalSystem account
                                NULL                   // no password
                                );
    if ( schService == NULL )
        return FALSE;

    CloseServiceHandle( schService );

    return TRUE;
}


/****************************************************************************
*
*    FUNCTION: StartDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Starts the driver service.
*
****************************************************************************/
BOOL StartDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE  schService;
    BOOL       ret;

    schService = OpenService( SchSCManager,
                              DriverName,
                              SERVICE_ALL_ACCESS
                              );
    if ( schService == NULL )
        return FALSE;

    ret = StartService( schService, 0, NULL )
       || GetLastError() == ERROR_SERVICE_ALREADY_RUNNING;

    CloseServiceHandle( schService );

    return ret;
}



/****************************************************************************
*
*    FUNCTION: OpenDevice( IN LPCTSTR, HANDLE *)
*
*    PURPOSE: Opens the device and returns a handle if desired.
*
****************************************************************************/
BOOL OpenDevice( IN LPCTSTR DriverName, HANDLE * lphDevice )
{
    TCHAR    completeDeviceName[64];
    HANDLE   hDevice;

    //
    // Create a \\.\XXX device name that CreateFile can use
    //
    // NOTE: We're making an assumption here that the driver
    //       has created a symbolic link using it's own name
    //       (i.e. if the driver has the name "XXX" we assume
    //       that it used IoCreateSymbolicLink to create a
    //       symbolic link "\DosDevices\XXX". Usually, there
    //       is this understanding between related apps/drivers.
    //
    //       An application might also peruse the DEVICEMAP
    //       section of the registry, or use the QueryDosDevice
    //       API to enumerate the existing symbolic links in the
    //       system.
    //

    wsprintf( completeDeviceName, TEXT("\\\\.\\%s"), DriverName );

    hDevice = CreateFile( completeDeviceName,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL
                          );
    if ( hDevice == ((HANDLE)-1) )
        return FALSE;

	// If user wants handle, give it to them.  Otherwise, just close it.
	if ( lphDevice )
		*lphDevice = hDevice;
	else
	    CloseHandle( hDevice );

    return TRUE;
}



/****************************************************************************
*
*    FUNCTION: StopDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Has the configuration manager stop the driver (unload it)
*
****************************************************************************/
BOOL StopDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE       schService;
    BOOL            ret;
    SERVICE_STATUS  serviceStatus;

    schService = OpenService( SchSCManager, DriverName, SERVICE_ALL_ACCESS );
    if ( schService == NULL )
        return FALSE;

    ret = ControlService( schService, SERVICE_CONTROL_STOP, &serviceStatus );

    CloseServiceHandle( schService );

    return ret;
}


/****************************************************************************
*
*    FUNCTION: RemoveDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Deletes the driver service.
*
****************************************************************************/
BOOL RemoveDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName )
{
    SC_HANDLE  schService;
    BOOL       ret;

    schService = OpenService( SchSCManager,
                              DriverName,
                              SERVICE_ALL_ACCESS
                              );

    if ( schService == NULL )
        return FALSE;

    ret = DeleteService( schService );

    CloseServiceHandle( schService );

    return ret;
}


/****************************************************************************
*
*    FUNCTION: UnloadDeviceDriver( const TCHAR *)
*
*    PURPOSE: Stops the driver and has the configuration manager unload it.
*
****************************************************************************/
BOOL UnloadDeviceDriver( const TCHAR * Name )
{
	SC_HANDLE	schSCManager;

	schSCManager = OpenSCManager(	NULL,                 // machine (NULL == local)
                              		NULL,                 // database (NULL == default)
									SC_MANAGER_ALL_ACCESS // access required
								);

	StopDriver( schSCManager, Name );
	RemoveDriver( schSCManager, Name );

	CloseServiceHandle( schSCManager );

	return TRUE;
}



/****************************************************************************
*
*    FUNCTION: LoadDeviceDriver( const TCHAR, const TCHAR, HANDLE *)
*
*    PURPOSE: Registers a driver with the system configuration manager
*	 and then loads it.
*
****************************************************************************/
BOOL LoadDeviceDriver( const TCHAR * Name, const TCHAR * Path, HANDLE * lphDevice )
{
	SC_HANDLE	schSCManager;
	BOOL		okay;

	schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );

	// Remove previous instance
	RemoveDriver( schSCManager, Name );

	// Ignore success of installation: it may already be installed.
	InstallDriver( schSCManager, Name, Path );

	// Ignore success of start: it may already be started.
	StartDriver( schSCManager, Name );

	// Do make sure we can open it.
	okay = OpenDevice( Name, lphDevice );

 	CloseServiceHandle( schSCManager );

	return okay;
}
//---------------------------------------------------------------------------
bool TWinPort::GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize)
{
DWORD dwBytesReturned;
tagPort32Struct Port32Struct;

if(WinNT)
  {
  Port32Struct.wPortAddr = wPortAddr;
  Port32Struct.bSize = bSize;

  if (!DeviceIoControl(hDriver, IOCTL_WINIO_READPORT, &Port32Struct,
                       sizeof(tagPort32Struct), &Port32Struct, sizeof(tagPort32Struct),
                       &dwBytesReturned, NULL))
    return false;
  else
    *pdwPortVal = Port32Struct.dwPortVal;
  }

return true;
}
//---------------------------------------------------------------------------
bool TWinPort::SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize)
{
DWORD dwBytesReturned;
tagPort32Struct Port32Struct;

if(WinNT)
  {
  Port32Struct.wPortAddr = wPortAddr;
  Port32Struct.dwPortVal = dwPortVal;
  Port32Struct.bSize = bSize;

  if(!DeviceIoControl(hDriver, IOCTL_WINIO_WRITEPORT, &Port32Struct,
                       sizeof(tagPort32Struct), NULL, 0, &dwBytesReturned, NULL))
	  return false;
  }

return true;
}
//---------------------------------------------------------------------------
TWinPort::TWinPort()
{
OSVERSIONINFO info;
memset(&info,0,sizeof(info));
info.dwOSVersionInfoSize = sizeof(info);
WinNT = false;
if(GetVersionEx(&info))
  WinNT = info.dwPlatformId == VER_PLATFORM_WIN32_NT;

error = false;
hDriver = NULL;

if(WinNT)
	{
  error = !OpenDevice("WINIO",&hDriver);
  }
}
//---------------------------------------------------------------------------
TWinPort::~TWinPort()
{
if(WinNT && hDriver)
	CloseHandle(hDriver);
}
//---------------------------------------------------------------------------
byte TWinPort::ReadByte(WORD adr)
{
if(!WinNT)
  {
  byte b;
  asm {
    mov dx, word ptr adr
    in al, dx
    mov byte ptr b,al
    }

  return b;
  }

DWORD val;
if(!hDriver || !GetPortVal(adr, &val, 1))
	{
  error = true;
  return 0;
  }

error = false;
return (byte) val;
}
//---------------------------------------------------------------------------
WORD TWinPort::ReadWord(WORD adr)
{
if(!WinNT)
  {
  WORD w;
  asm {
    mov dx, word ptr adr
    in ax,dx
    mov word ptr w,ax
    }
  return w;
  }

DWORD val;
if(!hDriver || !GetPortVal(adr, &val, 2))
	{
  error = true;
  return 0;
  }

error = false;

return (WORD) val;
}
//---------------------------------------------------------------------------
DWORD TWinPort::ReadDWord(WORD adr)
{
if(!WinNT)
  {
  DWORD w;
  asm {
    mov dx, word ptr adr
    in eax,dx
    mov dword ptr w,eax
    }
  return w;
  }

DWORD val;
if(!hDriver || !GetPortVal(adr, &val, 4))
	{
  error = true;
  return 0;
  }

error = false;

return val;
}
//---------------------------------------------------------------------------
void TWinPort::WriteByte(WORD adr, byte data)
{
if(!WinNT)
  {
  asm {
    mov dx, word ptr adr
    mov al, byte ptr data
    out dx,al
    }
  return;
  }

if(!hDriver)
	{
  error = true;
  return;
  }

error = !SetPortVal(adr, (DWORD) data, 1);
}
//---------------------------------------------------------------------------
void TWinPort::WriteWord(WORD adr,WORD data)
{
if(!WinNT)
  {
  asm {
    mov dx, word ptr adr
    mov ax, word ptr data
    out dx,ax
    }
  return;
  }

if(!hDriver)
	{
  error = true;
  return;
  }

error = !SetPortVal(adr, (DWORD) data, 2);
}
//---------------------------------------------------------------------------
void TWinPort::WriteDWord(WORD adr,DWORD data)
{
if(!WinNT)
  {
  asm {
    mov dx, word ptr adr
    mov eax, dword ptr data
    out dx,eax
    }
  return;
  }

if(!hDriver)
	{
  error = true;
  return;
  }

error = !SetPortVal(adr, (DWORD) data, 4);
}
//---------------------------------------------------------------------------
void TWinPort::ErrorMessage(char *buffer, int maxlen)
{
FormatMessage(
   FORMAT_MESSAGE_FROM_SYSTEM,
   NULL,
   GetLastError(),
   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
   buffer,
   maxlen,
   NULL);
}
//---------------------------------------------------------------------------
bool TWinPort::Install()
{
if(!WinNT)
	return true;

if(hDriver)
	CloseHandle(hDriver);

hDriver = NULL;


char SrcPath[MAX_PATH];
char DstPath[MAX_PATH];

if (!GetModuleFileName(GetModuleHandle(NULL), SrcPath, sizeof(SrcPath)))
  {
  return false;
  }

char *pszSlash = strrchr(SrcPath, '\\');

if (pszSlash)
  pszSlash[1] = 0;
else
  {
  return false;
  }

strcat(SrcPath, "winio.sys");

if(!GetSystemDirectory(DstPath,sizeof(DstPath)))
	{
  return false;
  }

strcat(DstPath, "\\Drivers\\winio.sys");

UnloadDeviceDriver("WINIO");
if(!CopyFile(SrcPath,DstPath,false))
	{
  return false;
  }

hDriver = NULL;
if (!LoadDeviceDriver("WINIO", SrcPath, &hDriver))
	return false;

error = false;
return true;
}
//---------------------------------------------------------------------------
bool TWinPort::Remove()
{
if(!WinNT)
	return true;

if(hDriver)
	CloseHandle(hDriver);

hDriver = NULL;

char DstPath[MAX_PATH];
if(!GetSystemDirectory(DstPath,sizeof(DstPath)))
	{
  return false;
  }

strcat(DstPath, "\\Drivers\\winio.sys");

if(!UnloadDeviceDriver("WINIO"))
	{
  return false;
  }

DeleteFile(DstPath);
return true;
}
//---------------------------------------------------------------------------

