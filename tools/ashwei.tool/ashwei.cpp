/*
	Coal heap calculator
    (c) 2005 Ruslan Keba
*/    	

#include <iostream>

#include "../../common/classes/coalheap.h"

int main ()
{
	CoalHeap h;
	double p, a;
	
	while (1)
	{
		cout<<"Enter P A: ";
		cin>>p>>a;

		if (p>0)
			h.addCoal(Coal(p,a));
		else
			h.subCoal(Coal(-p,a));

		cout<<h<<endl;
   	}
}
