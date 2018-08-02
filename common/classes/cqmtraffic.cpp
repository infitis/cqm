//---------------------------------------------------------------------------
#include <strstream>
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmtraffic.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmentity.h"
#include "cqmstreamparse.h"
#include "cqmfuncs.h"

//---------------------------------------------------------------------------
CqmTraffic::CqmTraffic() : CqmEntity()
{
    strcpy(name, "noname");
    strcpy(title, "notitle");
    csid = fid = 0;
    active = 0;
    argCount = 0;
    strcpy(mytype, "траффик");
    convName[0] = 0;
    coalSource[0] = 0;
}

//---------------------------------------------------------------------------
CqmTraffic::~CqmTraffic()
{
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

//---------------------------------------------------------------------------
void CqmTraffic::Start(void)
{
    CqmEntity::Start();

    csid = core.compute->getEntityId(coalSource);
    fid = core.compute->getFunctionId(FunctionName);

    std::istrstream* s = new istrstream(Args);
    while (!s->eof() && argCount<MAX_FUNC_ARGS)
    {
        char * var = new char[MAX_NAME_LEN];
        char * val = new char[MAX_NAME_LEN];
        GetPair((*s), MAX_NAME_LEN, var, val, '=');
        argNames[argCount] = var;
        argValues[argCount] = val;
        argCount++;
    }

    delete s;
}

//---------------------------------------------------------------------------
void CqmTraffic::Stop(void)
{
    for (int i=0; i<argCount; i++)
    {
        delete[] argNames[i];
        delete[] argValues[i];
    }
    argCount = 0;

    CqmEntity::Stop();
}

//---------------------------------------------------------------------------
void CqmTraffic::Prepare(void)
{
    double Sc = 0;
    double Sa = 0;
    for (int i=0; i<core.compute->dataCount; i++)
    {
        Sc = Sc +
        core.compute->s[i][convName];
    }
    if (Sc==0)
    {
        active = 0;
        return;
    }

    //подготовим переменные
    core.compute->functions[fid]->Prepare();
    for (int i=0; i<core.compute->dataCount; i++)
    {
        if (core.compute->s[i][convName])
        {
            for (int j=0; j<argCount; j++)
            {
                char*  var = argNames[j];
                double val = core.compute->s[i][argValues[j]];
                core.compute->functions[fid]->addVariable(var, val);
            }
            //посчитаем
            Sa += core.compute->functions[fid]->Solve();
        }
    }
    core.compute->functions[fid]->Finish();
    active = Sa / Sc;

    //debug
    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        char b[MAX_NAME_LEN];
        sprintf(b, "%1.2f/%1.2f=%1.2f", Sa, Sc, active);
        m(b);
    }
}

//---------------------------------------------------------------------------
void CqmTraffic::Make(void)
{
    //all actions in Prepare
}

//---------------------------------------------------------------------------
Coal CqmTraffic::getCoal(void)
{
    //получение доли угля от родительской точки контроля
    Coal parentCoal = core.compute->entitys[csid]->getCoal();
    if (parentCoal.empty() || active < MIN_DN)
    {
        return Coal(0,0,0);
    }
    Coal ret = core.compute->entitys[csid]->getCoal();
    ret.P.val *= active;
    return ret;
}

//---------------------------------------------------------------------------
istream& CqmTraffic::Input(istream& s)
{
    //item <имя> <титул> <род_точка> <откуда> <куда> <решающая_функция> (<аргумент_в_финкции>=<имя_сигнала> ...)
    s>>name>>title>>convName>>coalSource>>what_coaltype>>FunctionName;

    //ищем аргументы
    GetQuote(s, Args, MAX_NAME_LEN, '(', ')');

    return s;
}

//---------------------------------------------------------------------------
ostream& CqmTraffic::Print(ostream& s)
{
    return s<<name<<"\t"<<title<<"\t"
            <<convName<<"\t"<<coalSource<<"\t"
            <<what_coaltype<<"\t"<<FunctionName
            <<" ( "<<Args<<" )";
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmTraffic& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmTraffic& f)
{
    return f.Input(s);
}

//---------------------------------------------------------------------------

