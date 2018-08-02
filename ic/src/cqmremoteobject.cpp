//---------------------------------------------------------------------------
#include <inifiles.hpp>
#pragma hdrstop
#include "cqmremoteobject.h"

//---------------------------------------------------------------------------
CqmRemoteObject::CqmRemoteObject(AnsiString AIniFileName)
{
    Name = "noname";
    Title = "Нет Объекта";
    ClientData = "";
    LastUpdate = TDateTime(2005, 05, 01);
    PhoneNumber = "";
    IPAddress   = "";
    DBPort      = 3306;
    DBUser      = "cqmicuser";
    DBPassword  = "";
    IniFileName = AIniFileName;
    ready = LoadIni();
    oriLastUpdate = LastUpdate;
}

//---------------------------------------------------------------------------
CqmRemoteObject::~CqmRemoteObject()
{
    SaveIni();
}

//---------------------------------------------------------------------------
CqmRemoteObject::LoadIni()
{
    if (!FileExists(IniFileName))
        return 0;

	TIniFile *ini;
    try
    {
        try
        {
            ini = new TIniFile(IniFileName);

            Name                = ini->ReadString("cqmremoteobject", "name", Name);
            Title               = ini->ReadString("cqmremoteobject", "title", Title);
            ClientData          = ini->ReadString("cqmremoteobject", "clientdata", ClientData);
            LastUpdate          = ini->ReadDateTime("cqmremoteobject", "lastupdate", LastUpdate);
            PhoneNumber         = ini->ReadString("cqmremoteobject", "phonenumber", PhoneNumber);
            IPAddress           = ini->ReadString("cqmremoteobject", "ipaddress", IPAddress);
            DBPort              = ini->ReadInteger("connection", "port", DBPort);
            DBUser              = ini->ReadString("connection", "user", DBUser);
            DBPassword          = ini->ReadString("connection", "password", DBPassword);;
        }
        catch(...)
        {
            return 0;
        }
    }
    __finally
    {
        delete ini;
    }
    return 1;
}

//---------------------------------------------------------------------------
CqmRemoteObject::SaveIni()
{
    if (!ready)
        return 1;

    if (LastUpdate == oriLastUpdate)
        return 1;

	TIniFile *ini;
    try
    {
        ini = new TIniFile(IniFileName);
        ini->WriteDateTime("cqmremoteobject", "lastupdate", LastUpdate);
    }
    __finally
    {
        delete ini;
    }
    return 1;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
