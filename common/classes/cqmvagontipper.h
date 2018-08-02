/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmvagontripper.h

    �������� ������ CqmVagon, ������� ��������� ������ ��������� ����
    �� ������� � ������� ��������������

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmvagontipperH
#define cqmvagontipperH

//---------------------------------------------------------------------------
#include "cqmcustomvagon.h"

//---------------------------------------------------------------------------
class CqmVagonTipper : public CqmCustomVagon
{
public:
    CqmVagonTipper(void);
    ~CqmVagonTipper(void);

    void Start(void);

    void Prepare(void);
    void MakeCoaltype(void);
    void Make(void);
    void Complete(void);

    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

protected:
    char parententity[MAX_NAME_LEN];//title name

private:
    int mp;
    double lnFp;
    Coal c;

    void OnPressEov(double part_of_coalheap);
    void StoreVagon(double part_of_coalheap);
    void AddVagon(void);
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmVagonTipper& p);
extern istream& operator>> (istream& s, CqmVagonTipper& p);

//---------------------------------------------------------------------------
#endif
