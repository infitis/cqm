//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "stuff.h"
#include "global.h"
#include "fmain.h"
#include "..\common\windows\fdm.h"
#include "..\common\windows\fmsgs.h"
#include "..\common\windows\fclock.h"
#include "..\common\windows\floader.h"
#include "globcli.h"
#include "..\common\client\fcustomashgraph.h"
#include "..\common\client\fcustomvagonsviewer.h"
#include "..\common\client\fcustomminutes.h"
#include "..\common\client\fcustomvagonseditor.h"
#include "..\common\client\clientdata.h"
#include "..\common\client\findic.h"
#include "..\common\client\fpositseditor.h"
#include "..\common\client\foperhelp.h"
#include "..\common\client\froutes.h"
#include "..\common\client\faccums.h"
#include "..\common\client\cqmnet.h"
#include "cqmstreamparse.h"

//---------------------------------------------------------------------------
#include <strstream>

//---------------------------------------------------------------------------
int StartActions(void)
{
    //Загружаем ини-файл
    StepProgressForm("Чтение ини-настроек...");
	ini = new TMemIniFile(AppIniFileName);
	LoadDataFromIni();

    //Параметры командной строки
    StepProgressForm("Чтение параметров команндной строки...");
    ReadArgs();

    //Проверка Сервера
    StepProgressForm("Проверка сервера...");
    CheckServer(false);

    //Подключение к серверу и получение клиентских данных (0 - ошибка)
    StepProgressForm("Подключение к МКУ Серверу...");
    if (!ClientServerActions())
    {
        //сообщения об ошибках внутри
        return 1;
    }

    //соединяемся с БД
    StepProgressForm("Подключение к базе данных...");
    ConnectToDb();

    //Стартуем графики, окна вагонов
    StepProgressForm("Создание форм...");
    InitForms();

    //Обновим формы
    RefreshActions();

    //Показываем их
    ShowWorkPosition();

    //Проверим работает ли сервер
    StepProgressForm("Готово.");

    DoMsg("Старт.");
    return 0;
}

//---------------------------------------------------------------------------
int ClientServerActions(void)
{
    if (isserver)
    {
        //работаем с сервером

    	//Попробуем соединится с сервером
        if (!CqmNetConnect())
        {
            DoMsg2Buf("Не удалось соединится с МКУ Сервером.");
            Application->MessageBox(
                "Не удалось соединится с МКУ Сервером.\nРабота невозможна.",
                "МКУ Клиент",
                MB_OK+MB_ICONERROR);
            return 0;
        }

        //Проверим разрешение работать с сервером
        /*
        AnsiString a, q = "perm";
        if (CqmNetQuery(q,a))
        {
            char str[SOCKET_BUFFER_SIZE];
            int ok = 0;
            strcpy(str, a.c_str());
            std::istrstream s(str);

            s>>ok;
            if (!ok || a.Length() == 0)
            {
                DoMsg2Buf(AnsiString("Проверка разрешений: ")+a);
                Application->MessageBox(
                    AnsiString(AnsiString("Не удалось соединится с МКУ Сервером.\n")+a).c_str(),
                    "МКУ Клиент",
                    MB_OK+MB_ICONERROR);
                return 0;
            }
        }
        else
        {
            return 0;
        }
        */
    }

    //Получим клиентские данные
    if (!GetClientData())
    {
        DoMsg2Buf("Не удалось получить данные для клиента.");
        Application->MessageBox(
            "Не удалось получить данные для клиента.\nРабота невозможна.",
            "МКУ Клиент",
            MB_OK+MB_ICONERROR);
        return 0;
    }
    return 1;
}

//---------------------------------------------------------------------------
void StopActions(void)
{
    //Закрываем и удаляем динамически созданные формы формы
    CloseForms();

    //Отсоединимся от БД
    DisconnectFromDb();

    //Отсоединяемся от МКУ Сервера
    CqmNetDisconnect();

    //закрываем ини файл
    //ini->UpdateFile();
    delete ini;

    DoMsg("Стоп.");
}

//---------------------------------------------------------------------------
int GetClientData(void)
{
    AnsiString a, q = "core: getclientdata";
    if (isserver)
    {
        if (CqmNetQuery(q,a))
        {
            //Клиентские данные получены от сервера через cqmnet
            char str[SOCKET_BUFFER_SIZE];
            char buf[SOCKET_BUFFER_SIZE];
            int ok = 0;
            strcpy(str, a.c_str());
            std::istrstream s(str);

            s>>ok;
            if (!ok || a.Length() == 0)
                return 0;

            // сохраним эти полученные клиентские данные
            // в ини
            if (ClientData.Trim() != a.Trim())
            {
                ini->WriteString("client" , "clientdata", a.Trim());
                ini->UpdateFile();
            }
        }
        else
        {
            //сервер не ответил
            return 0;
        }
    }
    else
    {
        //работаем без сервера
        a = ClientData;
    }

    return ReadClientData(a.c_str());
}

