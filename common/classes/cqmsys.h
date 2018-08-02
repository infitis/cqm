/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: cqmsys.h

    Описание системных констант, структур данных,
    внешних функций

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmsysH
#define cqmsysH

//---------------------------------------------------------------------------
#include <map>
#include <string>

//---------------------------------------------------------------------------
#define MAX_NAME_LEN      256
#define CQML_STR          4095
#define MAX_FUNC_ARGS     8

//---------------------------------------------------------------------------
#define NO_CQM_ENTITY_NAME "NULL"
#define SELF_CQM_ENTITY    "SELF"

//---------------------------------------------------------------------------
#define NO_CQM_ENTITY    -1
#define NO_CLASS_ID      -1

//---------------------------------------------------------------------------
#define NO_COALTYPE       0
#define DEFAULT_COALTYPE  0

//---------------------------------------------------------------------------
extern int  PortReadByte (int addr);
extern void PortWriteByte(int addr, int data);

//---------------------------------------------------------------------------
extern void getCqmCalibration(std::map<std::string, double> * m, char * point, int coaltype);
extern void setCqmCalibration(char * point, int coaltype, char * param, double val);
extern void setAllCqmCalibration(char * point, char * param, double val);
extern void addCalibrArc(char * point, int coaltype, char * param, double val);
extern void msg(char * );
extern char debugstr[MAX_NAME_LEN+MAX_NAME_LEN];
extern int  addvagon(char* name);
extern int  setvagon(int id, int coaltype, double p, double a, int mp, double lnFp);
extern int  getvagon(int id, int* coaltype, double* p, double* a, int* mp, double* lnFp);
extern int  getvagoncoaltype(int id, int* coaltype);
extern int  lastemptyvagon(char* name);
extern int  firstemptyvagon(char* name);
extern int  solvecoaltype4(int id);

class CoalHeap;
extern int getaccumulator(char* name, CoalHeap* h, int* coaltype);
extern int setaccumulator(char* name, CoalHeap* h, int* coaltype);

//---------------------------------------------------------------------------
#define DATA_SIZE 30
//массив проименнованных сигналов
typedef std::map<std::string, int> SignalsData;
//массив проименнованных переменных
typedef std::map<std::string, double> NamedData;

//---------------------------------------------------------------------------
#endif
