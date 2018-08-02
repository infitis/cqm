//---------------------------------------------------------------------------
#include <strstream>
#include <math.h>

//---------------------------------------------------------------------------
#include "cqmvagon_cn.h"
#include "ctrlpntclass.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmpoint.h"
#include "cqmalgorithm.h"

//---------------------------------------------------------------------------
CqmVagonCurNext::CqmVagonCurNext(void)
{
    classid = CQM_VAGON_CURNEXT;
    strcpy(name, "noname");
    strcpy(title, "notitle");
    strcpy(pointname, "nopoint");
    strcpy(eovsigname, "noeovsignal");
    P = 0; pid = -1;
    strcpy(mytype, "������");
}

//---------------------------------------------------------------------------
CqmVagonCurNext::~CqmVagonCurNext(void)
{
}

//---------------------------------------------------------------------------
void CqmVagonCurNext::Start(void)
{
    pid = core.compute->getPointId(pointname);
    P = core.compute->points[pid];

    eov  = 0;
    teov = 0;
    id = lastemptyvagon(name);
    if (id == 0)
    {
        sprintf(debugstr, "��������� ����� �� ������.", id);
        m(debugstr);
        id = AddVagon();
    }
    else
    {
        sprintf(debugstr, "��������� ����� ������; ������ � ����, id=%i.", id);
        m(debugstr);
    }
    id2 = AddVagon();
    h.setEmpty();
    h2.setEmpty();
    np = 0;  F = 0;  lnFp = 0;
    np2 = 0; F2 = 0; lnFp2 = 0;
    coaltype  = 0;

    w2_after_eov = 0;
}

//---------------------------------------------------------------------------
void CqmVagonCurNext::Make(void)
{
    vnp = 0;    vnp2= 0;
    F=0;        F2=0;

    svnp = 0;
    for (int i=0; i<P->a->n; i++)
    {
        if (P->s[i][P->convName] != 0 &&
            P->s[i][P->fpName] >= P->a->c("Fpm") &&
            (P->s[i][name_f1] == 1 || P->s[i][name_f2] == 1))
        {
            svnp = svnp + 1;
        }
    }

    for (int i=0; i<P->a->n; i++)
    {
        if (P->s[i][P->convName] != 0)
        {
            if (P->s[i][P->fpName] >= P->a->c("Fpm"))
            {
                if (P->s[i][name_f1] == 1 && P->s[i][name_f2] == 0)
                {
                    //����� 2 �������
                    w2_after_eov = 0;
                    vnp = vnp + 1;
                    F = (F*(vnp-1) + P->s[i][P->fpName]) / vnp;
                }
                if (P->s[i][name_f1] == 0 && P->s[i][name_f2] == 1)
                {
                    if (w2_after_eov == 1)
                    {
                        //��� �� ����� 2 - �������, ������� �� ����� 1
                        vnp = vnp + 1;
                        F = (F*(vnp-1) + P->s[i][P->fpName]) / vnp;
                    }
                    else
                    {
                        vnp2 = vnp2 + 1;
                        F2 = (F2*(vnp2-1) + P->s[i][P->fpName]) / vnp2;
                    }
                }
                if (P->s[i][name_f1] == 1 && P->s[i][name_f2] == 1)
                {
                    if (w2_after_eov == 1)
                    {
                        //��� �� ����� 2 - �������, ������� �� ����� 1
                        vnp = vnp + 1;
                        F = (F*(vnp-1) + P->s[i][P->fpName]) / vnp;
                    }
                    else
                    {
                        vnp = vnp + 0.5;
                        F = (F*(vnp-0.5) + P->s[i][P->fpName]) / vnp;
                        vnp2 = vnp2 + 0.5;
                        F2 = (F2*(vnp2-0.5) + P->s[i][P->fpName]) / vnp2;
                    }
                }
            }
        }
        //�������� ��
        if (eov == core.vi("eov") && core.compute->s[i][eovsigname])
        {
            //��������, ��� ��� �� - ����� 2 ��������.
            //���� ��� �� ���������� ������� � ����� 1(�� �� - ����� 2)
            if (P->s[i][name_f2] == 1) w2_after_eov = 1;
            OnPressEov();
        }

        if (core.compute->s[i][eovsigname])
            eov++;
        else
            eov = 0;

    }
    StoreVagon();
}

