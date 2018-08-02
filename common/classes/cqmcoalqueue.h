/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmcoalqueue.h

    �������� ������ CqmCoalQueue - ����������� ���������� ���������,
    �� ������� ��������� ��� ����� �����.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmcoalqueueH
#define cqmcoalqueueH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"
#include "cqmentity.h"
#include "coalqueue.h"

//---------------------------------------------------------------------------
class CqmCoalQueue : public CqmEntity
{
public:
    CqmCoalQueue();
    ~CqmCoalQueue();

    void Start(void);
    void Make(void);
    void Stop(void);
    Coal getCoal(void);
    CoalHeap getCoalHeap(void);

    //�������� ������� ����
    Coal outputc[DATA_SIZE];

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream
















    char* argValues[MAX_FUNC_ARGS];

    CoalQueue* cq;//���� �������
    int conv_worked;//���������� ������ ����������� ���������

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmCoalQueue& f);
extern istream& operator>> (istream& s, CqmCoalQueue& f);


