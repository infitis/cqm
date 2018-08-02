//---------------------------------------------------------------------------
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------
#include "defines.h"

//---------------------------------------------------------------------------
const double P_MIN =  0.005;
const double N_MIN =  0.03;

const double A_MIN =  1.0;
const double A_MAX = 99.9;

const double H_MIN =  1.0;
const double H_MAX = 99.9;

const double PARAM_DEVIATION = 0.005;

const double P_DEVIATION = 0.005;
const double A_DEVIATION = 0.05;
const double H_DEVIATION = 0.05;

//---------------------------------------------------------------------------
CoalParameter::CoalParameter(void)
{
    val = 0.0;
    isNull = false;
}

//---------------------------------------------------------------------------
CoalParameter::CoalParameter(const double V)
{
    val = V;
    isNull = false;
}

//---------------------------------------------------------------------------
CoalParameter::CoalParameter(const CoalParameter &A)
{
    val = A.val;
    isNull = A.isNull;
}

//---------------------------------------------------------------------------
CoalParameter& CoalParameter::operator =(const CoalParameter &A)
{
    if (this == &A) return *this;
    val = A.val;
    isNull = A.isNull;
    return *this;
}

//---------------------------------------------------------------------------
bool CoalParameter::operator ==(const CoalParameter &A)
{
    return (fabs(val-A.val)<PARAM_DEVIATION && isNull == A.isNull);
}

//---------------------------------------------------------------------------
void CoalParameter::setNull(void)
{
    isNull = true;
    val = 0;
}

//---------------------------------------------------------------------------
char* CoalParameter::format(char* fmt)
{
    if (isNull)
    {
        strcpy(str, "  NULL");
    }
    else
    {
        sprintf(str, fmt, val);
    }
    return str;
}

//---------------------------------------------------------------------------
char* CoalParameter::format(void)
{
    if (isNull)
    {
        strcpy(str, "NULL");
    }
    else
    {
        sprintf(str, "%5.2f", val);
    }
    return str;
}

//---------------------------------------------------------------------------
ostream& operator<<(ostream& s, CoalParameter& a)
{
    return s<<a.format("%6.3f");
}

//---------------------------------------------------------------------------
istream& operator>>(istream& s, CoalParameter& a)
{
    char c[MAX_STR_LEN];
    s>>c;
    if (!strcmp(c, "NULL"))
    {
        a.setNull();
    }
    else
    {
        a.val = atof(c);
    }
    return s;
}

//---------------------------------------------------------------------------
Ash::Ash(void) : CoalParameter()
{
}

//---------------------------------------------------------------------------
Ash::Ash(const double V) : CoalParameter(V)
{
}

//---------------------------------------------------------------------------
Ash::Ash(const Ash &A) : CoalParameter(A)
{
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Weight::Weight(void) : CoalParameter()
{
}

//---------------------------------------------------------------------------
Weight::Weight(const double V) : CoalParameter(V)
{
}

//---------------------------------------------------------------------------
Weight::Weight(const Weight &W) : CoalParameter(W)
{
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Humidity::Humidity(void) : CoalParameter()
{
}

//---------------------------------------------------------------------------
Humidity::Humidity(const double V) : CoalParameter(V)
{
}

//---------------------------------------------------------------------------
Humidity::Humidity(const Humidity &H) : CoalParameter(H)
{
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Coal::Coal(void)
{

}

//---------------------------------------------------------------------------
Coal::Coal(const Coal &C)
{
    P = C.P;
    A = C.A;
    H = C.H;
}

//---------------------------------------------------------------------------
Coal::Coal(const double P_, const double A_, const double H_)
{
    P = Weight(P_);
    A = Ash(A_);
    H = Humidity(H_);
}


//---------------------------------------------------------------------------
Coal& Coal::operator =(const Coal &C)
{
    if (this == &C) return *this;
    P = C.P;
    A = C.A;
    H = C.H;
    return *this;
}

//---------------------------------------------------------------------------
bool Coal::operator ==(const Coal &C)
{
    return (P == C.P && A == C.A && H == C.H);
}

//---------------------------------------------------------------------------
bool Coal::empty(void)
{
	if (A.val == 0 && P.val == 0 && H.val ==0) return true;
    return false;
}

//---------------------------------------------------------------------------
void Coal::setempty(void)
{
	A.val = P.val = H.val = 0;
}

//---------------------------------------------------------------------------
ostream& operator<<(ostream& s, Coal& c)
{
    return s<<c.P<<" "<<c.A<<" "<<c.H;
}

//---------------------------------------------------------------------------
istream& operator>>(istream& s, Coal& c)
{
    return s>>c.P>>c.A>>c.H;
}

//---------------------------------------------------------------------------

