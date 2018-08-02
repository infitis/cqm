//---------------------------------------------------------------------------
#include <strstream>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmexec.h"
#include "cqmcore.h"
#include "cqmio.h"
#include "signals.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmvagon.h"
#include "cqmroute.h"
#include "hurup.h"
#include "cqmaccumulator.h"
#include "cqmstreamparse.h"

//---------------------------------------------------------------------------
//Максимальное число параметров
#define MAX_CQMEXEC_PARAMS 4
//строка с командой
char cmd[CQML_STR];
//строка с параметрами команды
char params[MAX_CQMEXEC_PARAMS][CQML_STR] = {"", "", "", ""};
//разделяет команду и параметры к ней
void get_cmd_and_params(char *c);
//строка с ссобщение о выполнении команды
char message[CQML_STR];

//---------------------------------------------------------------------------
//Команды
//ssd <signal>    Сделать сигнал не активным, принимать значение по умолчанию
int exec_ssd(void);
//ssa <signal>    Сделать сигнал активным
int exec_ssa(void);
//sdv <signal> <value>    задать значение сигнала по умолчанию
int exec_sdv(void);
//getinfo получить информацию о ядре
int exec_getinfo(void);
//getclientdata получить клиентские данные
int exec_getclientdata(void);
//? получить помощь
int exec_help(void);
//getsigval <сигнал> получить текущее значение сигнала.
int exec_getsigval(void);
//задать значение переменной ядра
int exec_set(void);
//получить значение переменной ядра
int exec_get(void);
//huru <script>      выполнить huru-скрипт
int exec_huru(void);
//получить все переменные и их значения
int exec_showvars(void);
//getroute <route> получить текущее coal для маршрута.
int exec_getroute(void);
//emptyaccumulator <name> опустошить аккумулятор
int exec_emptyaccumulator(void);
//getaccumulator <name> получить значение аккумулятора
int exec_getaccumulator(void);
//setaccumulator <name> "<data>"
int exec_setaccumulator(void);
//getpoint <name> получить значения от точки контроля
int exec_getpoint(void);


char *corehelp = "cqml core: ssd, ssa, sdv, getinfo, getclientdata, getsigval, set, get, huru, showvars, getroute, emptyaccumulator, setaccumulator, getaccumulator, getpoint, debug, ?.";

//---------------------------------------------------------------------------
/*
коды возврата
 1    ок
 0    ошибка, в answer - текст ошибки
*/

//---------------------------------------------------------------------------
int cqmExecute(char *c, char *a)
{
    int ok;
    get_cmd_and_params(c);

    //default
    strcpy(message, "ok");

    if (!strcmp(cmd, "ssd"))
        ok = exec_ssd();
    else
    if (!strcmp(cmd, "ssa"))
        ok = exec_ssa();
    else
    if (!strcmp(cmd, "sdv"))
        ok = exec_sdv();
    else
    if (!strcmp(cmd, "getinfo"))
        ok = exec_getinfo();
    else
    if (!strcmp(cmd, "getclientdata"))
        ok = exec_getclientdata();
    else
    if (!strcmp(cmd, "getsigval"))
        ok = exec_getsigval();
    else
    if (!strcmp(cmd, "getroute"))
        ok = exec_getroute();
    else
    if (!strcmp(cmd, "set"))
        ok = exec_set();
    else
    if (!strcmp(cmd, "get"))
        ok = exec_get();
    else
    if (!strcmp(cmd, "huru"))
        ok = exec_huru();
    else
    if (!strcmp(cmd, "showvars"))
        ok = exec_showvars();
    else
    if (!strcmp(cmd, "emptyaccumulator"))
        ok = exec_emptyaccumulator();
    else
    if (!strcmp(cmd, "getaccumulator"))
        ok = exec_getaccumulator();
    else
    if (!strcmp(cmd, "setaccumulator"))
        ok = exec_setaccumulator();
    else
    if (!strcmp(cmd, "getpoint"))
        ok = exec_getpoint();
    else
    if (!strcmp(cmd, "?"))
        ok = exec_help();
    else
    {
        strcpy(message, "bad command.");
        ok = 0;
    }

    strcpy(a, message);

    return ok;
}

