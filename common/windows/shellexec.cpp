//---------------------------------------------------------------------------
#include <vcl.h>
#include <strstream>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "shellexec.h"
#include "cqmsys.h"
#include "stuff.h"
#include "global.h"
#include "globsrv.h"
#include "fmain.h"

//---------------------------------------------------------------------------
int ExecOff(void);
int ExecPerm(void);
int ExecCmd(void);
int ExecHelp(void);

//---------------------------------------------------------------------------
AnsiString helpanswer = "cqml: ping, off, cmd, ?.";

//---------------------------------------------------------------------------
char c[CQML_STR]="";
std::istrstream *s = NULL;
AnsiString m = "ok";

//---------------------------------------------------------------------------
int ExecShellCommand(AnsiString command, AnsiString *answer)
{
    //по умолчанию
    int ok = 0;
    m = "ok";
    char buf[CQML_STR];

    strcpy(c, command.c_str());
    try
    {
        s = new std::istrstream(c);
        (*s)>>buf;

        if (!strcmp(buf, "perm"))
        {
            ok = ExecPerm();
        }
        else
        if (!strcmp(buf, "off"))
        {
            ok = ExecOff();
        }
        else
        if (!strcmp(buf, "cmd"))
        {
            ok = ExecCmd();
        }
        else
        if (!strcmp(buf, "?"))
        {
            ok = ExecHelp();
        }
        else
        {
            m = "Неизвестная команда.";
        }
    }
    __finally
    {
        delete s;
        s = NULL;
    }

    (*answer) = m;
    return ok;
}

//---------------------------------------------------------------------------
int ExecOff(void)
{
    if (s == NULL || s->eof() || s->bad())
    {
        m = "Не определён параметр для команды off.";
        return 0;
    }

    int ok;
    char buf[CQML_STR];

    (*s)>>buf;
    if (!strcmp(buf, "server"))
    {
        ok = DoOffCommand(OFF_SERVER);
    }
    else
    if (!strcmp(buf, "restart"))
    {
        ok = DoOffCommand(OFF_RESTART);
    }
    else
    if (!strcmp(buf, "reboot"))
    {
        ok = DoOffCommand(OFF_REBOOT);
    }
    else
    if (!strcmp(buf, "halt"))
    {
        ok = DoOffCommand(OFF_HALT);
    }
    else
    if (!strcmp(buf, "force"))
    {
        ok = DoOffCommand(OFF_FORCE);
    }
    else
    if (!strcmp(buf, "poweroff"))
    {
        ok = DoOffCommand(OFF_POWEROFF);
    }
    else
    {
        ok = 0;
        m = "Неизвестный параметр команды off.";
    }

    return ok;
}

//---------------------------------------------------------------------------
int ExecPerm(void)
{
    int ok = 0;

    if (MainF->ServerSocket->Socket->ActiveConnections > MAX_SERVER_CONNS)
    {
        m = "Слишком много подключений";
        ok = 0;
    }
    else
    {
        m = "ok";
        ok = 1;
    }

    return ok;
}

//---------------------------------------------------------------------------
int ExecCmd(void)
{
    if (s == NULL || s->eof() || s->bad())
    {
        m = "Не определёна команда для cmd.";
        return 0;
    }

    int ok;
    char buf[CQML_STR];

    s->getline(buf, CQML_STR, '?');
    AnsiString cmd = AnsiString(buf);
    cmd = TrimLeft(TrimRight(cmd));

    s->getline(buf, CQML_STR);
    AnsiString params = AnsiString(buf);
    params = params.TrimLeft();

    AnsiString dir = ExtractFileDir(cmd);

    HINSTANCE handle =
    ShellExecute(
    Application->MainForm->Handle, // handle to parent window
    NULL,	// pointer to string that specifies operation to perform
    cmd.c_str(),	// pointer to filename or folder name string
    params.c_str(),	// pointer to string that specifies executable-file parameters
    dir.c_str(),	// pointer to string that specifies default directory
    SW_SHOWNORMAL 	// whether file is shown when opened
    );

    if ((int)handle <= 32)
    {
        m = "Ошибка при выполнении команды: " + GetLastErrorMsg();
        ok = 0;
    }
    else
    {
        m = "Команда выполнена.";
        ok = 1;
    }

    return ok;
}

//---------------------------------------------------------------------------
int ExecHelp(void)
{
    m = helpanswer;
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
