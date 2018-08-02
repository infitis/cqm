//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------
#include "cqmalgorithm.h"
#include "cqmpoint.h"
#include "cqmdiag.h"
#include "cqmcore.h"


//---------------------------------------------------------------------------
CqmAlgorithm::CqmAlgorithm(CqmControlPoint *Par)
{
    P = Par;
}

//---------------------------------------------------------------------------
CqmAlgorithm::~CqmAlgorithm(void)
{
}

//---------------------------------------------------------------------------
void CqmAlgorithm::Make(void)
{
    getCqmCalibration(&calibration, P->name, P->getCoaltype());
    n = *(P->dataCount);
    C = Coal(0,0);
    diag = 0;
    MakeOrderStr[0] = 0;

    //calculate Fam,Fax from a,b,Am, Ax
    MakeLimits();

    //sense
    MakeAvgFP();
    MakeAvgFA();
    MakeP();
    MakeA();
    //


    P->setCoal(C);
    P->diag = diag;

    //debug
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        char str[255] = "";
        diag2str(str, diag);
        sprintf(debugstr, "[%s] ct=%i, p=%s, a=%s, diag=%s",
        MakeOrderStr, P->getCoaltype(), C.P.format(), C.A.format(), str);
        P->m(debugstr);
    }

    //активность точки контроля
    if (n)
    {
        P->active = ((double)mpn) / n;
    }
    else
    {
        P->active = 0;
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeLimits(void)
{
    //check dFaP
    if (fabs(c("dFaP")) > 1)
    {
        double bloc = c("b") - 2*c("a")*c("dFaP");
        double cloc = c("a")*c("dFaP")*c("dFaP") - c("b")*c("dFaP") + c("c");
        s("b", bloc);
        s("c", cloc);
        sprintf(debugstr, "New b,c: %s %i dFap = %6.3f, b = %6.3f, c = %6.3f",
        P->title, P->getCoaltype(), c("dFaP"), c("b"), c("c"));
        P->m(debugstr);
        s("dFaP", 0);
        return;
    }

    double newFam, newFax;
    //Fam
    if ((c("a")) == 0)
    {
        sprintf(debugstr, "MakeLimits error: %s %i a = 0!",
        P->title, P->getCoaltype());
        P->m(debugstr);
        return;
    }

    double DFam = c("b")*c("b") - 4*c("a")*(c("c")-c("Ax"));
    if (DFam < 0)
    {
        sprintf(debugstr, "MakeLimits error: %s %i DFam = %6.3f < 0!",
        P->title, P->getCoaltype(), DFam);
        P->m(debugstr);
        return;
    }
    newFam = (-sqrt(DFam)-c("b"))/2/c("a");
    if (newFam <= c("FaF") || newFam > 10000)
    {
        sprintf(debugstr, "MakeLimits error: %s %i Fam = %6.3f!",
        P->title, P->getCoaltype(), newFam);
        P->m(debugstr);
        return;
    }

    //Fax
    double DFax = c("b")*c("b") - 4*c("a")*(c("c")-c("Am"));
    if (DFax < 0)
    {
        sprintf(debugstr, "MakeLimits error: %s %i DFax = %6.3f < 0!",
        P->title, P->getCoaltype(), DFax);
        P->m(debugstr);
        return;
    }
    newFax = (-sqrt(DFax)-c("b"))/2/c("a");
    if (newFax <= c("FaF") || newFax > 10000)
    {
        sprintf(debugstr, "MakeLimits error: %s %i Fax = %6.3f!",
        P->title, P->getCoaltype(), newFax);
        P->m(debugstr);
        return;
    }

    s("Fam", newFam);
    s("Fax", newFax);
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAvgFP(void)
{
    SpL = Sp = SpR = SpW = Spn = 0;
    FpL = Fp = FpR = FpW = Fpn = 0;
    mpL = mp = mpR = mpW = mpn = 0;

    for (int i=0; i<n; i++)
    {
        if (P->s[i][P->convName] == 0)
        {
            SpW += P->s[i][P->fpName];
            mpW++;
        }
        else
        {
            Spn += P->s[i][P->fpName];
            mpn++;
            if (P->s[i][P->fpName] > c("Fpx"))
            {
                SpR += P->s[i][P->fpName];
                mpR++;
            }
            else
            if (P->s[i][P->fpName] < c("Fpm"))
            {
                SpL += P->s[i][P->fpName];
                mpL++;
            }
            else
            {
                Sp += P->s[i][P->fpName];
                mp++;
            }
        }
    }

    if (mpn) Fpn = Spn / mpn;
    if (mpL) FpL = SpL / mpL;
    if (mp ) Fp  = Sp  / mp ;
    if (mpR) FpR = SpR / mpR;
    if (mpW) FpW = SpW / mpW;

    //среднеквадратичное отклонение
    sigmaFpn = 0;
    double S = 0;
    for (int i=0; i<n; i++)
    {
        S += (Fpn - P->s[i][P->fpName])*(Fpn - P->s[i][P->fpName]);
    }
    if (mpn) sigmaFpn = sqrt(S / mpn);


    //debug
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "FP: %2i %5.1f %5.1f | %2i %5.1f, %2i %5.1f, %2i %5.1f | %2i %5.1f",
        mpn, Fpn, sigmaFpn, mpL, FpL, mp, Fp, mpR, FpR, mpW, FpW);
        P->m(debugstr);
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAvgFA(void)
{
    MakeAvgFA1();
    MakeAvgFA2();
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAvgFA1(void)
{
    SaL = Sa = SaR = SaW = San = 0;
    FaL = Fa = FaR = FaW = Fan = 0;
    maL = ma = maR = maW = man = 0;
    laL = la = laR = laW = 0;

    //Копируем значения сигналов в локальные массивы
    for(int i=0; i<n; i++)
    {
        FA[i]   = (P->s[i][P->faName]);
        CONV[i] = (P->s[i][P->convName]);
    }

    //сортируем по U {0-убыванию; 1-возрастанию}
    if (c("U"))
    {
        //сортируем по возрастанию
        for (int i=0; i<n-1; i++)
            for (int j=0; j<n-i-1; j++)
            {
                if (FA[j] > FA[j+1])
                {
                    int sw;
                    sw = FA[j]; FA[j] = FA[j+1]; FA[j+1] = sw;
                    sw = CONV[j]; CONV[j] = CONV[j+1]; CONV[j+1] = sw;
                }
            }
    }
    else
    {
        //сортируем по убыванию
        for (int i=0; i<n-1; i++)
            for (int j=0; j<n-i-1; j++)
            {
                if (FA[j] < FA[j+1])
                {
                    int sw;
                    sw = FA[j]; FA[j] = FA[j+1]; FA[j+1] = sw;
                    sw = CONV[j]; CONV[j] = CONV[j+1]; CONV[j+1] = sw;
                }
            }
    }
    //отбор значений от {минимального | максимального}

    k=0;
    if (c("U"))
    {
        //отбор от минимального значения
        for(int i=0; i<n; i++)
        {
            if (FA[i] <= FA[0] + c("delta")*FA[0])
            {
                k++;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        //отбор от максимального значения
        for(int i=0; i<n; i++)
        {
            if (FA[i] >= FA[0] - c("delta")*FA[0])
            {
                k++;
            }
            else
            {
                break;
            }
        }
    }
    /*
    k = n;
    */
    //расчёт сумм для интервалов частот
    for (int i=0; i<k; i++)
    {
        if (CONV[i] == 0)
        {
            SaW += FA[i];
            maW++;
        }
        else
        {
            San += FA[i];
            man++;
            if (FA[i] > c("Fax"))
            {
                SaR += FA[i];
                maR++;
            }
            else
            if (FA[i] < c("Fam"))
            {
                SaL += FA[i];
                maL++;
            }
            else
            {
                Sa += FA[i];
                ma++;
            }
        }
    }
    //рассчёт средних частот
    if (man) {Fan = San / man;}
    if (maL) {FaL = SaL / maL; dFaL = c("q1")*sqrt(FaL);}
    if (ma ) {Fa  = Sa  / ma ; dFa  = c("q1")*sqrt(Fa);}
    if (maR) {FaR = SaR / maR; dFaR = c("q1")*sqrt(FaR);}
    if (maW) {FaW = SaW / maW; dFaW = c("q1")*sqrt(FaW);}

    //среднеквадратичное отклонение
    sigmaFan = 0;
    double S = 0;
    for (int i=0; i<n; i++)
    {
        S += (Fan - FA[i])*(Fan - FA[i]);
    }
    if (man) sigmaFan = sqrt(S / man);

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "FA: %2i %5.1f %5.1f | %2i %5.1f, %2i %5.1f, %2i %5.1f | %2i %5.1f",
        man, Fan, sigmaFan, maL, FaL, ma, Fa, maR, FaR, maW, FaW);
        strcpy(FADebugStr, debugstr);
        P->m(debugstr);
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAvgFA2(void)
{
    //ещё сузим выбранные интервалы
    SaL = 0; Sa = 0; SaR = 0; SaW = 0;
    if (maW == k)
    {
        //laW = maW;
        //дальше
    }
    else
    {
        for (int i=0; i<k; i++)
        {
            if (CONV[i] == 0)
                continue;
            if (FA[i] > c("Fax"))
            {
                if (inInterval(FA[i], FaR, dFaR))
                {
                    SaR += FA[i];
                    laR++;
                }
            }
            else
            if (FA[i] < c("Fam"))
            {
                if (inInterval(FA[i], FaL, dFaL))
                {
                    SaL += FA[i];
                    laL++;
                }
            }
            else
            {
                if (inInterval(FA[i], Fa, dFa))
                {
                    Sa += FA[i];
                    la++;
                }
            }
        }
    }

    //
    laW = maW;

    //рассчёт средних частот
    if (laL){
        FaL = SaL / laL; dFaL = c("q1")*sqrt(FaL);
    } else { FaL = 0;}
    if (la ){
        Fa  = Sa  / la ; dFa  = c("q1")*sqrt(Fa);
    } else { Fa = 0;}
    if (laR){
        FaR = SaR / laR; dFaR = c("q1")*sqrt(FaR);
    } else { FaR = 0;}
    /*
    if (laW){
        FaW = SaW / laW; dFaW = c("q1")*sqrt(FaW);
    } else { FaW = 0;}
    */

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "FA: %2i %5.1f %5.1f | %2i %5.1f, %2i %5.1f, %2i %5.1f | %2i %5.1f",
        man, Fan, sigmaFan, laL, FaL, la, Fa, laR, FaR, laW, FaW);
        if (strcmp(FADebugStr, debugstr) != 0)
            P->m(debugstr);
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP(void)
{
    if (mpW == n)
    {
        MakeP0();
    }
    else
    if (mp > 0)
    {
        MakeP1();
    }
    else
    if (mpL > 0)
    {
        MakeP2();
    }
    else
    if (mpR > 0)
    {
        MakeP3();
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP0(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "P0 ");

    diag = diag | D_IDLE;
    if (FpW <= c("FpF") && FaW <= c("FaF"))
    {
        if (FpW < 1) /* FpW == 0*/
        {
            diag = diag | D_P_BREAK;
        }
        else
        {
            diag = diag | D_SOURCE;
        }
        C.P.setNull();
    }
    else
    {
        C.P.val = 0;
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP1(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "P1 ");

    if ((mp+mpR)>0 && (Fp+FpR)>0)
    {
        double F = (Fp*mp + FpR*mpR)/(mp+mpR);
        C.P.val = ((mp+mpR)/1800.0)*(-c("alpha")*log(F) + c("beta"));
        if (C.P.val < P_MIN)
        {
            C.P.val = 0;
        }
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP2(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "P2 ");

    double FpS;
    if (mpL || mpW)
    {
        FpS = (SpL + SpW)/(mpL + mpW);
        if (FpS <= c("FpF"))
        {
            if (FpS < 0.1)
            {
                diag = diag | D_P_BREAK;
            }
            else
            {
                if (FaL <= c("FaF"))
                {
                    diag = diag | D_SOURCE;
                }
            }
            C.P.setNull();
        }
        else
        {
            diag = diag | D_P_LESS;
            C.P.val = 0;
        }
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP3(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "P3 ");

    dFpP = 0;
    dFaP = 0;
    if (c("FpP") > 0) dFpP = c("q") * sqrt(c("FpP"));
    if (c("FaP") > 0) dFaP = c("q") * sqrt(c("FaP"));
    if (FpR < c("FpP")-dFpP)
    {
        diag = diag | D_P_SMALLLOAD;
        if (inInterval(FaL, c("FaP"), dFaP) && laL>0 && la==0 && laR==0)
        {
            MakeP4();
            C.P.val = 0;
        }
        else
        {
            MakeP1();
        }
    }
    else
    {
        if (FpR > c("FpP")+dFpP)
        {
            if (inInterval(FaL, c("FaP"), dFaP) && laL>0 && la==0 && laR==0)
            {
                diag = diag | D_P_MORE;
                MakeP4();
            }
            else
            {
                diag = diag | D_P_EXCITED;
                C.P.setNull();
            }
        }
        else
        {
            diag = diag | D_EMPTY | D_P_N;
            C.P.val = 0;
        }
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeP4(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "P4 ");

    double jpP = c("jpP");
    double SpP = c("SpP");
    SpP = ((SpP*jpP) + FpR) / (jpP + 1);
    jpP += 1;
    s("jpP", jpP);
    s("SpP", SpP);
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "SpP=%5.1f, jpP=%5.1f", SpP, jpP);
        P->m(debugstr);
    }
    if (jpP >= c("npP"))
    {
        double newFpP = SpP;
        SpP = 0; jpP = 0;
        s("jpP", jpP);
        s("SpP", SpP);
        addCalibrArc(P->title, P->getCoaltype(), "FpP", newFpP);
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeA(void)
{
    if (laW == k)
    {
        diag = diag | D_IDLE;
        if (FaW <= c("FaF"))
        {
            if (FaW == 0)
            {
                diag = diag | D_A_BREAK;
            }
            else
            {
                diag = diag | D_SOURCE;
            }
            C.A.setNull();
        }
        else
        {
            C.A.setNull();
        }
    }
    else
    if (la > 0)
    {
        MakeAB();
    }
    else
    if (laR > 0)
    {
        MakeAC();
    }
    else
    {
        MakeAA();
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAA(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "AA ");

    double FaS;
    if (laL + laW == 0)
    {
        P->m("laL+laW=0!");
        return;
    }
    dFpP = 0;
    dFaP = 0;
    if (c("FpP") > 0) dFpP = c("q") * sqrt(c("FpP"));
    if (c("FaP") > 0) dFaP = c("q") * sqrt(c("FaP"));
    FaS = (FaL*laL + FaW*laW)/(laL + laW);
    if (inInterval(FaL, c("FaP"), dFaP))
    {
        diag = diag | D_EMPTY | D_A_N;
        C.A.setNull();
    }
    else
    if (FaS <= c("FaF"))
    {
        if (FaS == 0)
        {
            diag = diag | D_A_BREAK;
        }
        else
        {
            diag = diag | D_SOURCE;
        }
        C.A.setNull();
    }
    else
    if (C.P.isNull)
    {
        diag = diag | D_A_LESS;
        C.A.setNull();
    }
    else
    if (inInterval(FpR, c("FpP"), dFpP/sqrt(c("NdP"))) && mpR>0 && mp==0 && mpL==0)
    {
        if (P->runningFeeder)
        {
            diag = diag | D_A_LESS;
        }
        else
        {
            double jaP = c("jaP");
            double SaP = c("SaP");
            SaP = ((SaP*jaP) + FaL) / (jaP+1);
            jaP += 1;
            sall("jaP", jaP);
            sall("SaP", SaP);
            if (core.vi("debug") & CORE_DEBUG_ALGO)
            {
                sprintf(debugstr, "SaP=%5.1f, jaP=%5.1f", SaP, jaP);
                P->m(debugstr);
            }
            if (jaP >= c("naP"))
            {
                double newFaP = SaP;
                double dFaP;
                SaP = 0; jaP = 0;
                sall("jaP", jaP);
                sall("SaP", SaP);
                addCalibrArc(P->title, P->getCoaltype(), "FaP", newFaP);

                dFaP = newFaP - c("FaP");
                if (core.vi("debug") & CORE_DEBUG_ALGO)
                {
                    sprintf(debugstr, "пустой конвейер новое FaP=%5.1f , dFaP=%5.1f", newFaP, dFaP);
                    P->m(debugstr);
                }

                if (c("ctrlCalibration")>0)
                {
                    sall("FaP",  newFaP);
                    sall("dFaP", dFaP);
                }
            }
        }
        C.A.setNull();
    }
    else
    {
        if (diag & D_P_SMALLLOAD)
        {
            MakeAB();
        }
        else
        {
            diag = diag | D_A_LESS;
            C.A.setNull();
        }
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAB(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "AB ");

    if (diag & D_P_SMALLLOAD)
    {
        if (FpR < c("FpK"))
        {
            MakeAD();
        }
        else
        {
            C.A.setNull();
        }
    }
    else
    {
        MakeAE();
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAC(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "AC ");

    if (FaR > c("Fax")+c("q")*sqrt(c("Fax")))
    {
        diag = diag + D_A_EXCITED;
    }
    else
    {
        diag = diag + D_A_MORE;
    }
        C.A.setNull();
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAD(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "AD ");

    double FaMH;
    if (c("ctrlP"))
    {
        if (la == 0)
        {
            FaMH = FaL;
        }
        else
        {
            FaMH = Fa;
        }
        double t, z;
        t = c("alpha1") + c("beta1")*C.P.val + c("gamma1")*C.P.val*C.P.val;
        z = c("alpha2") + c("beta2")*C.P.val + c("gamma2")*C.P.val*C.P.val;
        if (core.vi("debug") & CORE_DEBUG_ALGO)
        {
            sprintf(debugstr, "коррекция зольности по малой нагрузке t=%5.3f, z=%5.3f", t, z);
            P->m(debugstr);
        }
        if (t>1 && z<0)
        {
            Fa = t*FaMH + z;
            if (core.vi("debug") & CORE_DEBUG_ALGO)
            {
                sprintf(debugstr, "скорректированое Fa=%5.1f", Fa);
                P->m(debugstr);
            }
            MakeAE();
        }
        else
        {
            diag = diag | D_A_LESS;
            C.A.setNull();
        }
    }
    else
    {
        diag = diag | D_A_LESS;
        C.A.setNull();
    }
}

//---------------------------------------------------------------------------
void CqmAlgorithm::MakeAE(void)
{
    if (core.vi("debug") & CORE_DEBUG_ALGO)
        strcat(MakeOrderStr, "AE ");

    if (man)
        C.A.val = c("a")*Fa*Fa + c("b")*Fa + c("c");
}

//---------------------------------------------------------------------------
double CqmAlgorithm::c(char * calibrname)
{
    return calibration[std::string(calibrname)];
}

//---------------------------------------------------------------------------
void CqmAlgorithm::s(char * calibrname, double val)
{
    calibration[std::string(calibrname)] = val;
    setCqmCalibration(P->name, P->getCoaltype(), calibrname, val);
}

//---------------------------------------------------------------------------
void CqmAlgorithm::sall(char * calibrname, double val)
{
    setAllCqmCalibration(P->name, calibrname, val);
}

//---------------------------------------------------------------------------
bool inInterval(double what, double base, double delta)
{
    bool ret =false;
    if (base-delta <= what && what <= base+delta)
        ret = true;
    return ret;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

