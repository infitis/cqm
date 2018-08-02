//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "globsrv.h"
#include "global.h"
#include "floader.h"

//---------------------------------------------------------------------------
AnsiString LogName = "server";
AnsiString IoConfFile = "io.cqm";
AnsiString PointsConfFile = "points.cqm";
AnsiString DateTimeFormatForSignals = "dd.mm.yyyy hh:nn:ss";

//---------------------------------------------------------------------------
Tiothread * iothr;
bool iousing = true;
bool iothrstarted = false;
HANDLE hStopIoThreadEvent;
AnsiString StopIoThreadEventName = "cqm_server_io_thr_stop_event";

HANDLE hMTXCore;
AnsiString MutexName = "cqm_server_core_sync_mutex";
DWORD MutexCoreTimeOut;

DWORD iothrStopTimeOut;
AnsiString iothrTimerName        = "cqm_server_io_thr_timer";

//---------------------------------------------------------------------------
DWORD Tick = 2000;
DWORD iothrStartingTimeOut = 1000;

//---------------------------------------------------------------------------
int CqmNetPort = 11111;

//---------------------------------------------------------------------------
int MAX_SERVER_CONNS = 2;


//---------------------------------------------------------------------------
bool NeedRefresh = false;

//---------------------------------------------------------------------------
//œ–Œ¬≈– ¿ Õ¿À»◊»ﬂ œ»“¿Õ»ﬂ
bool CheckPower = true;
AnsiString PowerSignalName = "power";
bool NeedPowerOff = false;
AnsiString OffCommand = "";
int DefaultOffMethod = OFF_POWEROFF;

//---------------------------------------------------------------------------
bool NeedAutoReboot = false;

//---------------------------------------------------------------------------
TWinPort cqmPort;

//---------------------------------------------------------------------------
bool PortCheck(AnsiString *m)
{
	if(cqmPort.Error())
	{
        *m = GetLastErrorMsg();
		return false;
    }
    return true;
}

//---------------------------------------------------------------------------
int  PortReadByte (int addr)
{
    if (!iousing)
        return 0;
    return cqmPort.ReadByte(addr);
}

//---------------------------------------------------------------------------
void PortWriteByte(int addr, int data)
{
    if (iousing)
        cqmPort.WriteByte(addr, data);
}

//---------------------------------------------------------------------------
bool usePassword = true;
//AnsiString ServerPassword = "2718";
AnsiString ServerPassword = "31415";
bool is_nShell = false;

//---------------------------------------------------------------------------
#pragma package(smart_init)
