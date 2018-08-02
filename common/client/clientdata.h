//---------------------------------------------------------------------------
#ifndef clientdataH
#define clientdataH

//---------------------------------------------------------------------------
#define MAX_CLIENT_POINTS       6
#define MAX_CLIENT_VAGONS       6
#define MAX_CLIENT_SIGNALS      32
#define MAX_CLIENT_ROUTES       16
#define MAX_CLIENT_ACCUMULATORS 16

#define MAX_CLIENTDATA_LEN      4096

//---------------------------------------------------------------------------
extern int clipointCount;
extern int clivagonCount;
extern int clirouteCount;
extern int cliaccumulatorCount;
extern int clisignalCount;

//---------------------------------------------------------------------------
typedef struct
{
    char name[32];
    char title[32];
    int  id;
} clidata;

//---------------------------------------------------------------------------
extern clidata clipoints[MAX_CLIENT_POINTS];
extern clidata clivagons[MAX_CLIENT_VAGONS];
extern clidata cliroutes[MAX_CLIENT_ROUTES];
extern clidata cliaccumulators[MAX_CLIENT_ACCUMULATORS];
extern clidata clisignals[MAX_CLIENT_SIGNALS];

//---------------------------------------------------------------------------
int  ReadClientData(char* a);
void PrepareClientData(void);

//---------------------------------------------------------------------------
#endif
