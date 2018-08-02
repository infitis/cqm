//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "main.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmpointg.h"
#include "cqmcoalqueue.h"
#include "defines.h"
#include "cqmdiag.h"
#include "cqmextension_def.h"

//---------------------------------------------------------------------------
int cqm_extension_start(int tag, char * msg)
{
    strcpy(msg, "started.");
    return 1;
}

//---------------------------------------------------------------------------
int cqm_extension_stop(int tag, char * msg)
{
    strcpy(msg, "stoped.");
    return 1;
}

//---------------------------------------------------------------------------
int c116c(int tag, char * msg, CqmCore * core)
{
    if (core->compute->points[1]->diag & D_A_EXCITED)
    {
        Coal C = core->compute->coalqueues[1]->getCoal();
        if (C.empty())
        {
            core->compute->points[1]->C.setempty();
            core->compute->points[1]->diag = D_EMPTY;
        }
        else
        {
            core->compute->points[1]->C = C;
            core->compute->points[1]->diag = 0;
        }

        strcat(msg, "коррекция для точки контроля 1.");
        return CQM_EXTENSION_PROCESSED;
    }
    msg[0] = 0;
    return CQM_EXTENSION_IDLE;
}

//---------------------------------------------------------------------------