//---------------------------------------------------------------------------
void get_cmd_and_params(char *c)
{
    cmd[0] = 0;
    for (int i=0; i<MAX_CQMEXEC_PARAMS; i++)
        params[i][0] = 0;
    std::istrstream s(c, strlen(c));
    s >> cmd;
    int pcount = 0;
    while(!s.eof() && pcount < MAX_CQMEXEC_PARAMS)
    {
        SkipSpacesAndComments(s);
        char r;
        s.get(r);
        s.putback(r);
        if (r == '"')
        {
            GetQuote(s, params[pcount++], CQML_STR, '"', '"');
        }
        else
        {
            s >> params[pcount++];
        }
    }

    for (unsigned int i=0; i<strlen(cmd); i++)
    {
        cmd[i] = tolower(cmd[i]);
    }
    for (int p=0; p<MAX_CQMEXEC_PARAMS; p++)
    {
        for (unsigned int i=0; i<strlen(params[p]); i++)
        {
            params[p][i] = tolower(params[p][i]);
        }
    }
}

//---------------------------------------------------------------------------
int exec_ssd(void)
{
    int ok = 0;
    //search signal
    for (int i=0; i<core.io->SignalCount; i++ )
    {
        if (!strcmp(params[0], core.io->signals[i]->name))
        {
            core.io->signals[i]->active = 0;
            //sprintf(message, "signal %s set default, not active.", core.io->signals[i]->name);
            ok = 1;
            break;
        }
    }
    if (!ok)
    {
        strcpy(message, "bad signal.");
    }

    return ok;
}

//---------------------------------------------------------------------------
int exec_ssa(void)
{
    int ok = 0;
    //search signal
    for (int i=0; i<core.io->SignalCount; i++ )
    {
        if (!strcmp(params[0], core.io->signals[i]->name))
        {
            core.io->signals[i]->active = 1;
            //sprintf(message, "signal %s set active.", core.io->signals[i]->name);
            ok = 1;
            break;
        }
    }
    if (!ok)
    {
        strcpy(message, "bad signal.");
    }

    return ok;
}

//---------------------------------------------------------------------------
int exec_sdv()
{
    int ok = 0;
    //value in params[1]
    int value = atoi(params[1]);
    //search signal
    for (int i=0; i<core.io->SignalCount; i++ )
    {
        if (!strcmp(params[0], core.io->signals[i]->name))
        {
            core.io->signals[i]->defaultvalue = value;
            //sprintf(message, "for signal %s set default value %i", core.io->signals[i]->name, value);
            ok = 1;
            break;
        }
    }
    if (!ok)
    {
        strcpy(message, "bad signal.");
    }

    return ok;
}

//---------------------------------------------------------------------------
int exec_getinfo(void)
{
    core.get_info(message);
    return 1;
}

//---------------------------------------------------------------------------
int exec_showvars(void)
{
    core.showvars(message);
    return 1;
}

//---------------------------------------------------------------------------
int exec_getclientdata(void)
{
    char t[CQML_STR] = "";
    ostrstream s(t, CQML_STR);
    s<<"points "<<core.compute->PointCount<<" ";
	for (int i=0; i<core.compute->PointCount; i++)
	{
		s<<core.compute->points[i]->name<<" "
         <<core.compute->points[i]->title<<" ";
    }

    s<<"vagons "<<core.compute->VagonCount<<" ";
	for (int i=0; i<core.compute->VagonCount; i++)
	{
		s<<core.compute->vagons[i]->name<<" "
         <<core.compute->vagons[i]->title<<" "
         <<core.compute->vagons[i]->pid<<" ";
    }

    s<<"routes "<<core.compute->RouteCount<<" ";
	for (int i=0; i<core.compute->RouteCount; i++)
	{
		s<<core.compute->routes[i]->name<<" "
         <<core.compute->routes[i]->title<<" ";
    }

    s<<"accumulators "<<core.compute->AccumulatorCount<<" ";
	for (int i=0; i<core.compute->AccumulatorCount; i++)
	{
		s<<core.compute->accumulators[i]->name<<" "
         <<core.compute->accumulators[i]->title<<" ";
    }

    //client signals
    int scount = 0;
    char buf[CQML_STR] = "";
    ostrstream b(buf, CQML_STR);
	for (int i=0; i<core.io->SignalCount; i++)
	{
        if (core.io->signals[i]->type & SIGNAL_FOR_CLIENT)
        {
            ++scount;
    		b<<" "<<core.io->signals[i]->name
             <<" "<<core.io->signals[i]->title;
        }
    }
    s<<"signals "<<scount<<buf;

    strcpy(message, t);
    return 1;
}

