/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmvagon.h

    �������� ������ CqmVagon, ������� ��������� ������ �������� ����
    � ������ � ������� ������ ��������

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmvagon_qH
#define cqmvagon_qH

//---------------------------------------------------------------------------
#include "cqmcustomvagon.h"

//---------------------------------------------------------------------------
class CqmControlPoint;

//---------------------------------------------------------------------------
class CqmVagonQueue : public CqmCustomVagon
{
public:
    CqmVagonQueue(void);
    ~CqmVagonQueue(void);

    void Start(void);
    void Make(void);
    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

protected:
    CoalHeap hi;//��������� �����

    char coalqueue_name[MAX_NAME_LEN];//��� �������
    int coalqueue_id;//�� �������

    char FunctionName[MAX_NAME_LEN];//��� �������
    char Args[MAX_NAME_LEN];//������ � ����������� �������
    int fid;//�� �������

    //��������� ������� ����� �������� ������ Args
    int argCount;
    char* argNames[MAX_FUNC_ARGS];
    char* argValues[MAX_FUNC_ARGS];

    virtual void OnPressEov(void);
    virtual void StoreVagon(void);
    virtual int  AddVagon(void);

    CqmControlPoint * P; // ������������ ����� ��������
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmVagonQueue& p);
extern istream& operator>> (istream& s, CqmVagonQueue& p);

//---------------------------------------------------------------------------
#endif
