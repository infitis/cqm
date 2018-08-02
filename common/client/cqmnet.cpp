//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "cqmnet.h"
#include "fmain.h"
#include "globcli.h"
#include "fmsgs.h"

//---------------------------------------------------------------------------
bool CqmNetConnected(void)
{
    return MainF->ClientSocket->Active;
}

//---------------------------------------------------------------------------
int  CqmNetConnect(void)
{
    if (!isserver) return 0;

    MainF->ClientSocket->Address = CqmNetAddress;
    MainF->ClientSocket->Host = CqmNetHost;
    MainF->ClientSocket->Port = CqmNetPort;
    try
    {
        MainF->ClientSocket->Active = true;
    }
    catch (Exception &e)
    {
        DoMsg("������ ��� ��������� ���������� � ��� ��������: "+e.Message);
    }

    if (MainF->ClientSocket->Active)
    {
        DoMsg("������: "+IntToStr(MainF->ClientSocket->Socket->SocketHandle)
             +". ������������ ���������� � ��� ��������.");
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------
void CqmNetDisconnect(void)
{
    if (!MainF->ClientSocket->Active) return;

    try
    {
        MainF->ClientSocket->Active = false;
    }
    catch (Exception &e)
    {
        DoMsg("������ ��� ���������� ���������� � ��� ��������: "+e.Message);
    }

    if (!MainF->ClientSocket->Active)
    {
        DoMsg("������� ���������� � ��� ��������.");
    }
}

//---------------------------------------------------------------------------
int CqmNetCheckConnection(void)
{
    if (!isserver) return 0;

    int rcv;
    char buf[SOCKET_BUFFER_SIZE];
    int restart = 0;

    if (!MainF->ClientSocket->Active)
        restart = 1;
    else
    {
        TWinSocketStream *pStream = new TWinSocketStream(MainF->ClientSocket->Socket, CqmNetTimeOut);
        try
        {
            try
            {
                pStream->Write("ping", 4);
                if (pStream->WaitForData(CqmNetTimeOut))
                {
                    rcv = pStream->Read(buf, SOCKET_BUFFER_SIZE);
                    if (rcv)
                    {
                        AnsiString a = AnsiString(buf, rcv);
                        a = a.Trim();
                        if (a != "ok")
                            throw(Exception("�� ������� ������."));
                    }
                    else
                    {
                        throw(Exception("�� ������� ������."));
                    }
                }
            }
            catch (Exception &e)
            {
                DoMsg("�������� ���������� � ��� ��������: "+e.Message);
                restart = 1;
            }
        }
        __finally
        {
            delete pStream;
        }
    }

    if (restart)
    {
        DoMsg("������� ���������� ����� ����������.");
        CqmNetDisconnect();
        CqmNetConnect();
    }

    return MainF->ClientSocket->Active;
}

//---------------------------------------------------------------------------
int CqmNetQuery(AnsiString q, AnsiString &a)
{
    if (!isserver) return 0;

    char buf[SOCKET_BUFFER_SIZE];
    int rcv;
    int ok = 1;

    if (!CqmNetCheckConnection())
        return 0;

    TWinSocketStream *pStream = new TWinSocketStream(MainF->ClientSocket->Socket, CqmNetTimeOut);
    try
    {
        try
        {
            pStream->Write(q.c_str(), q.Length());
            if (pStream->WaitForData(CqmNetTimeOut))
            {
                rcv = pStream->Read(buf, SOCKET_BUFFER_SIZE);
                if (rcv)
                {
                    a = AnsiString(buf, rcv);
                }
                else
                {
                    a = "ERROR: Read 0 bytes!";
                    ok = 0;
                }
            }
            else
            {
                a = "ERROR: Time Out!";
                ok = 0;
            }
        }
        catch (Exception &e)
        {
            DoMsg("CqmNetQuery ERROR: "+e.Message);
        }
    }
    __finally
    {
        delete pStream;
    }
    return ok;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
