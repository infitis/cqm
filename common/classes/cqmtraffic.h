/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmtraffic.h

    �������� ������ CqmTraffic - ����������� ���������� �������� -
    ���������� ������ �����, ������� �������� �� ���������������
    ������������ ������.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmtrafficH
#define cqmtrafficH

//---------------------------------------------------------------------------
#include "cqmsys.h" 
#include "defines.h"
#include "cqmentity.h"

//---------------------------------------------------------------------------
#define MIN_DN   0.001

//---------------------------------------------------------------------------
class CqmTraffic : public CqmEntity
{
public:
    CqmTraffic();
    ~CqmTraffic();

    int csid;//����� ����� ��������
    int fid;//����� �������

    void Start(void);
    void Prepare(void);
    void Make(void);
    void Stop(void);
    //double dn;
    Coal getCoal(void);

    int argCount;
    char* argNames[MAX_FUNC_ARGS];
    char* argValues[MAX_FUNC_ARGS];

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

private:
    char convName[MAX_NAME_LEN];
    char coalSource[MAX_NAME_LEN];
    char FunctionName[MAX_NAME_LEN];
    char Args[MAX_NAME_LEN];
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmTraffic& f);
extern istream& operator>> (istream& s, CqmTraffic& f);

//---------------------------------------------------------------------------
#endif
