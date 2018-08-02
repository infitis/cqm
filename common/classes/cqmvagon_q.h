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














    char* argValues[MAX_FUNC_ARGS];


    virtual void StoreVagon(void);
    virtual int  AddVagon(void);

    CqmControlPoint * P; // ������������ ����� ��������
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmVagonQueue& p);
extern istream& operator>> (istream& s, CqmVagonQueue& p);

//---------------------------------------------------------------------------
#endif