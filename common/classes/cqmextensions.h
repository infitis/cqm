/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmextensions.h

    �������� ������ CqmExtension, ������� ������������
    ���������� ������� ����������.
    ���������� ��������-���������.

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef cqmextensionsH
#define cqmextensionsH

//---------------------------------------------------------------------------
#include <iostream.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmentity.h"
#include "cqmextension_def.h"

//---------------------------------------------------------------------------
class CqmExtension : public CqmEntity
{
public:

    CqmExtension(void);
    ~CqmExtension(void);

    char path[MAX_NAME_LEN];
    char proc[MAX_NAME_LEN];
    int  loaded;

    void Start(void);
    void Make(void);
    void Stop(void);

    virtual istream& Input(istream& s);     //get data from istream
    virtual ostream& Print(ostream& s);     //print to ostream












//---------------------------------------------------------------------------
extern ostream& operator<< (ostream& s, CqmExtension& f);
extern istream& operator>> (istream& s, CqmExtension& f);
//---------------------------------------------------------------------------
#endif