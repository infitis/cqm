//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "act.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmpointg.h"

//---------------------------------------------------------------------------
int cqm_extension_start(char * msg)
{
    strcpy(msg, "started.");
    return 1;
}

//---------------------------------------------------------------------------
int cqm_extension_stop(char * msg)
{
    strcpy(msg, "stoped.");
    return 1;
}

//---------------------------------------------------------------------------
int c116c(char * msg, CqmCore * core)
{
    core->showvars(msg);
    strcat(msg, "extension worked.");
    return 1;
}

//---------------------------------------------------------------------------