//---------------------------------------------------------------------------
void LoadDataFromIni(void)
{
	Title =                 ini->ReadString("client" , "title", Title);
    isserver =              ini->ReadBool  ("client" , "isserver", isserver);
    PathToServer =          ini->ReadString("client" , "server", PathToServer);
    PathToCertFaceTemplate =ini->ReadString("client" , "certface", PathToCertFaceTemplate);
    //CertForBlank =          ini->ReadBool  ("client" , "certprintonblank", CertForBlank);
    RepIntervalsStartHour = ini->ReadInteger("client" , "repintervalsstarthour", RepIntervalsStartHour);
    RepIntervalsWorkingShift = ini->ReadInteger("client" , "repintervalsworkingshift", RepIntervalsWorkingShift);
    DayRepStartHour =       ini->ReadInteger("client" , "dayrepstarthour", DayRepStartHour);
    WorkingShift =          ini->ReadInteger("client" , "workingshift", WorkingShift);
    RepPosAllMonthPos =     ini->ReadInteger("client",  "repposallmonthpos", RepPosAllMonthPos);
    RepPosWRHVis =          ini->ReadInteger("client",  "repposwrhvis", RepPosWRHVis);
    VagonBatchPanelVisible= ini->ReadInteger("client",  "vagonbatchpanelvisible", VagonBatchPanelVisible);
    ClientData            = ini->ReadString("client" , "clientdata", ClientData);

    CqmNetAddress =         ini->ReadString("clientsocket" , "address", CqmNetAddress);
    CqmNetHost =            ini->ReadString("clientsocket" , "host", CqmNetHost);
    CqmNetPort =            ini->ReadInteger("clientsocket" , "port", CqmNetPort);
    CqmNetTimeOut =         ini->ReadInteger("clientsocket" , "timeout", CqmNetTimeOut);

    ConnectionHost =		ini->ReadString("connection" , "host", ConnectionHost);
	ConnectionPort =		ini->ReadInteger("connection" , "port", ConnectionPort);
	ConnectionDataBase =	ini->ReadString("connection" , "database", ConnectionDataBase);
	ConnectionLogin =		ini->ReadString("connection" , "login", ConnectionLogin);
	ConnectionPassword =	ini->ReadString("connection" , "password", ConnectionPassword);
    ConnectionSqlMonitor =  ini->ReadBool  ("connection" , "sqlmonitor", ConnectionSqlMonitor);
}

//---------------------------------------------------------------------------
int CheckServer(bool needdialog)
{
    if (!isserver) return 0;
    //проверим локальный сервер или удалённый
    if (CqmNetHost.LowerCase() != "localhost" &&
        CqmNetAddress          != "127.0.0.1")
         return 0;
    HANDLE hsem;
    hsem = CreateSemaphore (NULL, 1, 2, RunningNowSemaphore);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle (hsem);//Приложение уже работает
        return 1;
    }
    else
    {
        CloseHandle (hsem);
        if (needdialog)
        {
            if (Application->MessageBox("Сервер МКУ НЕ работает.\nЗапустить?", "Внимание!",
                       MB_YESNO | MB_ICONWARNING) != IDYES)
            {
                return 0;
            }
        }

        AnsiString dir = ExtractFileDir(PathToServer);
        HINSTANCE handle =
        ShellExecute(
        MainF->Handle, // handle to parent window
        NULL,	// pointer to string that specifies operation to perform
        PathToServer.c_str(),	// pointer to filename or folder name string
        NULL,	// pointer to string that specifies executable-file parameters
        dir.c_str(),	// pointer to string that specifies default directory
        SW_SHOWNORMAL 	// whether file is shown when opened
        );
        if ((int)handle <= 32)
        {
            //ERROR!
            //Beep(880, 1000);
            DoMsg("Ошибка запуска сервера: "+GetLastErrorMsg());
            return 0;
        }
        else
        {
            DoMsg2Buf("Стартовый файл запущен, проверим семафор Сервера.");
            for (int i=0; i<5; i++)
            {
                Application->ProcessMessages();
                Sleep(1000);
            }
            hsem = CreateSemaphore (NULL, 1, 2, RunningNowSemaphore);
            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                CloseHandle (hsem);
                DoMsg2Buf("Проверка успешна. Сервер работает.");
                return 1;
            }
            else
            {
                DoMsg2Buf("Сервер не работает");
                return 0;
            }
        }
    }
}

//---------------------------------------------------------------------------
void ReadArgs(void)
{
    if (FindCmdLineSwitch("noserver"))
        isserver = false;
}

