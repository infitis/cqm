//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <dateutils.hpp>
#include <math.h>
#include <time.h>
#include <Registry.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "../common/windows/fdm.h"
#include "../common/classes/cqmcore.h"
#include "../common/classes/cqmio.h"
#include "../common/classes/signals.h"
#include "../common/classes/cqmcompute.h"
#include "../common/classes/cqmpoint.h"
#include "../common/classes/cqmvagon.h"
#include "../common/classes/cqmdiag.h"
#include "../common/classes/alarms.h"
#include "../common/windows/global.h"
#include "../common/windows/globsrv.h"
#include "../common/windows/stuff.h"
#include "../common/windows/tiothread.h"
#include "../common/windows/fmsgs.h"
#include "../common/windows/fsignals.h"
#include "../common/windows/dbacts.h"
#include "../common/windows/ftableviewer.h"
#include "../common/windows/fdatetimeselect.h"
#include "../common/windows/fclock.h"
#include "../common/windows/floader.h"
#include "../common/windows/shellexec.h"
#include "fmain.h"

//---------------------------------------------------------------------------
int StartActions(void)
{
	//Загружаем данные из ini-файла
    StepProgressForm("Чтение настроек...");
	LoadDataFromIni();

    //Проверяем аргументы и командной строки
    ReadArgs();

    //Запуск cqmnet сервера
    StepProgressForm("Запуск cqmnet...");
    if (!StartCmqNet())
    {
        Application->MessageBox(
                   "Ошибка запуска cqmnet сервера.\nРабота невозможна.",
                   "МКУ Сервер",
                   MB_OK+MB_ICONERROR);
    }
    //void* ewcfw = (void*)SetErrorProc(SocketErrorProc);


    //соединяемся с БД
    StepProgressForm("Подключение к базе данных...");
    ConnectToDb();

    //проверим целостность БД
    //StepProgressForm("Проверка базы данных...");
    //выполняется отдельно от сервера до его запуска.

    //Проверяем winio драйвер
    StepProgressForm("Проверка драйвера ввода/вывода...");
    AnsiString PortError;
    if (iousing)
    {
        if (!PortCheck(&PortError))
        {
            ShowMessage(AnsiString("Ошибка драйвера ввода/вывода: ")+PortError+" Возможно драйвер не установлен.");
            DisconnectFromDb();
            return 4;
        }
    }
    else
    {
        DoMsg("Работа без драйвера ввода/вывода.");
    }
    
	//Загружаем параметры ввода/выода
    StepProgressForm("Загрузка core: конфигурация ввода/вывода...");
    if (!core.io_load_start(AnsiString(ConfDir+"\\"+IoConfFile).c_str()))
    {
        ShowMessage(AnsiString("Ошибка при инициализации ядра: ")+
                    AnsiString(core.exctext));
        return 5;
    }

	//Загружаем параметры точек контроля
    StepProgressForm("Загрузка core: точки контроля...");
    if (!core.compute_load_start(AnsiString(ConfDir+"\\"+PointsConfFile).c_str()))
    {
        ShowMessage(AnsiString("Ошибка при инициализации ядра: ")+
                    AnsiString(core.exctext));
        return 6;
    }

    //Запустить сервер
    StepProgressForm("Запуск core...");
    SignalsF->Init(FormatSignalsHeader());
    StartLoop();

    //Открываем редакторы таблиц (points, calibration)
    StepProgressForm("Открытие редакторов...");
    InitTableViewers();

    //действия с окнами
    StepProgressForm("Окна...");
    MainF->WindowState = wsMaximized;
    TableViewer->WindowState = wsMaximized;

    StepProgressForm("Финал загрузки...");

    MainF->Caption = "МКУ Сервер - " + Title;

    //Проверим windows shell
    //SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
    TRegistry *Registry = new TRegistry(KEY_READ);
    try
    {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
        Registry->OpenKeyReadOnly("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
        AnsiString S = Registry->ReadString("Shell");
        if (S.LowerCase() != "explorer.exe")
            is_nShell = true;
        else
            is_nShell = false;
    }
    __finally
    {
        delete Registry;
    }


    if (is_nShell)
    {
        //shell = nShell.exe
        //MainF->TrayIcon->Visible = false;
        //MainF->TrayIcon->Hide = false;
        //Application->Minimize();
    }
    else
    {
        MainF->TrayIcon->Visible = true;
        MainF->TrayIcon->Hide = true;
        //shell = explorer.exe
        //Application->Minimize();
        MainF->TrayIcon->Minimize();
    }

    ClockF->Show();

    //Сбросим буфер сообщенией
    StepProgressForm("Сброс буфера сообщений...");
    DoFlushBuf();

    return 0;
}

//---------------------------------------------------------------------------
void StopActions(void)
{
    //Остановим нить ввода/вывода
    StopLoop();

    //Финальные действия с core.compute
    core.compute_stop_clear();

    //Финальные действия с core->io
    core.io_stop_clear();

    //отключимся от бд
    DisconnectFromDb();

    //Закроем сокет cqmnet
    StopCqmNet();

    //сбросим буфер сообщений
    DoFlushBuf();
}

//---------------------------------------------------------------------------
void LoadDataFromIni(void)
{
	TIniFile *ini;
	ini = new TIniFile(AppIniFileName);

	Title =                 ini->ReadString("server" , "title", Title);
	Tick =      			ini->ReadInteger("server" , "tick", 2000);
    iousing =               ini->ReadBool("server" , "iousing", iousing);
	iothrStopTimeOut =		ini->ReadInteger("server" , "iothrstoptimeout", Tick*2);
    iothrStartingTimeOut =  ini->ReadInteger("server" , "iothrstarttimeout", iothrStartingTimeOut);
	MutexCoreTimeOut =		ini->ReadInteger("server" , "coresharetimeout", Tick);
    NeedRefresh =           ini->ReadBool("server" , "needrefresh", NeedRefresh);
    usePassword =           ini->ReadBool("server" , "usepassword", usePassword);
    DateTimeFormatForSignals = ini->ReadString("server" , "datetimeformat4signals", DateTimeFormatForSignals);
    is_nShell =             ini->ReadBool("server" , "nshell", is_nShell);

	CqmNetPort =   			ini->ReadInteger("serversocket" , "port", 11111);

    CheckPower =            ini->ReadBool  ("power" , "checkpower", CheckPower);
	PowerSignalName =    	ini->ReadString("power" , "powersignalname", PowerSignalName);
	OffCommand =        	ini->ReadString("power" , "offcommand", OffCommand);
    DefaultOffMethod =      ini->ReadInteger("power", "defaultoffmethod", DefaultOffMethod);

	IoConfFile = 			ini->ReadString("core" , "ioconffile", IoConfFile);
	PointsConfFile =  		ini->ReadString("core" , "pointsconffile", PointsConfFile);

    ConnectionHost =		ini->ReadString("connection" , "host", ConnectionHost);
	ConnectionPort =		ini->ReadInteger("connection" , "port", ConnectionPort);
	ConnectionDataBase =	ini->ReadString("connection" , "database", ConnectionDataBase);
	ConnectionLogin =		ini->ReadString("connection" , "login", ConnectionLogin);
	ConnectionPassword =	ini->ReadString("connection" , "password", ConnectionPassword);
    ConnectionSqlMonitor =  ini->ReadBool  ("connection" , "sqlmonitor", ConnectionSqlMonitor);

	delete ini;
}

//---------------------------------------------------------------------------
void ReadArgs(void)
{
    if (FindCmdLineSwitch("noio"))
        iousing = false;
}

//---------------------------------------------------------------------------
void StartLoop(void)
{
    if (iothrstarted) return;

    //Создаем событие по которому остановится нить ввода/вывода
    //и мутекс разделения core
    InitSync();

	iothr = new Tiothread(MainF->Handle, true);
    iothr->Resume();
    Sleep(700);
    if (iothr->executing)
    {
        DoMsg("Старт.");
    	iothrstarted = true;
    }
    else
    {
        DoMsg("Нить ввода/вывода не стартовала.");
    }
}

//---------------------------------------------------------------------------
void StopLoop(void)
{
    if (!iothrstarted) return;
    if (!SetEvent(hStopIoThreadEvent))
    {
        //throw Exception (AnsiString("Не удалось установить событие: ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
        DoMsg(AnsiString("Не удалось установить событие: ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
    }

    DWORD Result = WaitForSingleObject ((HANDLE)iothr->Handle, iothrStopTimeOut);
    if (Result==WAIT_TIMEOUT)
    {
        //throw Exception (AnsiString("Время ожидания остановки истекло "));
        DoMsg("Время ожидания остановки нити ввода/вывода истекло.");
    }

    DoMsg("Стоп.");
    iothrstarted = false;
    delete iothr;

    //Закроем объекты синхронизации
    CloseSync();
    DoFlushBuf();
}

//---------------------------------------------------------------------------
void InitSync(void)
{
   	//Создаём мутекс
	hMTXCore = CreateMutex(NULL, FALSE, MutexName.c_str());
    if (hMTXCore == NULL)
    {
        throw Exception (AnsiString("Не удалось создать мутекс доступа к ядру: ") + MutexName + ": " + GetLastErrorMsg());
    }
    else
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        throw Exception (AnsiString("Мутекс доступа к ядру уже существует: ") + MutexName);
    }

    //Создаем событие остановки нити ввода/вывода
    hStopIoThreadEvent = CreateEvent (NULL, FALSE, FALSE, StopIoThreadEventName.c_str());
    if (hStopIoThreadEvent == NULL)
    {
        throw Exception (AnsiString("Не удалось создать событие остановки нити ввода/вывода: ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
    }
    else
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        throw Exception (AnsiString("Событие остановки нити ввода/вывода уже существует: ") + StopIoThreadEventName);
    }
}

//---------------------------------------------------------------------------
void CloseSync(void)
{
    if (!CloseHandle(hStopIoThreadEvent))
        DoMsg(AnsiString("Не удалось закрыть ") + StopIoThreadEventName + ": " + GetLastErrorMsg());
    if (!CloseHandle(hMTXCore))
        DoMsg(AnsiString("Не удалось закрыть ") + MutexName + ": " + GetLastErrorMsg());
}

//---------------------------------------------------------------------------
void KickActions(int second)
{
    try
    {

    //----------------------------------------------------------
    DWORD ret = WaitForSingleObject(hMTXCore, MutexCoreTimeOut);
    switch (ret)
    {
        // The thread got mutex ownership.
        case WAIT_OBJECT_0:
        {
            try
            {
                try
                {
                    //Начало работы с core
                    CoreActions(second);
                    //Конец работы с core
                }
                catch (Exception *E)
                {
                    DoMsg(AnsiString("Исключительная ситуация в CoreActions: ") + E->Message);
                }
            }
            __finally
            {
                // Release ownership of the mutex object.
                if (!ReleaseMutex(hMTXCore))
                {
                    throw Exception (AnsiString("Не удалось освободить мутекс доступа к ядру ") + MutexName + ": " + GetLastErrorMsg());
                }
                //DoMsg("release coremutex");
            }
            break;
        }

        // Cannot get mutex ownership due to time-out.
        case WAIT_TIMEOUT:
        {
            throw Exception (AnsiString("Таймаут ожидания мутекса доступа к ядру ") + MutexName);
        }

        // Got ownership of the abandoned mutex object.
        case WAIT_ABANDONED:
        {
            throw Exception (AnsiString("Мутекс доступа к ядру закрытый ") + MutexName + ": " + GetLastErrorMsg());
        }

        // default
        default:
        {
            throw Exception (AnsiString("Захват мутекса доступа к ядру ") + MutexName + " вернул: "
                             + IntToStr(ret) + " Ошибка: " + GetLastErrorMsg());
        }
    }


        //----------------------------------------------------------
    }
    catch (Exception *E)
    {
       DoMsg(AnsiString("Исключительная ситуация в KickActions: ") + E->Message);
    }

    DoFlushBuf();
    if (second == 0)
    {
        FlushTables();
        SignalsF->FlushSignals();

        //обновить гриды
        RefreshTableViewers();

        //нет питания?
        if (NeedPowerOff)
        {
            DoOffCommand(DefaultOffMethod);
        }

        //нужно перезагрузится?
        if (NeedAutoReboot)
        {
            DoMsg("Сервер работает больше недели. Перезагружаем.");
            DoOffCommand(OFF_REBOOT);
        }
    }
}

//---------------------------------------------------------------------------
void CoreActions(int second)
{
    //выбрать значения сигналов для точек контроля
    core.io_2_compute();
    //Посчитать если это конец минуты
    if (second == 0)
    {
        //рассчитать минутные значения
        core.compute_make();
        //Принеобходимости просигнализировать
        MakeAlarm();
        //сохранить их в бд
        StorePoints();
        //Проверим наличие питания
        MakeCheckPower();
        //Проверим время работы
        CheckAutoReboot();
    }

    //Вывести на экран сигналы
    SignalsF->AddSignals(FormatSignalsStr());
}

//---------------------------------------------------------------------------
AnsiString FormatSignalsHeader(void)
{
    AnsiString ret = "moment             ";
    for (int i=0; i<core.io->SignalCount; i++)
	{
	    ret = ret +
        AnsiString().sprintf(",%s", core.io->signals[i]->name);
	}

    return ret;
}

//---------------------------------------------------------------------------
AnsiString FormatSignalsStr(void)
{
    AnsiString ret;
    for (int i=0; i<core.io->SignalCount; i++)
	{
	    ret = ret +
        AnsiString().sprintf(",%s", core.io->signals[i]->format());
	}

    return ret;
}

//---------------------------------------------------------------------------
void MakeCheckPower(void)
{
    if (!CheckPower) return;
    for (int i=0; i<core.io->SignalCount; i++)
	{
        if (PowerSignalName.LowerCase()
            == AnsiString(core.io->signals[i]->name).LowerCase())
        {
            if (core.io->signals[i]->result == 1)
            {
                NeedPowerOff = true;
                msg("Произошло отключение питания. Система будет выключена.");
            }
            break;
        }
	}
}

//---------------------------------------------------------------------------
void CloseMe(void)
{
    PostMessage(MainF->Handle, WM_CLOSE, 0, 0);
}

//---------------------------------------------------------------------------
int DoOffCommand(int offtype)
{
    int ok;
    if (offtype == OFF_RESTART)
    {
        ok = 1;
        CloseMe();
        unsigned int handle = WinExec("cqmstart.cmd", SW_MINIMIZE);
        if (handle <= 32)
        {
            //ERROR!
            DoMsg("Ошибка при запуске команды рестарта: "+GetLastErrorMsg());
            ok = 0;
        }
        return ok;
    }

    if (offtype == OFF_SERVER)
    {
        CloseMe();
        return 1;
    }

    ok = 1;
    AnsiString c = OffCommand+" ";

    switch(offtype)
    {
        case OFF_REBOOT:   {c=c+"reboot";break;}
        case OFF_HALT:     {c=c+"halt";break;}
        case OFF_FORCE:    {c=c+"force";break;}
        case OFF_POWEROFF: {c=c+"poweroff";break;}
    }

    //выполняем команды отключения
    CloseMe();
    unsigned int handle = WinExec(c.c_str(), SW_SHOW);
    if (handle <= 32)
    {
        //ERROR!
        DoMsg("Ошибка при запуске команды off: "+GetLastErrorMsg());
        ok = 0;
    }
    return ok;
}

//---------------------------------------------------------------------------
void msg(char * s)
{
    DoMsg2Buf(AnsiString(s));
}

//---------------------------------------------------------------------------
char debugstr[MAX_NAME_LEN+MAX_NAME_LEN];

//---------------------------------------------------------------------------
void addCalibrArc(char * point, int coaltype, char * param, double val)
{
    AnsiString s = CalibrArcDir + "\\carc.log";
    FILE *f;

    char str[255];
    AnsiString d = FormatDateTime("yyyy-mm-dd hh:nn:ss.zzz", Now());
    sprintf(str, "%s, %s, %i, %s, %6.3f\n",d.c_str(), point, coaltype, param, val);

    if ((f = fopen(s.c_str(), "a")) == NULL)
    {
        DoMsg("Ошибка при открытии "+s);
        return;
    }

    fputs(str, f);

    fclose(f);
    return;
}

//---------------------------------------------------------------------------
void MakeAlarm(void)
{
    int needalarm = 0;
    for (int i=0; i<core.compute->PointCount; i++)
	{
	    int diag = core.compute->points[i]->diag;
        if (diag & D_SOURCE ) needalarm = needalarm | AL_SOURCE;
        if (diag & D_P_BREAK) needalarm = needalarm | AL_BREAK;
        if (diag & D_A_BREAK) needalarm = needalarm | AL_BREAK;
	}
    if (needalarm) Alarm(needalarm);
}

//---------------------------------------------------------------------------
void MakePbyVagWei(void)
{
    TDateTime  t1,  t2;
    AnsiString dt1, dt2;

    const double INTERVALSinHOUR = 1800;
    double x, y;
    double Sx=0, Sy=0, Sxy=0, Sxx=0;
    double alpha, beta;
    int n=0;
    AnsiString buf = "2";

    //интервал времени
    t1 = Now();
    t2 = Now();
    if (!InputDateTime("Выбор интревала времени для расчёта коэффициентов нагрузки по весам вагонов", true, t1, t2))
    {
        return;
    }
    dt1 = FormatDateTimeToDB(t1);
    dt2 = FormatDateTimeToDB(t2);
    if (!OpenSql("select mp, lnFp, wei from vagons where mp>0 and mp is not null and lnFp>0 and lnFp is not null and wei>0 and wei is not null and moment>='"+dt1+"' and moment<='"+dt2+"'"))
    {
        return;
    }
    DoMsg("Расчёт коэффициентов нагрузки по весам вагонов.");
    n = RECORDCOUNT;
    DoMsg("Количество вагонов: "+IntToStr(n));
    if (n < 2) return;
    while (!MEOF)
    {
        y = INTERVALSinHOUR * GETFIELD("wei")->AsFloat / GETFIELD("mp")->AsFloat;
        x = GETFIELD("lnFp")->AsFloat;
        Sx  += x;
        Sy  += y;
        Sxy += x*y;
        Sxx += x*x;
        MNEXT;
    }

    AnsiString strFpP = "1000";
    double FpP;
    if (InputQuery("Расчёт коэффициентов нагрузки по весам вагонов.",
                   "Введите значение FpP", strFpP))
    {
        try
        {
            FpP = strFpP.ToDouble();
            if (FpP > 0 && FpP < 20000)
            {
                Sx  += log(FpP);
                Sy  += 0;
                Sxy += 0;
                Sxx += log(FpP)*log(FpP);
                n++;
                DoMsg(AnsiString().sprintf("Добавили Fp=FpP=%6.3f и P=0.", FpP));
            }
        }
        catch(...)
        {
            DoMsg("Значение FpP не принято!");
        }
    }

    alpha = (Sxy - Sx*Sy/n)/(Sxx - Sx*Sx/n);
    beta  = (Sy - alpha*Sx)/n;

    alpha = -alpha;

    DoMsg("Результаты:");
    DoMsg(AnsiString().sprintf("alpha = %8.4f; beta = %8.4f.", alpha, beta));
}

//---------------------------------------------------------------------------
void SaveCalbrFile(void)
{
    AnsiString s;
    AnsiString f;
    TStringList *L = new TStringList; // declare the list
    try
    {
        L->Append("Градиуровочный файл. " + DateTimeToStr(Now()));
        if (OpenSql("select * from calibration order by point, param, coaltype"))
        {
            while(!MEOF)
            {
                s =     GETFIELD("moment")->AsString + "\t";
                s = s + GETFIELD("point")->AsString  + "\t";
                s = s + GETFIELD("coaltype")->AsString  + "\t";
                s = s + GETFIELD("param")->AsString  + "\t";
                s = s + GETFIELD("val")->AsString  + "\t";
                s = s + GETFIELD("comment")->AsString;
                L->Append(s);
                MNEXT;
            }
            f=CalibrArcDir+"\\grad_"+FormatDateTime("yyyy_mm_dd_hh_nn", Now())+".txt";
            L->SaveToFile(f);
            ShowMessage("Градуировочный файл сохранён в "+f);
        }
    }
    __finally
    {
        delete L; // destroy the list object
    }
}

//---------------------------------------------------------------------------
int ExecCommand(AnsiString command, AnsiString *answer)
{
    int ok;
    command = command.TrimLeft();
    if (command.Pos("core:") == 1)
    {
        command = command.Delete(1,5);
        command = command.TrimLeft();
        ok = ExecCoreCommand(command, answer);
    }
    else
    {
        ok = ExecShellCommand(command, answer); //in shellexec.h
    }
    return ok;
}

//---------------------------------------------------------------------------
int ExecCoreCommand(AnsiString command, AnsiString *answer)
{
    char a[CQML_STR];
    int ok;
    if (!iothrstarted)
    {
        (*answer) = AnsiString("Запрос выплнить невозможно: ядро остановлено.");
        return 0;
    }

    DWORD ret = WaitForSingleObject(hMTXCore, MutexCoreTimeOut);
    switch (ret)
    {
        // The thread got mutex ownership.
        case WAIT_OBJECT_0:
        {
            try
            {
                //Начало работы с core
                ok = core.execute(command.c_str(), a);
                //Конец работы с core

            }
            __finally
            {
                // Release ownership of the mutex object.
                if (!ReleaseMutex(hMTXCore))
                {
                    throw Exception (AnsiString("Не удалось освободить мутекс доступа к ядру ") + MutexName + ": " + GetLastErrorMsg());
                }
                //DoMsg("release coremutex");
            }
            break;
        }

        // Cannot get mutex ownership due to time-out.
        case WAIT_TIMEOUT:
        {
            throw Exception (AnsiString("Таймаут ожидания мутекса доступа к ядру ") + MutexName);
        }

        // Got ownership of the abandoned mutex object.
        case WAIT_ABANDONED:
        {
            throw Exception (AnsiString("Мутекс доступа к ядру закрытый ") + MutexName + ": " + GetLastErrorMsg());
        }
    }
    (*answer) = AnsiString(a);
    return ok;
}

//---------------------------------------------------------------------------
void BetterAsh(void)
{
    AnsiString bpoint, bcoaltype, bhowmuch;
    TDateTime  d1, d2;
    d1 = Now(); d2 = Now();
    if (!InputQuery("Поправление зольности ;)", "На какой точке контроля?", bpoint))
        return;
    if (!InputQuery("Поправление зольности ;)", "Для какого типа угля?", bcoaltype))
        return;
    if (!InputDateTime("За какой интервал времени?", true, d1, d2))
        return;
    if (!InputQuery("Поправление зольности ;)", "На сколько процентов?", bhowmuch))
        return;
    DoSql(
    "update points set a=a+("+bhowmuch+") where point='"+bpoint
    +"' and coaltype="+bcoaltype+" and moment>='"
    +FormatDateTimeToDB(d1)+"' and moment<='"
    +FormatDateTimeToDB(d2)+"' and a is not null and a>0"
    );
    DoMsg("Поправили зольность для точки контроля "+bpoint
    +", тип "+bcoaltype+" c "+DateTimeToStr(d1)+" по "+DateTimeToStr(d2)
    +" на "+bhowmuch+" %");
    DoMsg("Обновили записей: "+IntToStr(ROWSAFFECTED));
}

//---------------------------------------------------------------------------
void BetterRoutes(void)
{
    AnsiString bpoint, bhowmuch;
    TDateTime  d1, d2;
    d1 = Now(); d2 = Now();
    if (!InputQuery("Поправление зольности ;)", "На каком маршруте?", bpoint))
        return;
    if (!InputDateTime("За какой интервал времени?", true, d1, d2))
        return;
    if (!InputQuery("Поправление зольности ;)", "На сколько процентов?", bhowmuch))
        return;
    DoSql(
    "update routes set a=a+("+bhowmuch+") where route='"+bpoint
    +"' and moment>='"
    +FormatDateTimeToDB(d1)+"' and moment<='"
    +FormatDateTimeToDB(d2)+"' and a is not null and a>0"
    );
    DoMsg("Поправили зольность для маршрута "+bpoint
    +" c "+DateTimeToStr(d1)+" по "+DateTimeToStr(d2)
    +" на "+bhowmuch+" %");
    DoMsg("Обновили записей: "+IntToStr(ROWSAFFECTED));
}

//---------------------------------------------------------------------------
void BetterVagons(void)
{
    AnsiString bvagons, bhowmuch;
    TDateTime  d1, d2;
    d1 = Now(); d2 = Now();
    if (!InputQuery("Поправление зольности вагонов ;)", "Для какой точки СПК?", bvagons))
        return;
    if (!InputDateTime("За какой интервал времени?", true, d1, d2))
        return;
    if (!InputQuery("Поправление зольности вагонов ;)", "На сколько процентов?", bhowmuch))
        return;
    DoSql(
    "update vagons set a=a+("+bhowmuch+") where vname='"+bvagons
    +"' and moment>='"+FormatDateTimeToDB(d1)
    +"' and moment<='"+FormatDateTimeToDB(d2)+"' and a is not null and a>0"
    );
    DoMsg("Поправили зольность для точки СПК "+bvagons
    +" c "+DateTimeToStr(d1)+" по "+DateTimeToStr(d2)
    +" на "+bhowmuch+" %");
    DoMsg("Обновили записей: "+IntToStr(ROWSAFFECTED));
}

//---------------------------------------------------------------------------
void __fastcall SocketErrorProc(int ErrorCode)
{
    DoMsg(AnsiString("Ошибка сокета. код ")+IntToStr(ErrorCode));
}

//---------------------------------------------------------------------------
void CheckAutoReboot()
{
    time_t now_time = time(NULL);
    double work_time = difftime(now_time, core.starttime);
    if (work_time > MAX_WORK_TIME_SECONDS)
    {
        TDateTime now = Now();
        if (HourOf(now) == 1)
        {
            NeedAutoReboot = true;
        }
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

