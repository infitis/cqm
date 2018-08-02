//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmdiag.h"

//---------------------------------------------------------------------------
void diag2str(char* str, int diag)
{
    str[0] = 0;
    if (diag &D_IDLE          ) strcat(str, " ������� |");
    if (diag &D_SOURCE        ) strcat(str, " �������� |");
    if (diag &D_P_BREAK       ) strcat(str, " ��� ����� |");
    if (diag &D_A_BREAK       ) strcat(str, " ��� ����� |");
    if (diag &D_P_EXCITED     ) strcat(str, " ��� �������� |");
    if (diag &D_A_EXCITED     ) strcat(str, " ��� �������� |");
    if (diag &D_EMPTY         ) strcat(str, " ������ |");
    if (diag &D_P_N           ) strcat(str, " ��� N |");
    if (diag &D_A_N           ) strcat(str, " ��� N |");
    if (diag &D_P_MORE        ) strcat(str, " ��� > |");
    if (diag &D_A_MORE        ) strcat(str, " ��� > |");
    if (diag &D_P_LESS        ) strcat(str, " ��� < |");
    if (diag &D_A_LESS        ) strcat(str, " ��� < |");
    if (diag &D_P_SMALLLOAD   ) strcat(str, " ����� �������� |");
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
 