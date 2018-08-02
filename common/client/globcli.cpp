//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "globcli.h"

//---------------------------------------------------------------------------
TMemIniFile * ini;

//---------------------------------------------------------------------------
#ifdef CQM_CLIENT_APPLICATION
bool isserver = true;
#else
// МКУ Инфоцентр
bool isserver = false;
#endif

AnsiString ClientData = "";

AnsiString PathToServer = "srvrun.cmd";
AnsiString LogName = "client";
AnsiString PathToCertFaceTemplate = "\"..\\lib\\cert\\p14.stw\"";

//---------------------------------------------------------------------------
bool CertForBlank = false;

int RepIntervalsStartHour = 0;
int RepIntervalsWorkingShift = 6;

int DayRepStartHour = 0;
int WorkingShift    = 6;

int RepPosAllMonthPos = 0;
int RepPosWRHVis = 0;

int VagonBatchPanelVisible = 0;


//---------------------------------------------------------------------------
AnsiString CqmNetAddress="127.0.0.1";
AnsiString CqmNetHost="";
int CqmNetPort=11111;
int CqmNetTimeOut=2000;

//---------------------------------------------------------------------------
#pragma package(smart_init)
