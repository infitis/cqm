//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmdiag.h"

//---------------------------------------------------------------------------
void diag2str(char* str, int diag)
{
    str[0] = 0;
    if (diag &D_IDLE          ) strcat(str, " простой |");
    if (diag &D_SOURCE        ) strcat(str, " источник |");
    if (diag &D_P_BREAK       ) strcat(str, " БДН обрыв |");
    if (diag &D_A_BREAK       ) strcat(str, " БДЗ обрыв |");
    if (diag &D_P_EXCITED     ) strcat(str, " БДН возбуждён |");
    if (diag &D_A_EXCITED     ) strcat(str, " БДЗ возбуждён |");
    if (diag &D_EMPTY         ) strcat(str, " пустой |");
    if (diag &D_P_N           ) strcat(str, " БДН N |");
    if (diag &D_A_N           ) strcat(str, " БДЗ N |");
    if (diag &D_P_MORE        ) strcat(str, " БДН > |");
    if (diag &D_A_MORE        ) strcat(str, " БДЗ > |");
    if (diag &D_P_LESS        ) strcat(str, " БДН < |");
    if (diag &D_A_LESS        ) strcat(str, " БДЗ < |");
    if (diag &D_P_SMALLLOAD   ) strcat(str, " малая нагрузка |");
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
 