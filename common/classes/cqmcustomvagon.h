/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmcustomvagon.h

    �������� ������ CqmCustomVagon, ������� ��������� ����������� �����

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmcustomvagonH
#define cqmcustomvagonH

//---------------------------------------------------------------------------
#include <iostream.h>
#include <time.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "coalheap.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
class CqmCustomVagon : public CqmEntity
{
public:
    CqmCustomVagon(void);
    ~CqmCustomVagon(void);

    char eovsigname[MAX_NAME_LEN];//�������� ������� ��

    int id;//���������� ������������� ������
    CoalHeap h;//���� � ����

    int eov;//������� �������� ��
    time_t teov;//����� ���������� ��

    int pid;//����� ������������ ��������

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmCustomVagon& p);
extern istream& operator>> (istream& s, CqmCustomVagon& p);

//---------------------------------------------------------------------------
#endif
