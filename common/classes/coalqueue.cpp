//---------------------------------------------------------------------------
#include "coalqueue.h"

//---------------------------------------------------------------------------
CoalQueue::CoalQueue(int coalsize)
{
    size = coalsize;

    if (size < COALQUEUE_MIN_SIZE)
        size = COALQUEUE_MIN_SIZE;
    if (size > COALQUEUE_MAX_SIZE)
        size = COALQUEUE_MAX_SIZE;

    queue = new Coal[size];

    for (int i=0; i<size; i++)
    {
        queue[i].setempty();
    }
}

//---------------------------------------------------------------------------
CoalQueue::~CoalQueue()
{
    delete[] queue;
    size = 0; 
}

//---------------------------------------------------------------------------
Coal CoalQueue::move(Coal c)
{
    Coal ret = queue[size-1];
    for (int i=size-1; i>0; i--)
    {
        queue[i] = queue[i-1];
    }
    queue[0] = c;
    return ret;
}

//---------------------------------------------------------------------------
Coal CoalQueue::getCoal()
{
    return getCoalHeap().c;
}

//---------------------------------------------------------------------------
CoalHeap CoalQueue::getCoalHeap()
{
    CoalHeap h;
    for (int i=0; i<size; i++)
    {
        h.addCoal(queue[i]);
    }
    return h;
}

//---------------------------------------------------------------------------
int CoalQueue::getsize()
{
    return size;
}

//---------------------------------------------------------------------------


