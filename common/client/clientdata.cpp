//---------------------------------------------------------------------------
#include <string.h>
#include <strstream>

//---------------------------------------------------------------------------
#include "clientdata.h"
#include "cqmstreamparse.h"

//---------------------------------------------------------------------------
clidata clipoints[MAX_CLIENT_POINTS];
int clipointCount = 0;

//---------------------------------------------------------------------------
clidata clivagons[MAX_CLIENT_VAGONS];
int clivagonCount = 0;

//---------------------------------------------------------------------------
clidata cliroutes[MAX_CLIENT_ROUTES];
int clirouteCount = 0;

//---------------------------------------------------------------------------
clidata cliaccumulators[MAX_CLIENT_ACCUMULATORS];
int cliaccumulatorCount = 0;

//---------------------------------------------------------------------------
clidata clisignals[MAX_CLIENT_SIGNALS];
int clisignalCount = 0;

//---------------------------------------------------------------------------
int  ReadClientData(char* a)
{
    char str[MAX_CLIENTDATA_LEN];
    char buf[MAX_CLIENTDATA_LEN];
    strcpy(str, a);
    std::istrstream s(str);

    while (!s.eof())
    {
        SkipSpacesAndComments(s);
        s>>buf;
        if (!strcmp(buf, "points"))
        {
            s>>clipointCount;
            for (int i=0; i<clipointCount; i++)
            {
                s>>clipoints[i].name;
                s>>clipoints[i].title;
            }
        }
        else if (!strcmp(buf, "vagons"))
        {
            s>>clivagonCount;
            for (int i=0; i<clivagonCount; i++)
            {
                s>>clivagons[i].name;
                s>>clivagons[i].title;
                s>>clivagons[i].id;
            }
        }
        else if (!strcmp(buf, "routes"))
        {
            s>>clirouteCount;
            for (int i=0; i<clirouteCount; i++)
            {
                s>>cliroutes[i].name;
                s>>cliroutes[i].title;
            }
        }
        else if (!strcmp(buf, "accumulators"))
        {
            s>>cliaccumulatorCount;
            for (int i=0; i<cliaccumulatorCount; i++)
            {
                s>>cliaccumulators[i].name;
                s>>cliaccumulators[i].title;
            }
        }
        else if (!strcmp(buf, "signals"))
        {
            s>>clisignalCount;
            for (int i=0; i<clisignalCount; i++)
            {
                s>>clisignals[i].name;
                s>>clisignals[i].title;
            }
        }
        SkipSpacesAndComments(s);
    }
    if (clipointCount < 1) return 0;
    PrepareClientData();
    return 1;
}

//---------------------------------------------------------------------------
void PrepareClientData(void)
{
    //заменим в названиях '_' на пробелы
    for (int i=0; i<clipointCount; i++)
    {
        for (unsigned int j=0; j<strlen(clipoints[i].title); j++)
            if (clipoints[i].title[j] == '_')
                clipoints[i].title[j] = ' ';
    }
    for (int i=0; i<clivagonCount; i++)
    {
        for (unsigned int j=0; j<strlen(clivagons[i].title); j++)
            if (clivagons[i].title[j] == '_')
                clivagons[i].title[j] = ' ';
    }

    for (int i=0; i<clirouteCount; i++)
    {
        for (unsigned int j=0; j<strlen(cliroutes[i].title); j++)
            if (cliroutes[i].title[j] == '_')
                cliroutes[i].title[j] = ' ';
    }

    for (int i=0; i<cliaccumulatorCount; i++)
    {
        for (unsigned int j=0; j<strlen(cliaccumulators[i].title); j++)
            if (cliaccumulators[i].title[j] == '_')
                cliaccumulators[i].title[j] = ' ';
    }

    //найдём для каждой точки контоля id (вагона)
    for (int i=0; i<clipointCount; i++)
    {
        clipoints[i].id = -1;
        for (int j=0; j<clivagonCount; j++)
        {
            if (clivagons[j].id == i)
            {
                clipoints[i].id = j;
                break;
            }
        }
    }

    //установим для сигналов и маршрутов id = -1
    for (int i=0; i<clisignalCount; i++)
    {
        clisignals[i].id = -1;
    }
    for (int i=0; i<clirouteCount; i++)
    {
        cliroutes[i].id = -1;
    }
}

//---------------------------------------------------------------------------

