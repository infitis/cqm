//---------------------------------------------------------------------------
#ifndef globalH
#define globalH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
//Данные, которые инициализируются из ini-файла

//Имя файла с логом
extern AnsiString LogName;
//Заглавие, обьект установки
extern AnsiString Title;
//Директория со всеми конфигами
extern AnsiString ConfDir;
//Путь к логам сервера
extern AnsiString LogDir;//FOR CLIENT TOO
//Путь к файлам с архивом сигналов
extern AnsiString SignalsLogDir;//FOR CLIENT TOO
//Путь к файлам с архивом калибровок
extern AnsiString CalibrArcDir;//FOR CLIENT TOO
//Путь к главному ини
extern AnsiString AppIniFileName;

//Соединение с БД
extern AnsiString ConnectionHost;//FOR CLIENT TOO
extern int        ConnectionPort;//FOR CLIENT TOO
extern AnsiString ConnectionDataBase;//FOR CLIENT TOO
extern AnsiString ConnectionLogin;//FOR CLIENT TOO
extern AnsiString ConnectionPassword;//FOR CLIENT TOO
//Активность sql монитора
extern bool       ConnectionSqlMonitor;

//---------------------------------------------------------------------------
//Сервер уже запущен - семафор
extern char * RunningNowSemaphore;//FOR CLIENT TOO
//Клиент уже запущен - семафор
extern char * RunningNowClientSemaphore;//FOR CLIENT TOO
//Инфоцентр уже запущен - семафор
extern char * RunningNowICSemaphore;
//Проверяет, не запущена ли ещё одна копия программы
int RegisterApplication (const char * SemaphoreName);
//Устанавливает точку '.' в качестве разделителя целой и дробной части
int CheckDecimalSeparator(void);

//---------------------------------------------------------------------------
//уведомление от нити в/в, для сервера, что данные прочитаны
#define WM_KICK_SERVER (WM_APP + 400)

//---------------------------------------------------------------------------
//получает сообщение о последней системной ошибке
AnsiString __fastcall GetLastErrorMsg();

//---------------------------------------------------------------------------
//проверяет наличие ини-файла
int __fastcall CheckIniFile(void);

//---------------------------------------------------------------------------
#endif

