/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: dev_a10.h

    ��������� ������ ��� ������ � ������������ �����/������ a10

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef dev_a10H
#define dev_a10H

//---------------------------------------------------------------------------
#include "cqmsys.h"
#include "device.h"
#include "signals.h"

//---------------------------------------------------------------------------
//defines for a10
//Counter control register
#define SELECT_COUNTER_0                    0x00
#define SELECT_COUNTER_1                    0x40
#define SELECT_COUNTER_2                    0x80
#define SELECT_COUNTER_READ_BACK            0xc0

#define RW_COUNTER_LATCH                    0x00
#define RW_LSB                              0x10
#define RW_MSB                              0x20
#define RW_LSB_MSB                          0x30

#define MODE_0                              0x00
#define MODE_1                              0x02
#define MODE_2                              0x04
#define MODE_3                              0x06
#define MODE_4                              0x08
#define MODE_5                              0x0a

#define BCD_16_BIT                          0x00
#define BCD_DECIMAL                         0x01

#define MAX_COUNTER_VALUE					0xffff

//from model
/* = 0x80 = 10000000*/
//#define WR_RD_A10							(0x80 & 0xbf)
//from real i/o
/* = 0x40 = 01000000*/
#define WR_RD_A10							(0x40 & 0x7f)

//---------------------------------------------------------------------------
class Device_a10_counters : public Device
{
private:
    void write_counter_control_word(int counter, unsigned char cw);

public:
	Device_a10_counters(void);	//�����������

    virtual void Start(void);	//�������������, �������� ������
    virtual void Stop(void);	//�������� ������, ����������� ��������

    virtual int Get(int offset, int bit);	//�������� ��������� ������
    virtual int Put(int offset, int bit, int data);//������� ��������� ������
};

//---------------------------------------------------------------------------
class Device_a10_discrete : public Device
{
public:
	Device_a10_discrete(void);	//�����������

    virtual int Get(int offset, int bit);//�������� ��������� ������
    								/*
                                    offset � ������ ������ - ��� ����� ������
                                    ��������������
                                    */
    virtual int Put(int offset, int bit, int data);	//������� ���������� ������
    								/*
                                    � ��� offset - �������� �� �������� ������
                                    */
};

//---------------------------------------------------------------------------
//��������� ������
class FreqSignal_a10 : public FreqSignal
{
public:
    FreqSignal_a10(void);//constructor

    virtual void In (void); //out from i/o port
    virtual char* format(void);
private:
    int prev;
    int devotion;
};


//---------------------------------------------------------------------------
#endif
