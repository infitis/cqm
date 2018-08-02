//---------------------------------------------------------------------------
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmfuncs.h"
#include "cqmstreamparse.h"
#include "hurup.h"

//---------------------------------------------------------------------------
CqmFunction::CqmFunction(void)
{
    errors = 0;
    errors_msg[0] = 0;
    h = NULL;
    strcpy(name, "noname");
    strcpy(script, "0");
}

//---------------------------------------------------------------------------
CqmFunction::~CqmFunction(void)
{

}

//---------------------------------------------------------------------------
void CqmFunction::Prepare(void)
{
    if (!h)
    {
        h = new huru();
    }
}

//---------------------------------------------------------------------------
void CqmFunction::setScript(char* s)
{
    if (strlen(s) < MAX_SCRIPT_LEN)
    {
        strcpy(script, s);
    }
}

//---------------------------------------------------------------------------
void CqmFunction::addVariable(char* n, double val)
{
    if (h)
    {
        h->insert(n, val);
    }
}

//---------------------------------------------------------------------------
double CqmFunction::Solve(void)
{
    double d = h->solve(script);
    errors = h->errors;
    strcpy(errors_msg, h->errors_msg);
    return d;
}

//---------------------------------------------------------------------------
void CqmFunction::Finish(void)
{
    if (h)
    {
        delete h;
        h = NULL;
    }
}

//---------------------------------------------------------------------------
istream& CqmFunction::Input(istream& s)
{
    s>>name;

    //ищем "scriptbody"
    GetQuote(s, script, MAX_SCRIPT_LEN, '"', '"');

    return s;
}

//---------------------------------------------------------------------------
ostream& CqmFunction::Print(ostream& s)
{
    return s<<name<<"\t"<<"\""<<script<<"\"";
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmFunction& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmFunction& f)
{
    return f.Input(s);
}

//---------------------------------------------------------------------------

