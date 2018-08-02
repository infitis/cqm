//---------------------------------------------------------------------------
#include <strstream>
#include <string.h>

//---------------------------------------------------------------------------
#include "cqmcoalqueue.h"
#include "cqmcore.h"
#include "cqmcompute.h"
#include "cqmstreamparse.h"
#include "defines.h"
#include "coalheap.h"
#include "cqmfuncs.h"

//---------------------------------------------------------------------------
CqmCoalQueue::CqmCoalQueue() : CqmEntity()
{
    strcpy(name, "noname");
    strcpy(title, "notitle");
    strcpy(mytype, "�������");

    conv_name[0] = 0;

    coal_source_id = NO_CQM_ENTITY;
    queue_source_id = NO_CQM_ENTITY;
    size = 0;

    coal_source_name[0] = 0;
    FunctionName[0] = 0;
    Args[0] = 0;
    fid = NO_CQM_ENTITY;

    argCount = 0;
    conv_worked = 0;
}

//---------------------------------------------------------------------------
CqmCoalQueue::~CqmCoalQueue()
{
}

//---------------------------------------------------------------------------
void CqmCoalQueue::Start(void)
{
    CqmEntity::Start();

    coal_source_id = core.compute->getEntityId(coal_source_name);
    try{
        queue_source_id = core.compute->getCoalQueueId(coal_source_name);
    }
    catch(...)
    {
        //�������� -- �� �������
        //����� �������������� coal_source_id -- ������ ��������
        queue_source_id = NO_CQM_ENTITY;
    }

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

    cq = new CoalQueue(size);

    if (size != cq->getsize())
    {
        size = cq->getsize();
        char b[64];
        sprintf(b, "���������� ������������ ������: %i �����.", size);
        m(b);
    }
}

//---------------------------------------------------------------------------
void CqmCoalQueue::Stop(void)
{
    delete cq;

    for (int i=0; i<argCount; i++)
    {
        delete[] argNames[i];
        delete[] argValues[i];
    }
    argCount = 0;

    CqmEntity::Stop();
}

//---------------------------------------------------------------------------
void CqmCoalQueue::Make(void)
{
    active = 0;
    //������ ��������� ����
    Coal ci;
    //���� ��������� ����
    CoalHeap hi;
    hi.setEmpty();
    //������� �������� �������
    for (int i=0; i<DATA_SIZE; i++)
    {
        outputc[i].setempty();
    }

    //���������� ������ ����������� ���������
    conv_worked = 0;
    for (int i=0; i<core.compute->dataCount; i++)
    {
        //���� �������� �������
        if (core.compute->s[i][conv_name])
        {
            //�������� ���������� ���� ������ �� ������
            conv_worked++;
        }
    }

    if (conv_worked == 0)
    {
        if (core.vi("debug") & CORE_DEBUG_ENTITYS)
        {
            m("�������");
        }
        return;
    }


    //��������� ������� ��������
    core.compute->functions[fid]->Prepare();
    for (int i=0; i<core.compute->dataCount; i++)
    {
        //���� �������� �������
        if (core.compute->s[i][conv_name])
        {
            //��������, ���� �� �������
            for (int j=0; j<argCount; j++)
            {
                char*  var = argNames[j];
                double val = core.compute->s[i][argValues[j]];
                core.compute->functions[fid]->addVariable(var, val);
            }
            //���������
            double feeder = core.compute->functions[fid]->Solve();
            if (feeder > 0)
            {
                //�������� ����� �������� ������
                active++;
                //������� �������� ���� �� ������� ��� �� ���������
                if (queue_source_id != NO_CQM_ENTITY)
                {
                    ci = core.compute->coalqueues[queue_source_id]->outputc[i];
                    ci.P.val *= feeder;
                }
                else
                {
                    ci = core.compute->entitys[coal_source_id]->getCoal();
                    ci.P.val = ci.P.val / conv_worked * feeder;
                }
            }
            else
            {
                //�������� �� �������
                ci.setempty();
            }
            //����c��� � ������ ������� ����� �������� ���� �
            //������ ������� �� ������� � ����c��� ��� � �������� ������
            outputc[i] = cq->move(ci);
            //�������� ��������� ����
            hi.addCoal(ci);
            //cq.push(ci);
            //outputc[i] = cq.front();
            //cq.pop();
        }
    }
    core.compute->functions[fid]->Finish();

    if (conv_worked == 0)
    {
        active = 0;
    }
    else
    {
        active = active / conv_worked;
    }

    //debug
    if (core.vi("debug") & CORE_DEBUG_ENTITYS)
    {
        std::strstream s;
        s<<"�������� �������: ";
        Coal curcoal, prevcoal; int coaln = 0;

        for (int i=0; i<core.compute->dataCount; i++)
        {
            //���� �������� �������
            if (core.compute->s[i][conv_name])
            {
                curcoal = outputc[i];
                if (curcoal == prevcoal)
                {
                    coaln++;
                }
                else
                {
                    if (coaln > 0)
                    {
                        s<<" ( "<<prevcoal<<" )x "<<coaln<<" |";
                    }
                    coaln = 1;
                }
                prevcoal = curcoal;
            }
        }
        if (coaln > 0)
            s<<" ( "<<curcoal<<" )x "<<coaln<<" |";

        s<<endl;
        s.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);

        CoalHeap ho = this->getCoalHeap();
        CoalHeap hq = cq->getCoalHeap();
        s<<"����������: "<<active
         <<"; ����: "<<hi
         <<"; �������: "<<hq
         <<"; �����: "<<ho
         <<endl;
        s.getline(debugstr, MAX_NAME_LEN);
        m(debugstr);
    }
}

//---------------------------------------------------------------------------
CoalHeap CqmCoalQueue::getCoalHeap(void)
{
    CoalHeap h;
    for (int i=0; i<conv_worked; i++)
    {
        h.addCoal(outputc[i]);
    }
    return h;
}

//---------------------------------------------------------------------------
Coal CqmCoalQueue::getCoal(void)
{
    CoalHeap h = this->getCoalHeap();
    return h.c;
}

//---------------------------------------------------------------------------
istream& CqmCoalQueue::Input(istream& s)
{
    s>>name>>title>>conv_name>>coal_source_name>>size>>FunctionName;

    //���� ���������
    GetQuote(s, Args, MAX_NAME_LEN, '(', ')');

    return s;
}

//---------------------------------------------------------------------------
ostream& CqmCoalQueue::Print(ostream& s)
{
    return s<<name<<"\t"<<title<<"\t"<<conv_name<<"\t"<<coal_source_name<<"\t"
            <<size<<"\t"<<FunctionName<<" ( "<<Args<<" )";
}

//---------------------------------------------------------------------------
ostream& operator<< (ostream& s, CqmCoalQueue& f)
{
	return f.Print(s);
}

//---------------------------------------------------------------------------
istream& operator>> (istream& s, CqmCoalQueue& f)
{
    return f.Input(s);
}

//---------------------------------------------------------------------------
 
