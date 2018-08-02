/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmpoint.h

    �������� ������ CqmControlPoint - ����������� ���������� ����� �������
    �� ���������, ������� ���������� ������� �� ���������, 
    �� ������� �������� � ���������. �������� ������, ����������� ��������
    ��������� ���� ��������.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmpointH
#define cqmpointH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmalgorithm.h"
#include "defines.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
class CqmControlPoint : public CqmEntity
{
public:
    CqmControlPoint(void);

    CqmAlgorithm * a; // compute algorithm

    int diag;//diagnostic code

    //������� ������ �������� ��������� ����� ��������
    //(����� ��� ������� ����������� ��� �������� ����)
    int runningFeeder;

    void Prepare(void);
    void Make(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

    void Start(void);
    void Stop(void);

    int* dataCount;//point to count of time interval where setting signals
    NamedData* s;//point to signals data

    char convName[MAX_NAME_LEN];//conveyor signal name
    char fpName[MAX_NAME_LEN];//weight freq signal name
    char faName[MAX_NAME_LEN];//ash freq signal name

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmControlPoint& p);
extern istream& operator>> (istream& s, CqmControlPoint& p);

//---------------------------------------------------------------------------
#endif
