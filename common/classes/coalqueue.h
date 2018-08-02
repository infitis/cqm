//---------------------------------------------------------------------------
#ifndef coalqueueH
#define coalqueueH

//---------------------------------------------------------------------------
#include "defines.h"
#include "coalheap.h"

//---------------------------------------------------------------------------
const int COALQUEUE_MIN_SIZE = 1;
const int COALQUEUE_MAX_SIZE = 2000;

//---------------------------------------------------------------------------
class CoalQueue
{
    public:
    CoalQueue(int coalsize);
    ~CoalQueue();

    Coal move(Coal c);

    Coal getCoal();
    CoalHeap getCoalHeap();

    int getsize();

    private:
    int size;
    Coal* queue;
};

//---------------------------------------------------------------------------
#endif
