//---------------------------------------------------------------------------
#ifndef dbactsH
#define dbactsH

//---------------------------------------------------------------------------
#include <map>
#include <string>

//---------------------------------------------------------------------------
//��������� ������� ��� ��������� (point, calibration, vagons)
void InitTableViewers(void);
//��������� ������� ��� ��������� (point, calibration, vagons)
void RefreshTableViewers(void);

//---------------------------------------------------------------------------
//��������� ������������ ����� �������� � ������� ��
void StorePoints(void);

//---------------------------------------------------------------------------
//�������� ��� ��������� �� ����������
//�� ��������� ����� �������� � coaltype
void getCqmCalibration(std::map<std::string, double> * m, char * point, int coaltype);
//��������� �������� � ����������
void setCqmCalibration(char * point, int coaltype, char * param, double val);
//��������� �������� ��� ���� ����������
void setAllCqmCalibration(char * point, char * param, double val);

//---------------------------------------------------------------------------
//�������� ����� � ������� ��� id
int  addvagon(char* name);
//��������� �����
int  setvagon(int id, int coaltype, double p, double a, int mp, double lnFp);
//�������� �����
int  getvagon(int id, int* coaltype, double* p, double* a, int* mp, double* lnFp);
// �������� ��� ���� �� ������
int  getvagoncoaltype(int id, int* coaltype);
//���� ��������� ����� ���� - ����� 0, ����� - ��� id
int  lastemptyvagon(char* name);
//���� ������ ����� ���� - ����� 0, ����� - ��� id
int  firstemptyvagon(char* name);
//�������� ��� ���� �� ������� � ����� ��� ������ id
int solvecoaltype4(int id);

//---------------------------------------------------------------------------
class CoalHeap;
//�������� �������� ������������
int getaccumulator(char* name, CoalHeap* h, int* coaltype);
//��������� �������� ������������
int setaccumulator(char* name, CoalHeap* h, int* coaltype);

//---------------------------------------------------------------------------
//�������� �������
void FlushTables(void);

//---------------------------------------------------------------------------
#endif
