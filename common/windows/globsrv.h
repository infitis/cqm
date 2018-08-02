//---------------------------------------------------------------------------
#ifndef globsrvH
#define globsrvH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "tiothread.h"
#include "WinPort32.h"

//---------------------------------------------------------------------------
#define OFF_SERVER      0
#define OFF_RESTART     1
#define OFF_REBOOT      2
#define OFF_HALT        3
#define OFF_FORCE       4
#define OFF_POWEROFF    5

//---------------------------------------------------------------------------
//мутекс, который обеспечивает разделение ресурса core
extern HANDLE hMTXCore;

//Имя мутекса для синхронизации нити измерений и главной нити
//сервера во время разделения core - ресурсов
extern AnsiString MutexName;

//Имя файла с логом
extern AnsiString LogName;
//Файл с описанием ввода/вывода
extern AnsiString IoConfFile;
//Файл с описанием точек контроля
extern AnsiString PointsConfFile;
//Формат даты и времени для файла с архивом сигналов
extern AnsiString DateTimeFormatForSignals;

//---------------------------------------------------------------------------
//указатель на класс нити ввода/вывода
extern Tiothread * iothr;

//---------------------------------------------------------------------------
//Использовать ли ввод-вывод (проверка драйвера)
extern bool iousing;
//Работает ли нить ввода/вывода
extern bool iothrstarted;
//Событие, по которому останавливется нить ввода/вывода
extern HANDLE hStopIoThreadEvent;
//Имя этого события
extern AnsiString StopIoThreadEventName;
//Таймаут остановки нити
extern DWORD iothrStopTimeOut;
//имя внутреннего таймера нити ввода/вывода
extern AnsiString iothrTimerName;
//Таймаут для мутекса ражделения доступа к core
extern DWORD MutexCoreTimeOut;

//---------------------------------------------------------------------------
//Интервал таймера нити в/в
extern DWORD Tick;
//Время ожидания запуска нити ввода/вывода
extern DWORD iothrStartingTimeOut;

//---------------------------------------------------------------------------
//Параметры cqmnet сервера
extern int CqmNetPort;

//---------------------------------------------------------------------------
//Максимально возможное количество подключений к серверу
//проверяется по запросу perm
extern int MAX_SERVER_CONNS;

//---------------------------------------------------------------------------
//Нужно ли обновлять таблицы после CoreActions
extern bool NeedRefresh;

//---------------------------------------------------------------------------
//ПРОВЕРКА НАЛИЧИЯ ПИТАНИЯ
//Нужно ли проверять наличие питания (из ini)
extern bool CheckPower;
//Имя сигнала от питания (из ini)
extern AnsiString PowerSignalName;
//Необходимость отключить систему
extern bool NeedPowerOff;
//команда для отключения (из ini)
extern AnsiString OffCommand;
//метод отключения при отсутствии питания (0: SERVER, 1: RESTART, 2: REBOOT, 3: HALT, 4: FORCE, 5: POWEROFF)
//если не указано, то 5 (POWER_OFF).
extern int DefaultOffMethod;


//---------------------------------------------------------------------------
//АВТОМАТИЧЕСКАЯ ПЕРЕЗАГРУЗКА ПОСЛЕ РАБОТЫ БОЛЬШЕ НЕДЕЛИ
//                            60*60*24*7
#define MAX_WORK_TIME_SECONDS 604800

extern bool NeedAutoReboot;

//---------------------------------------------------------------------------
//Порт для ввода/вывода
extern TWinPort cqmPort;	// Порт
//Функции работы с портом
bool PortCheck(AnsiString *m);
int  PortReadByte (int addr);
void PortWriteByte(int addr, int data);

//---------------------------------------------------------------------------
//использовать ли пароль для работы с сервером
extern bool usePassword;
//собственно, пароль
extern AnsiString ServerPassword;
//запуск из-под nshell
extern bool is_nShell;

//---------------------------------------------------------------------------
#endif
