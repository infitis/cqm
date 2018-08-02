/*
	Convert cqm diagnostic code to text message.
	(c) 2005, Ruslan Keba
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>

#include "../../common/classes/cqmdiag.h"

#define MSG_MAX_LEN 256

int main (int argc, char** argv)
{
    int diagcode = 0;

	if (argc != 2)
	{
		printf("Cqm diagnostic code to message translation.\nUsage: cqmdiag <diag_code>\nEnter <diag_code>: ");
		scanf("%d", &diagcode);
	}
	else
	{
        sscanf(argv[1], "%d", &diagcode);
    }
    
    char diagmsg[MSG_MAX_LEN] = "";
    char diagmsgOem[MSG_MAX_LEN]     = "";

    diag2str(diagmsg, diagcode);
    CharToOem(diagmsg, diagmsgOem);

    printf("%s\n", diagmsgOem);

	if (argc != 2)
	{
		system("pause");
	}

    return 0;
}