//---------------------------------------------------------------------------
int exec_help(void)
{
    strcpy(message, corehelp);
    return 1;
}

//---------------------------------------------------------------------------
int exec_getsigval(void)
{
    int ok = 0;
    //search signal
    for (int i=0; i<core.io->SignalCount; i++ )
    {
        if (!strcmp(params[0], core.io->signals[i]->name))
        {
            sprintf(message,"%i", core.io->signals[i]->data);
            //sprintf(message, "signal %s set default, not active.", core.io->signals[i]->name);
            ok = 1;
            break;
        }
    }
    if (!ok)
    {
        strcpy(message, "bad signal.");
    }

    return ok;
}

//---------------------------------------------------------------------------
int exec_set(void)
{
    //variable in params[0]
    //value    in params[1]
    double value = atof(params[1]);
    core.setvar(std::string(params[0]), value);
    return 1;
}

//---------------------------------------------------------------------------
int exec_get(void)
{
    //variable in params[0]
    double value = core.vd(params[0]);
    sprintf(message,"%6.3f", value);
    return 1;
}

//---------------------------------------------------------------------------
int exec_huru(void)
{
    if (strlen(params[0]) == 0)
    {
        strcpy(message, "no script.");
        return 0;
    }

    huru* h = new huru();
    double ret = h->solve(params[0]);

    if (h->errors)
    {
        strcpy(message, h->errors_msg);
        return 0;
    }

    delete h;

    sprintf(message, "%5.10f", ret);
    return 1;
}

//---------------------------------------------------------------------------
int exec_getroute(void)
{
    //search route
    try
    {
        int rid = core.compute->getRouteId(params[0]);
        char buf[CQML_STR] = "\0";
        std::strstream ss(buf, CQML_STR);
        Coal C = core.compute->routes[rid]->getCoal();
        double ac = core.compute->routes[rid]->active;
        ss<<ac<<" "<<C;
        ss.flush();
        ss.getline(message, CQML_STR);
    }
    catch(...)
    {
        strcpy(message, "bad route.");
        return 0;
    }

    return 1;
}

//---------------------------------------------------------------------------
int exec_emptyaccumulator(void)
{
    try
    {
        int aid = core.compute->getAccumulatorId(params[0]);
        core.compute->accumulators[aid]->setEmpty();
    }
    catch(...)
    {
        strcpy(message, "bad accumulator.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
int exec_getaccumulator(void)
{
    try
    {
        int aid = core.compute->getAccumulatorId(params[0]);
        core.compute->accumulators[aid]->getFormatHeap(message);
    }
    catch(...)
    {
        strcpy(message, "bad accumulator.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
int exec_setaccumulator(void)
{
    try
    {
        int aid = core.compute->getAccumulatorId(params[0]);
        core.compute->accumulators[aid]->setFormatHeap(params[1]);
    }
    catch(...)
    {
        strcpy(message, "bad accumulator.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
int exec_getpoint(void)
{
    try
    {
        int pid = core.compute->getPointId(params[0]);
        char buf[CQML_STR] = "\0";
        std::strstream ss(buf, CQML_STR);
        Coal C = core.compute->points[pid]->getCoal();
        ss<<C<<" "<<core.compute->points[pid]->diag;
        ss.flush();
        ss.getline(message, CQML_STR);
    }
    catch(...)
    {
        strcpy(message, "bad point.");
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------

