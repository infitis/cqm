//---------------------------------------------------------------------------
#ifndef fdmH
#define fdmH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "ZConnection.hpp"
#include "ZSqlMonitor.hpp"

//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
    TZConnection *db;
    TZReadOnlyQuery *q;
    TZSQLMonitor *SqlMonitor;

private:	// User declarations
public:		// User declarations
	__fastcall TDM(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern TDM *DM;

//---------------------------------------------------------------------------
//установить соединение с бд
void ConnectToDb(void);//FOR CLIENT TOO
//разорвать соединение с бд
void DisconnectFromDb(void);//FOR CLIENT TOO

//Запросы к бд
//возвращают 0 если произошла ошибка
//Выполняет sql-запрос к бд
int  DoSql(AnsiString s);//FOR CLIENT TOO
//открывает дейтасет по sql-запросу
int  OpenSql(AnsiString s);//FOR CLIENT TOO
//Возвращает последнее значение автоинкремента
int  LastInsertId();

//---------------------------------------------------------------------------
#define GETFIELD(x)    DM->q->FieldByName(x)
#define ROWSAFFECTED   DM->q->RowsAffected()
#define RECORDCOUNT    DM->q->RecordCount
#define EMPTYRESULT    (DM->q->Eof) && (DM->q->Bof)
#define MEOF            DM->q->Eof
#define MNEXT           DM->q->Next()

//---------------------------------------------------------------------------
//Формирует из строки с временем-датой строку с датой-временем для MySql
AnsiString FormatDateTimeToDB   (TDateTime s, int type=0);//FOR CLIENT TOO
AnsiString FormatDateTimeStrToDB(AnsiString s,  int type=0);//FOR CLIENT TOO

//Найти hhv & k для марки угля
int getCoalrankData(AnsiString name, double &hhv, double &k);

//---------------------------------------------------------------------------
#endif