//---------------------------------------------------------------------------
void CqmVagonCurNext::StoreVagon(void)
{
    Coal newCoal = P->getCoal();
    Coal newCoal2= P->getCoal();
    Coal PCoal   = P->getCoal();
    if (PCoal.P.val != 0 && !PCoal.P.isNull)
    {
        if (svnp && vnp)
        {
            newCoal.P.val = double(vnp) / svnp * newCoal.P.val;
            if (F > 0.1 && F < 100000)
                lnFp = (lnFp*np + log(F)*vnp) / (np + vnp);
        }
        else
        {
            newCoal.setempty();
        }
        np += vnp;

        if (svnp && vnp2)
        {
            newCoal2.P.val = double(vnp2) / svnp * newCoal2.P.val;
            if (F2 > 0.1 && F2 < 100000)
                lnFp2 = (lnFp2*np2 + log(F2)*vnp2) / (np2 + vnp2);
        }
        else
        {
            newCoal2.setempty();
        }
        np2 += vnp2;
    }

    //******** ����� ������� ********
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "����� �������, id = %i.", id);
        m(debugstr);
        strstream ss; char tmpstr[MAX_NAME_LEN] = "";
        ss<<"����������:"<<newCoal;
        ss.getline(tmpstr, MAX_NAME_LEN);
        sprintf(debugstr, "    vnp=%2.1f, svnp=%i, np=%2.1f, %s", vnp, svnp, np, tmpstr);
        m(debugstr);
    }
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"��____:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        char tmp[MAX_NAME_LEN]="    ";strcat(tmp, debugstr);strcpy(debugstr, tmp);
        m(debugstr);
    }
    if (vnp > 0)
    {
        h.addCoal(newCoal);
    }
    else
    {
        if (core.vi("debug") & CORE_DEBUG_ALGO)
        {
            m("    ������ �� ���������; vnp=0.");
        }
    }

    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"�����_:"<<h<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        char tmp[MAX_NAME_LEN]="    ";strcat(tmp, debugstr);strcpy(debugstr, tmp);
        m(debugstr);
    }

    //******** ����� ��������� ********
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        sprintf(debugstr, "����� ���������, id2 = %i.", id2);
        m(debugstr);
        strstream ss; char tmpstr[MAX_NAME_LEN] = "";
        ss<<"����������:"<<newCoal2;
        ss.getline(tmpstr, MAX_NAME_LEN);
        sprintf(debugstr, "    vnp2=%2.1f, svnp=%i, np2=%2.1f, %s", vnp2, svnp, np2, tmpstr);
        m(debugstr);
    }
    if (core.vi("debug") & CORE_DEBUG_ALGO)
    {
        strstream ss;
        ss<<"��____:"<<h2<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        char tmp[MAX_NAME_LEN]="    ";strcat(tmp, debugstr);strcpy(debugstr, tmp);
        m(debugstr);
    }
    if (vnp2 > 0)
    {
        h2.addCoal(newCoal2);
    }
    else
    {
        if (core.vi("debug") & CORE_DEBUG_ALGO)
        {
            m("    ������ �� ���������; vnp2=0.");
        }
    }

    if (P->a->c("debug")>0)
    {
        strstream ss;
        ss<<"�����_:"<<h2<<endl;
        ss.getline(debugstr, MAX_NAME_LEN);
        char tmp[MAX_NAME_LEN]="    ";strcat(tmp, debugstr);strcpy(debugstr, tmp);
        m(debugstr);
    }

    setvagon(id,  coaltype, h.c.P.val,  h.c.A.val,  np,  lnFp);
    setvagon(id2, coaltype, h2.c.P.val, h2.c.A.val, np2, lnFp2);
}

//---------------------------------------------------------------------------
void CqmVagonCurNext::OnPressEov(void)
{
    time_t now = time(0);
    if (now-teov >= core.vi("minteov"))
    {
        sprintf(debugstr, "����� ������; ��������� ���� %i ��� �����.", now-teov);
        teov = now;
        m(debugstr);
        StoreVagon();
        //�� 2 � 1
        id = id2; h = h2; np = np2; F = F2; lnFp = lnFp2; vnp = 0;
        id2 = AddVagon();
        h2.setEmpty(); np2 = 0; F2 = 0; lnFp2 = 0; vnp2 = 0;
    }
}

//---------------------------------------------------------------------------
int CqmVagonCurNext::AddVagon(void)
{
    int thisid = addvagon(name);
    if (thisid == -1)
    {
        sprintf(debugstr, "�� %s addvagon error: id=%i", title, thisid);
        m(debugstr);
    }
    else
    {
        sprintf(debugstr, "�� %s �������� �����: id=%i", title, thisid);
        m(debugstr);
    }
    return thisid;
}

//---------------------------------------------------------------------------
istream& CqmVagonCurNext::Input(istream& s)
{
    return s>>name>>title>>pointname>>eovsigname>>name_f1>>name_f2;
}

//---------------------------------------------------------------------------
ostream& CqmVagonCurNext::Print(ostream& s)
{
    return s<<classid<<"\t"<<name<<"\t"<<title<<"\t"<<pointname<<"\t"
            <<eovsigname<<"\t"<<name_f1<<"\t"<<name_f2;
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmVagonCurNext& p)
{
	return p.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmVagonCurNext& p)
{
    return p.Input(s);
}

//---------------------------------------------------------------------------

