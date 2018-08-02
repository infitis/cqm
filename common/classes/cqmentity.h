/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmentity.h

    ����������� ������ CqmEnity - ���������� ��� ���������
    ���� ������������ ������� ���� ��������� �������
    (����� ��������, ��������, ��������)

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmentityH
#define cqmentityH

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"

//---------------------------------------------------------------------------
#define MSG_LEN 1024

//---------------------------------------------------------------------------
class CqmEntity
{
public:
    CqmEntity();
    ~CqmEntity();

    char name[MAX_NAME_LEN];
    char title[MAX_NAME_LEN];

    int classid;

    double active;

    virtual void Start(void);

    virtual void Prepare(void);
    virtual void MakeCoaltype(void);
    virtual void Make(void);
    virtual void Complete(void);

    virtual void Stop(void);

    virtual Coal getCoal(void);
    virtual void setCoal(Coal);
    virtual int  getCoaltype(void);

    virtual istream& Input(istream& s);     //get data from istream
    virtual ostream& Print(ostream& s);     //print to ostream

    virtual void m(char *t);

    //�� protected ��� ������� �� extensions
    Coal C;
    int coaltype;

protected:
    char what_coaltype[MAX_NAME_LEN];
    int  myCoaltype;
    int  ctpid;
    char mytype[16];

};

//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmEntity& f);
extern istream& operator>> (istream& s, CqmEntity& f);

//---------------------------------------------------------------------------
#endif
 