//---------------------------------------------------------------------------
void InitForms(void)
{
    MainF->Caption = "МКУ Клиент - " + Title;
    //графики
    for(int i=0; i<clipointCount; i++)
    {
        CustomAshGraphF = new TCustomAshGraphF(Application);
        CustomAshGraphF->Init(i);
        AshGraphs[i] = CustomAshGraphF;
    }
    //Показ вагонов
    if (clivagonCount <= 0)
    {
        MainF->NVagons->Visible = false;
    }
    else
    {
        for(int i=0; i<clivagonCount; i++)
        {
            CustomVagonsViewerF = new TCustomVagonsViewerF(Application);
            CustomVagonsViewerF->Init(i);
            VagonsViewers[i] = CustomVagonsViewerF;
        }
        //Редакторы вагонов
        for(int i=0; i<clivagonCount; i++)
        {
            CustomVagonsEditorF = new TCustomVagonsEditorF(Application);
            CustomVagonsEditorF->Init(i);
            VagonsEditors[i] = CustomVagonsEditorF;
        }
    }
    //минутный архив
    MinutesF->Init();
    //панель индикации
    IndicatorF->Init();
    //редактор позиций
    PositsEditorF->Init();

    //помощник оператора погрузки
    OperHelpFInit();
    if (!OperHelpFEnabled) MainF->NOperHelper->Visible = false;

    //маршруты
    RoutesFInit();
    if (!RoutesFEnabled) MainF->NRoutes->Visible = false;

    //аккумуляторы
    AccumsFInit();
    if (!AccumsFEnabled) MainF->NAccums->Visible = false;

    //удостоверение
    if (PathToCertFaceTemplate == "")
    {
        MainF->NRepCert->Visible = false;
    }

    MainF->Timer->Enabled = true;

}

//---------------------------------------------------------------------------
void CloseForms(void)
{
    AccumsFKill();
    RoutesFKill();
    OperHelpFKill();
    PositsEditorF->Stop();
    IndicatorF->Stop();
    for(int i=0; i<clipointCount; i++)
    {
        delete AshGraphs[i];
    }
    for(int i=0; i<clivagonCount; i++)
    {
        delete VagonsViewers[i];
        delete VagonsEditors[i];
    }
}

//---------------------------------------------------------------------------
void RefreshActions(void)
{
    //DoMsg("commit retain");
    DoSql("commit retain");
    //DoMsg("графики");
    for(int i=0; i<clipointCount; i++)
    {
        AshGraphs[i]->Refresh();
    }
    //DoMsg("вагоны");
    for(int i=0; i<clivagonCount; i++)
    {
        VagonsViewers[i]->Refresh();
        VagonsEditors[i]->Refresh();
    }
    //DoMsg("минуты");
    MinutesF->Refresh();
    //DoMsg("остальное");
    IndicatorF->Refresh();
    if (OperHelpFEnabled) OperHelpF->Refresh();
    if (RoutesFEnabled) RoutesF->Refresh();
    if (AccumsFEnabled) AccumsF->Refresh();
    //DoMsg("...завершено.");
    DoFlushBuf();
}

//---------------------------------------------------------------------------
void ShowWorkPosition(void)
{
    ClockF->Show();
    if (OperHelpF) OperHelpF->WindowState = wsMinimized;
    MsgsF->WindowState     = wsMinimized;
    MinutesF->WindowState  = wsMinimized;
    PositsEditorF->WindowState = wsMinimized;

    for(int i=0; i<clipointCount; i++)
    {
        AshGraphs[i]->WindowState = wsNormal;
        AshGraphs[i]->LoadPosition();
    }

    for(int i=0; i<clivagonCount; i++)
    {
        VagonsViewers[i]->WindowState = wsNormal;
        VagonsViewers[i]->LoadPosition();
    }

    for(int i=0; i<clivagonCount; i++)
    {
        VagonsEditors[i]->WindowState = wsMinimized;
    }

    IndicatorF->WindowState = wsNormal;
    IndicatorF->LoadPosition();
    AshGraphs[0]->SetFocus();
}

//---------------------------------------------------------------------------
void ShowMinutes(void)
{
    MinutesF->WindowState  = wsMaximized;
    MinutesF->Show();
}

//---------------------------------------------------------------------------
void ShowVagons(void)
{
    for(int i=0; i<clivagonCount; i++)
    {
        VagonsEditors[i]->WindowState = wsNormal;
        VagonsEditors[i]->LoadPosition();
    }
}

//---------------------------------------------------------------------------
void ShowPosEditor(void)
{
    PositsEditorF->WindowState  = wsNormal;
    PositsEditorF->Show();
}

//---------------------------------------------------------------------------
void CertFaceShow(void)
{
    //печатаем лицевую сторону удостоверения
    AnsiString dir = ExtractFileDir(PathToCertFaceTemplate);
    HINSTANCE handle =
    ShellExecute(
    MainF->Handle, // handle to parent window
    NULL,	// pointer to string that specifies operation to perform
    PathToCertFaceTemplate.c_str(),	// pointer to filename or folder name string
    NULL,	// pointer to string that specifies executable-file parameters
    dir.c_str(),	// pointer to string that specifies default directory
    SW_MAXIMIZE 	// whether file is shown when opened
    );
    if ((int)handle <= 32)
    {
        //ERROR!
        DoMsg("Ошибка при открытии шаблона удостоверения: "+GetLastErrorMsg());
    }
}

//---------------------------------------------------------------------------
void ShowOperHelper()
{
    if (OperHelpF)
    {
        OperHelpF->WindowState  = wsNormal;
        OperHelpF->LoadPosition();
    }
}

//---------------------------------------------------------------------------
#pragma package(smart_init)

