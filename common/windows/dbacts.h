//---------------------------------------------------------------------------
#ifndef dbactsH
#define dbactsH

//---------------------------------------------------------------------------
#include <map>
#include <string>

//---------------------------------------------------------------------------
//открываем таблицы для просмотра (point, calibration, vagons)
void InitTableViewers(void);
//обновляем таблицы для просмотра (point, calibration, vagons)
void RefreshTableViewers(void);

//---------------------------------------------------------------------------
//сохранить рассчитанные точки контроля в таблицу БД
void StorePoints(void);

//---------------------------------------------------------------------------
//получить все параметры из калибровки
//по известной точке контроля и coaltype
void getCqmCalibration(std::map<std::string, double> * m, char * point, int coaltype);
//сохранить параметр в калибровке
void setCqmCalibration(char * point, int coaltype, char * param, double val);
//сохранить параметр для всех калибровок
void setAllCqmCalibration(char * point, char * param, double val);

//---------------------------------------------------------------------------
//вставить вагон и вернуть его id
int  addvagon(char* name);
//сохранить вагон
int  setvagon(int id, int coaltype, double p, double a, int mp, double lnFp);
//получить вагон
int  getvagon(int id, int* coaltype, double* p, double* a, int* mp, double* lnFp);
// получить тип угля из вагона
int  getvagoncoaltype(int id, int* coaltype);
//если последний вагон пуст - вернёт 0, иначе - его id
int  lastemptyvagon(char* name);
//если первый вагон пуст - вернёт 0, иначе - его id
int  firstemptyvagon(char* name);
//получить тип угля по позиции и марке для вагона id
int solvecoaltype4(int id);

//---------------------------------------------------------------------------
class CoalHeap;
//получить значение аккумулятора
int getaccumulator(char* name, CoalHeap* h, int* coaltype);
//сохранить значение аккумулятора
int setaccumulator(char* name, CoalHeap* h, int* coaltype);

//---------------------------------------------------------------------------
//сбросить таблицы
void FlushTables(void);

//---------------------------------------------------------------------------
#endif
