//---------------------------------------------------------------------------
#ifndef globcliH
#define globcliH

//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

//---------------------------------------------------------------------------
#define MIN_ASH_VALUE 2.0

//---------------------------------------------------------------------------
extern TMemIniFile * ini;

//---------------------------------------------------------------------------

/*

    до версии 2.2.7

//Проверять запущен ли сервер
extern bool checkserver;
//Сервер на локельной или удалённой машине
extern bool remoteserver;
*/

//  с версии 2.2.8
//Работаем с сервером или без
extern bool isserver;

//Клиентские данные для запуска Клиента без Сервера
extern AnsiString ClientData;
//Путь к серверу для его запуска
extern AnsiString PathToServer;
//Имя файла с логом
extern AnsiString LogName;//FOR CLIENT TOO

//Путь к файлу с шаблоном лица удостоверения
extern AnsiString PathToCertFaceTemplate;

//---------------------------------------------------------------------------
//Печатать удостоверение на пустой странице или на бланке?
extern bool CertForBlank;
//С какого часа начинать начинать отчёт по интервалам работы маршрутов
extern int RepIntervalsStartHour;
//Сколько часов в смене для интервального отчёта
extern int RepIntervalsWorkingShift;
//С какого часа начинать печатать суточный отчёт
extern int DayRepStartHour;
//Сколько часов в смене (0 - смен не надо)
extern int WorkingShift;
//Включать в отчёт по позициям все позиции за месяц?
extern int RepPosAllMonthPos;
//Включать в отчёт по позициям влажность, марку и теплоту?
extern int RepPosWRHVis;
//Видимость панели для работы с партиями в редакторе вагонов
extern int VagonBatchPanelVisible;

//---------------------------------------------------------------------------
//Параметры соединения с cqmnet сервером
#define SOCKET_BUFFER_SIZE 4095
extern AnsiString CqmNetAddress;
extern AnsiString CqmNetHost;
extern int CqmNetPort;
extern int CqmNetTimeOut;

//---------------------------------------------------------------------------
#endif
