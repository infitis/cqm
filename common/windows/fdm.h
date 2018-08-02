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
//���������� ���������� � ��
void ConnectToDb(void);//FOR CLIENT TOO
//��������� ���������� � ��
void DisconnectFromDb(void);//FOR CLIENT TOO

//������� � ��
//���������� 0 ���� ��������� ������
//��������� sql-������ � ��
int  DoSql(AnsiString s);//FOR CLIENT TOO
//��������� �������� �� sql-�������
int  OpenSql(AnsiString s);//FOR CLIENT TOO
//���������� ��������� �������� ��������������
int  LastInsertId();

//---------------------------------------------------------------------------
#define GETFIELD(x)    DM->q->FieldByName(x)
#define ROWSAFFECTED   DM->q->RowsAffected()
#define RECORDCOUNT    DM->q->RecordCount
#define EMPTYRESULT    (DM->q->Eof) && (DM->q->Bof)
#define MEOF            DM->q->Eof
#define MNEXT           DM->q->Next()

//---------------------------------------------------------------------------
//��������� �� ������ � ��������-����� ������ � �����-�������� ��� MySql
AnsiString FormatDateTimeToDB   (TDateTime s, int type=0);//FOR CLIENT TOO
AnsiString FormatDateTimeStrToDB(AnsiString s,  int type=0);//FOR CLIENT TOO

//����� hhv & k ��� ����� ����
int getCoalrankData(AnsiString name, double &hhv, double &k);

//---------------------------------------------------------------------------
#endif
