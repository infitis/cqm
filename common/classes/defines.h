/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: defines.h

    ����������� ������� ������� : ���, ���������, ���������, �����.

---------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
#ifndef CommonDefines
#define CommonDefines

//------------------------------------------------------------------------------
#include <iostream.h>

//------------------------------------------------------------------------------
#define MAX_STR_LEN 10

//------------------------------------------------------------------------------
extern const double P_MIN;
extern const double N_MIN;

extern const double A_MIN;
extern const double A_MAX;

extern const double H_MIN;
extern const double H_MAX;

extern const double PARAM_DEVIATION;

extern const double P_DEVIATION;
extern const double A_DEVIATION;
extern const double H_DEVIATION;

//------------------------------------------------------------------------------
class CoalParameter
{
    public:
    CoalParameter(void);      //�����������
    CoalParameter(const double V);//���������������� �����������
    CoalParameter(const CoalParameter &A);//���������� �����������
    CoalParameter& operator = (const CoalParameter &A);//�������� ������������
    virtual bool   operator ==(const CoalParameter &A);//�������� ������������
    double val;     //��������
    void setNull(void);//��������� � Null
    bool isNull;  //������� ���������� ��������
    char* format(void);//������� ����������������� ��������
    char* format(char *fmt);//������� ����������������� ��������

    protected:
    char str[MAX_STR_LEN];//����������������� ��������
};
ostream& operator<<(ostream& s, CoalParameter& a);
istream& operator>>(istream& s, CoalParameter& a);

//------------------------------------------------------------------------------
class Ash : public CoalParameter  //����
{
    public:
    Ash(void);      //�����������
    Ash(const double V);//���������������� �����������
    Ash(const Ash &A);//���������� �����������
};

//------------------------------------------------------------------------------
class Weight : public CoalParameter //���
{
    public:
    Weight(void);   //�����������
    Weight(const double V);//���������������� �����������
    Weight(const Weight &W);//���������� �����������
};

//------------------------------------------------------------------------------
class Humidity : public CoalParameter //���������
{
    public:
    Humidity(void);   //�����������
    Humidity(const double V);//���������������� �����������
    Humidity(const Humidity &H);//���������� �����������
};

//------------------------------------------------------------------------------
class Coal    //�����
{
    public:
    Coal(void);         //�����������
    Coal(const Coal &C);//���������� �����������
    Coal(const double P_, const double A_, const double H_=0);//���-�����������
    Coal& operator =(const Coal &C);//�������� ������������
    bool operator ==(const Coal &C);//�������� ������������
    bool empty(void);//true ���� p=a=h=0;
    void setempty(void);//set p=a=h=0;
    Weight P;//��� ����
    Ash    A;//��������� ����
    Humidity H;//��������� ����
};
ostream& operator<<(ostream& s, Coal& c);
istream& operator>>(istream& s, Coal& c);

//------------------------------------------------------------------------------
#endif

