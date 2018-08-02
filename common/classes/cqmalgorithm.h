/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmalgorithm.h

    �������� ������ CqmAlgorithm - ���������� ��������� ��������
    �������� � ��������� �� ����������� ��������� ���������� �
    ��������� �������� �� ������, ������ ���� ��������, �����������
    �������� � ���������.

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmalgorithmH
#define cqmalgorithmH

//---------------------------------------------------------------------------
#include <map>
#include <string>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "defines.h"

//---------------------------------------------------------------------------
#define MAX_MAKE_ORDER_STR 128
#define MAX_FA_STR         128

//---------------------------------------------------------------------------
class CqmControlPoint;

//---------------------------------------------------------------------------
class CqmAlgorithm
{
public:
    CqmAlgorithm(CqmControlPoint *Par);
    ~CqmAlgorithm(void);

    virtual void Make(void);

    int    n;//���������� �������� �����
    int    k;//���������� ���������� �������� ��� FA

    //��� ������� ���������:

    //���
    int    mpn;//���������� ��������
    int    mpL, mp, mpR, mpW;//���������� �������� � ������ ��������� ���������
    double Fpn;//������� �������� �������
    double FpL, Fp, FpR, FpW;//������� �������� ������ �� ����������
    double Spn, SpL, Sp, SpR, SpW;//����� ������� �������� ������ �� ����������
    double sigmaFpn;//������������������ ���������� Fan

    //����
    int FA[DATA_SIZE], CONV[DATA_SIZE];
    int    man;//���������� ��������
    int    maL, ma, maR, maW;//���������� �������� � ������ ��������� ���������
    int    laL, la, laR, laW;//���������� �������� � ������ ��������� ��������� ����� ������
    double Fan;//������� �������� �������
    double FaL, Fa, FaR, FaW;//������� �������� ������ �� ����������
    double dFaL, dFa, dFaR, dFaW;//������� ������� �������� ������ �� ����������
    double San, SaL, Sa, SaR, SaW;//����� ������� �������� ������ �� ����������
    double sigmaFan;//������������������ ���������� Fan
    double dFpP;//���������� ��������
    double dFaP;//������ ����������

    virtual inline double c (char * calibrname);
    virtual inline void s   (char * calibrname, double val);
    virtual inline void sall(char * calibrname, double val);

protected:
    virtual void MakeLimits(void);
    virtual void MakeAvgFP(void);
    virtual void MakeAvgFA(void);
    virtual void MakeAvgFA1(void);
    virtual void MakeAvgFA2(void);
    virtual void MakeP(void);
    virtual void MakeP0(void);
    virtual void MakeP1(void);
    virtual void MakeP2(void);
    virtual void MakeP3(void);
    virtual void MakeP4(void);
    virtual void MakeA(void);
    virtual void MakeAA(void);
    virtual void MakeAB(void);
    virtual void MakeAC(void);
    virtual void MakeAD(void);
    virtual void MakeAE(void);

    std::map<std::string, double> calibration;

    char MakeOrderStr[MAX_MAKE_ORDER_STR];
    char FADebugStr[MAX_FA_STR];

private:
    CqmControlPoint *P; //������������ ����� ��������
    Coal C;
    int diag;
};

//---------------------------------------------------------------------------
bool inInterval(double what, double base, double delta);

//---------------------------------------------------------------------------
#endif
