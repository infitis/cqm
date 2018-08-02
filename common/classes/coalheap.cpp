//---------------------------------------------------------------------------
#include "coalheap.h"
#include "defines.h"

//---------------------------------------------------------------------------
CoalHeap::CoalHeap(void)
{
    setEmpty();
    resetDeltaN();
}

//---------------------------------------------------------------------------
void CoalHeap::setEmpty(void)
{
    c = Coal(0, 0);
    Pa.val = 0;
    n  = 0;
    empty = true;
}

//---------------------------------------------------------------------------
void CoalHeap::setNotEmpty(void)
{
    empty = false;
}

//---------------------------------------------------------------------------
void CoalHeap::setPa()
{
    Pa = c.P;
}

//---------------------------------------------------------------------------
void CoalHeap::addCoal (Coal m)
{
    if (m.empty())
        return;

    addAsh(m);
    addHum(m);
    addWei(m);
    n += dn;
    correctCoal();
    resetDeltaN();
}

//---------------------------------------------------------------------------
void CoalHeap::addAsh (Coal m)
{
/*
    if (m.A.isNull || m.A.val<=A_MIN)
        return;

    if (c.A.isNull || c.A.val<=A_MIN)
        c.A = m.A;

    if (!c.P.isNull && !m.P.isNull && (c.P.val + m.P.val)>=P_MIN)
    {
         c.A.val = (c.A.val * c.P.val + m.A.val * m.P.val)/(c.P.val + m.P.val);
         return;
    }

    c.A.val = (c.A.val * n + m.A.val * dn)/(n + dn);
*/
    if (m.A.isNull || m.A.val<=A_MIN
     || m.P.isNull || m.P.val<=P_MIN)
        return;

    if (Pa.isNull || Pa.val<=P_MIN)
    {
        c.A = m.A;
        Pa  = m.P;
        return;
    }

    c.A.val = (c.A.val * Pa.val + m.A.val * m.P.val)/(Pa.val + m.P.val);
    Pa.val += m.P.val;
}

//---------------------------------------------------------------------------
//по идее нужно сделать так же как и для ash
void CoalHeap::addHum (Coal m)
{
    if (m.H.isNull || m.H.val<=H_MIN)
        return;

    if (c.H.isNull || c.H.val<=H_MIN)
        c.H = m.H;

    if (!c.P.isNull && !m.P.isNull && (c.P.val + m.P.val)>=P_MIN)
    {
         c.H.val = (c.H.val * c.P.val + m.H.val * m.P.val)/(c.P.val + m.P.val);
         return;
    }

    c.H.val = (c.H.val * n + m.H.val * dn)/(n + dn);
}

//---------------------------------------------------------------------------
void CoalHeap::addWei (Coal m)
{
    if (m.P.isNull || m.P.val<=P_MIN)
        return;

    if (c.P.isNull)
        return;

    c.P.val += m.P.val;
}

//---------------------------------------------------------------------------
void CoalHeap::subCoal (Coal m)
{
    if (m.empty())
        return;

    subAsh(m);
    subHum(m);
    subWei(m);
    n -= dn;
    correctCoal();
    resetDeltaN();
}

//---------------------------------------------------------------------------
void CoalHeap::subAsh (Coal m)
{
/*
    if (m.A.isNull || m.A.val<=A_MIN)
        return;

    if (c.A.isNull || c.A.val<=A_MIN)
        c.A = m.A; // можно ли так?

    if (!c.P.isNull && !m.P.isNull && (c.P.val - m.P.val)>=P_MIN)
    {
         c.A.val = (c.A.val * c.P.val - m.A.val * m.P.val)/(c.P.val - m.P.val);
         return;
    }

    if (n - dn > N_MIN )
        c.A.val = (c.A.val * n - m.A.val * dn)/(n - dn);
*/
    if (m.A.isNull || m.A.val<=A_MIN
     || m.P.isNull || m.P.val<=P_MIN)
        return;

    if (Pa.isNull || Pa.val<=A_MIN)
    {
        return;
    }

    if ((Pa.val - m.P.val) >= P_MIN)
    {
         c.A.val = (c.A.val * Pa.val - m.A.val * m.P.val)/(Pa.val - m.P.val);
         Pa.val -= m.P.val;
         return;
    }
    else
    {
        Pa.val = 0;
    }
}

//---------------------------------------------------------------------------
void CoalHeap::subHum (Coal m)
{
    if (m.H.isNull || m.H.val<=H_MIN)
        return;

    if (c.H.isNull || c.H.val<=H_MIN)
        c.H = m.H; // можно ли так?

    if (!c.P.isNull && !m.P.isNull && (c.P.val - m.P.val)>P_MIN)
    {
         c.H.val = (c.H.val * c.P.val - m.H.val * m.P.val)/(c.P.val - m.P.val);
         return;
    }

    if (n - dn > N_MIN )
        c.H.val = (c.H.val * n - m.H.val * dn)/(n - dn);
}

//---------------------------------------------------------------------------
void CoalHeap::subWei (Coal m)
{
    if (m.P.isNull || m.P.val<=P_MIN)
        return;

    if (c.P.isNull)
        return;

    c.P.val -= m.P.val;
}

//---------------------------------------------------------------------------
void CoalHeap::correctCoal(void)
{
    if (c.A.val <= A_MIN || c.A.val >= A_MAX)
        c.A.setNull();

    if (c.H.val <= H_MIN || c.H.val >= H_MAX)
        c.H.setNull();

    if (c.P.val <= P_MIN)
        setEmpty();
    else
        setNotEmpty();

    if (n <= N_MIN)
        n = 0;

}

//---------------------------------------------------------------------------
void CoalHeap::setDeltaN(double dN_)
{
    dn = dN_;
    if (dn <= 0) resetDeltaN();
}

//---------------------------------------------------------------------------
void CoalHeap::resetDeltaN(void)
{
    dn = 1.0;
}


//---------------------------------------------------------------------------
ostream& operator<<(ostream& s, CoalHeap& ch)
{
    return s<<ch.c<<" "<<ch.n<<" "<<ch.empty;
}

//---------------------------------------------------------------------------
istream& operator>>(istream& s, CoalHeap& ch)
{
    return s>>ch.c>>ch.n>>ch.empty;
}

//---------------------------------------------------------------------------
double HeatVal(Coal c, double hhv, double k)
{
    double ret = hhv*(1-c.A.val/100.0)*(1-c.H.val/100.0) -
                 2.442*(c.H.val/100.0+k*(1-c.A.val/100.0)*(1-c.H.val/100.0));
    return ret;
}

//---------------------------------------------------------------------------
AverageWeightedHeat::AverageWeightedHeat(void)
{
    setEmpty();
}

//---------------------------------------------------------------------------
void AverageWeightedHeat::add(Coal c, double hv)
{
    if (p+c.P.val > P_MIN)
    {
        heat = (heat*p + c.P.val*hv) / (p += c.P.val);
    }
}

//---------------------------------------------------------------------------
void AverageWeightedHeat::setEmpty(void)
{
    p = 0;
    heat = 0;
}

//---------------------------------------------------------------------------
double AverageWeightedHeat::getHeat(void)
{
    return heat;
}

//---------------------------------------------------------------------------

