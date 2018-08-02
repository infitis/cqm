//---------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmcore.h"
#include "cqmio.h"
#include "device.h"
#include "signals.h"
#include "cqmcompute.h"
#include "cqmfuncs.h"
#include "cqmpoint.h"
#include "cqmvagon.h"
#include "cqmexec.h"
#include "cqmtraffic.h"
#include "cqmroute.h"
#include "cqmaccumulator.h"
#include "cqmcoalqueue.h"
#include "cqmextensions.h"

//---------------------------------------------------------------------------
CqmCore core;

//---------------------------------------------------------------------------
CqmCore::CqmCore(void)
{
    io = new HardwareIO();
    compute = new Compute();
    starttime = time(NULL);
}

//---------------------------------------------------------------------------
CqmCore::~CqmCore(void)
{
    delete compute;
    delete io;
}

//---------------------------------------------------------------------------
void CqmCore::io_set_tick1(int t)
{
    io->tick1 = t;
}

//---------------------------------------------------------------------------
void CqmCore::io_set_tick2(int t)
{
    io->tick2 = t;
}

//---------------------------------------------------------------------------
void CqmCore::io_set_tick3(int t)
{
    io->tick3 = t;
}

//---------------------------------------------------------------------------
void CqmCore::io_read(void)
{
    io->ReadAllSignals();
}

//---------------------------------------------------------------------------
int CqmCore::io_load_start(char* conffilename)
{
    try{
    io->LoadIO(conffilename);
    io->StartIO();
    }
    catch(const std::exception& e)
    {
        sprintf(exctext, "core::io_load_start exception, what: %s", e.what());
        msg(exctext);
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void CqmCore::io_stop_clear(void)
{
    io->StopIO();
    io->ClearIO();
}

//---------------------------------------------------------------------------
int CqmCore::compute_load_start(char* conffilename)
{
    try{
    compute->Load(conffilename);
    compute->StartCompute();
    }
    catch(const std::exception& e)
    {
        sprintf(exctext, "core::compute_load_start exception, what: %s", e.what());
        msg(exctext);
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void CqmCore::compute_stop_clear(void)
{
    compute->StopCompute();
    compute->Clear();
}

//---------------------------------------------------------------------------
void CqmCore::io_2_compute(void)
{
    compute->FillSignals(io->signals, io->SignalCount);
}

//---------------------------------------------------------------------------
void CqmCore::compute_make(void)
{
    compute->ProcessSignals(io->signals, io->SignalCount);
    compute->Make();
}

//---------------------------------------------------------------------------
void CqmCore::get_info(char *info)
{
    char t[CQML_STR] = "";
    char version[80] = "";
    ostrstream s(t, CQML_STR);
    cqm_version_get_string(version);
    s<<"cqm version "<<version
     <<"\n"<<"name is "<<io->name
     <<"\nstarted at "<<ctime(&starttime)
     <<"loaded device: "<<io->DeviceCount<<"\n";
	for (int i=0; i<io->DeviceCount; i++)
	{

        s<<*(io->devices[i])<<"\n";
    }
    s<<"loaded signals: "<<io->SignalCount<<"\n";
	for (int i=0; i<io->SignalCount; i++)
	{
		s<<*(io->signals[i])<<"\n";
    }
    s<<"loaded functions: "<<compute->FunctionCount<<"\n";
	for (int i=0; i<compute->FunctionCount; i++)
	{
		s<<*(compute->functions[i])<<"\n";
    }
    s<<"loaded traffics: "<<compute->TrafficCount<<"\n";
	for (int i=0; i<compute->TrafficCount; i++)
	{
		s<<*(compute->traffics[i])<<"\n";
    }
    s<<"loaded points: "<<compute->PointCount<<"\n";
	for (int i=0; i<compute->PointCount; i++)
	{
		s<<*(compute->points[i])<<"\n";
    }
    s<<"loaded routes: "<<compute->RouteCount<<"\n";
	for (int i=0; i<compute->RouteCount; i++)
	{
		s<<*(compute->routes[i])<<"\n";
    }
    s<<"loaded coalqueues: "<<compute->CoalQueueCount<<"\n";
	for (int i=0; i<compute->CoalQueueCount; i++)
	{
		s<<*(compute->coalqueues[i])<<"\n";
    }
    s<<"loaded vagons: "<<compute->VagonCount<<"\n";
	for (int i=0; i<compute->VagonCount; i++)
	{
		s<<*(compute->vagons[i])<<"\n";
    }
    s<<"loaded accumulators: "<<compute->AccumulatorCount<<"\n";
	for (int i=0; i<compute->AccumulatorCount; i++)
	{
		s<<*(compute->accumulators[i])<<"\n";
    }
    s<<"loaded makecoaltypeorder: "<<compute->MakeCoaltypeCount<<"\n";
    for (int i=0; i<compute->MakeCoaltypeCount; i++)
    {
        s<<compute->entitys[compute->MakeCoaltypeOrder[i]]->name<<"\t";
    }
    s<<"loaded extensions: "<<compute->ExtensionCount<<"\n";
	for (int i=0; i<compute->ExtensionCount; i++)
	{
		s<<*(compute->extensions[i])<<"\n";
    }

    strcpy(info, t);
}

//---------------------------------------------------------------------------
int CqmCore::execute(char *command, char *answer)
{
    int ok;
    char m[MAX_NAME_LEN];
    ok = cqmExecute(command, answer);
    if (ok)
    {
        /*
        sprintf(m, "core recieved command: %s", command);
        msg(m);
        sprintf(m, "done : %s", answer);
        msg(m);
        */
    }
    else
    {
        sprintf(m, "core recieved command: %s", command);
        msg(m);
        sprintf(m, "error: %s", answer);
        msg(m);
    }
    return ok;
}

//---------------------------------------------------------------------------
void CqmCore::setvar(std::string var, double val)
{
    vars[var] = val;
}

//---------------------------------------------------------------------------
void CqmCore::showvars(char* m)
{
    NamedData::const_iterator start = vars.begin();
    NamedData::const_iterator stop  = vars.end();

    char t[CQML_STR] = "";
    ostrstream s(t, CQML_STR);

    for (; start != stop; ++start)
    {
        s<<start->first<<"\t"<<start->second<<"\n";
    }
    strcpy(m, t);
}

//---------------------------------------------------------------------------

