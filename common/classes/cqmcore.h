/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmcore.h

    �������� ������ CqmCore, ������� ������������� ���������
    ������� � �������� �������� � �������� ����.
---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmcoreH
#define cqmcoreH

//---------------------------------------------------------------------------
#include <time.h>

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "cqmversion.h"

//---------------------------------------------------------------------------
//��������� �� �.�., �������.
#define CORE_DEBUG_ALGO      0x01
//+ ��������� �� ���������, ���������, �������������
#define CORE_DEBUG_ENTITYS   0x02
//��������� �� ��������� 836 � a10
#define CORE_DEBUG_HARDWARE  0x04
//��������� �� ����������� cqml
#define CORE_DEBUG_CQML      0x08

//---------------------------------------------------------------------------
class HardwareIO;
class Compute;

//---------------------------------------------------------------------------
class CqmCore
{
public:
		CqmCore(void);
        ~CqmCore(void);

        HardwareIO* io;
        Compute* compute;

        //start time
        time_t starttime;

        //core actions
        void io_set_tick1(int t);                   //���������� �������� �����
        void io_set_tick2(int t);                   //������
        void io_set_tick3(int t);                   //������
        void io_read(void);                         //2-second action
        int  io_load_start(char* conffilename);     //start action
        void io_stop_clear(void);                   //stop  action
        int  compute_load_start(char* conffilename);//start action
        void compute_stop_clear(void);              //stop  action
        void io_2_compute(void);                    //2-second action
        void compute_make(void);                    //1-minute action
        void get_info(char *info);                  //getting info about core
        int execute(char *command, char *answer);   //core execute command

        char exctext[1023];//����� � ���������� �� ��������� ���������� core

        void setvar(std::string var, double val);
        inline double vd(std::string var) {return vars[var];}
        inline double vd(char*       var) {return vars[std::string(var)];}
        inline int    vi(std::string var) {return (int) vars[var];}
        inline int    vi(char*       var) {return (int) vars[std::string(var)];}

        void showvars(char* m);

private:
        NamedData vars;
};

//---------------------------------------------------------------------------
extern CqmCore core; 

//---------------------------------------------------------------------------
#endif
