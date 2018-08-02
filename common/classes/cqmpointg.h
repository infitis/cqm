/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmpointg.h

    �������� ������ CqmControlPointG - ����������� ����������
    ���������� ����� ��������. ������� CqmControlPoint.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmpointgH
#define cqmpointgH

//---------------------------------------------------------------------------
#include "cqmpoint.h"

//---------------------------------------------------------------------------
#define MAX_COALTYPE_DELAY 10
#define MAX_FEEDING_DELAY  10

//---------------------------------------------------------------------------
class CqmControlPointG : public CqmControlPoint
{
public:
    CqmControlPointG(void);
    ~CqmControlPointG(void);

    void Start(void);

    void Prepare(void);
    void MakeCoaltype(void);
    void Make(void);
    void Complete(void);

    void Stop(void);

    istream& Input(istream& s);     //get data from istream
    ostream& Print(ostream& s);     //print to ostream

protected:
    int  coaltype_delay;
    char feeding_traffic[MAX_NAME_LEN];
    int  ftid;
    int  feeding_delay;

private:
    int coaltype_stack[MAX_COALTYPE_DELAY+1];
    int feeding_stack[MAX_FEEDING_DELAY+1];
};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmControlPointG& p);
extern istream& operator>> (istream& s, CqmControlPointG& p);

//---------------------------------------------------------------------------
#endif
 