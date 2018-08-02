/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: ctrlpntclass.h

    ��������� �������������� ������� ����� ��������,
    ������� ����������� ��������

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef CTRLPNTCLASSH
#define CTRLPNTCLASSH

//---------------------------------------------------------------------------
// points classes

//simply point (c20@stash, 1@samara)
#define CQM_POINT         1

//point with 1 feeder (c20@stash, 1@samara)
#define CQM_POINT_003     3

//general point
#define CQM_POINT_GENERAL 10


//---------------------------------------------------------------------------
// vagons classes

//---------------------------------------------------------------------------
//base vagon class
#define CQM_CUSTOM_VAGON -1

//simply (vag4@stash, vag5@stash, vag4@redstar)
#define CQM_VAGON         0

//cur/next wings (vag1@samara)
#define CQM_VAGON_CURNEXT 1

//vagon tipper
#define CQM_VAGON_TIPPER  2

//vagon tipper
#define CQM_VAGON_QUEUE   3

//---------------------------------------------------------------------------
#endif
