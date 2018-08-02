//---------------------------------------------------------------------------
#include "cqmversion.h"
#include <stdio.h>

//---------------------------------------------------------------------------
void cqm_version_get_string(char *s)
{
    sprintf(s, "%i.%i.%i-%s",
        CQM_VERSION_MAJOR,
        CQM_VERSION_MINOR,
        CQM_VERSION_RELEASE,
        CQM_VERSION_STATUS);
}

//---------------------------------------------------------------------------
void ic_version_get_string(char *s)
{
    sprintf(s, "%i.%i.%i-%s",
        IC_VERSION_MAJOR,
        IC_VERSION_MINOR,
        IC_VERSION_RELEASE,
        IC_VERSION_STATUS);
}

//---------------------------------------------------------------------------

