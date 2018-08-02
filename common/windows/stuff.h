//---------------------------------------------------------------------------
#ifndef stufH
#define stufH

//---------------------------------------------------------------------------
//Стартовые действия после создания всех форм и до запуска Application->Run();
int StartActions(void);
//Финальные действия при завершении работы сервера
void StopActions(void);
//Загрузка из ini-файла параметров
void LoadDataFromIni(void);
//Прочитать настройки из командной строки
void ReadArgs(void);

//Стартовать цикл ввода/вывода и нить
void StartLoop(void);
//Остановить цикл ввода/вывода и нить
void StopLoop(void);
//Создает событие по которому остановится нить ввода/вывода
//и мутекс взаимодействия
void InitSync(void);
//Закрывает объекты синхронизации
void CloseSync(void);
//Действия при толкании севера нитью в/в
void KickActions(int second);
//Эксклюзивное использование core
//при толкании нитью в/в,
//вызов из KickAction  
void CoreActions(int second);
//формирует строку со значениями сигналов для вывода на экран и в csv
AnsiString FormatSignalsStr(void);
//формирует строку с названиями сигналов, заголовок
AnsiString FormatSignalsHeader(void);
//проверим питание
void MakeCheckPower(void);
//выполняет комманду отключения системы
int DoOffCommand(int offtype);
//этой функцией пользуется алгоритм для передачи сообщений
void msg(char * );
//этой функцией пользуется алгоритм для сохранения новых калибровочных параметров
void addCalibrArc(char * point, int coaltype, char * param, double val);
//Проверить диагностику и просигнализировать
void MakeAlarm(void);
//Рассчиатать коэффициенты нагрузки по весам вагонов
void MakePbyVagWei(void);
//Сохранить градуировочный файл на диск
void SaveCalbrFile(void);
//Команда для сервера
int ExecCommand(AnsiString command, AnsiString *answer);
//Команда для ядра
int ExecCoreCommand(AnsiString command, AnsiString *answer);
//Поправить зольность в минутном архиве
void BetterAsh(void);
//Поправить зольность в архиве маршрутов
void BetterRoutes(void);
//Поправить зольность вагонов
void BetterVagons(void);
//Хэндлер исключений от сокетов
void __fastcall SocketErrorProc(int ErrorCode);
//Проверить как долго работает сервер
void CheckAutoReboot();

//---------------------------------------------------------------------------
#endif
