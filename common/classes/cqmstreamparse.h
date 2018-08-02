/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 ��������  ���� �����������,
                            �������   ���� �����������,
                            �������   �������� ���������,
                            ��������� ��������� ���������,
                            ����      ������ �����������.

    ���� ����������� �������
    ��������� ����������� �������� �����

    ����: cqmstreamparse.h

    ���������� ������� ��� ��������������� ������� ������� �������

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef cqmstreamparseH
#define cqmstreamparseH

//---------------------------------------------------------------------------
#include <istream>

//---------------------------------------------------------------------------
#define COMMENT_SYMBOL    '#'

//---------------------------------------------------------------------------
//������� ���������� � ������ ������ ������� � ����������� �� '#...'
void SkipSpacesAndComments(std::istream& s);
//���������� �� ������ ������ ����� ��������� ��� ��������
void GetQuote(std::istream& s, char* buf, int bufsize, char forwardQuote, char closeQuote);
//���������� �� ������ ���� "var = val"
void GetPair(std::istream& s, int bufsize, char* var, char* val, char divider);

//---------------------------------------------------------------------------
#endif