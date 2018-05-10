#include "pqueue.h"


PQueue::PQueue()
{
	PQueue(1);
}
PQueue::PQueue(int cap)
{
	q = new Board*[cap];
	size = 0;	
}
Board* PQueue::peek()
{
	return q[0];
}
void PQueue::push(Board* x)
{
	q[size] = x;
	size ++;
	swapup(size-1);
}
Board* PQueue::pop()
{
	Board* x = q[0];
	q[0] = q[size-1];
	size --;
	swapdown(0);
	return x;
}
void PQueue::swapup(int i)
{
	int p = parent(i);
	if( p >= 0 && p < size && *q[i]->fitness > *q[p]->fitness )
	{
		swap(i, p);
		swapup(p);
	}
}
void PQueue::swapdown(int i)
{
	int l = childL(i), r = childR(i);
	if( l<size && *q[i]->fitness < *q[l]->fitness )
	{
		swap(i, l);
		swapdown(l);
	}
	if( r<size && *q[i]->fitness < *q[r]->fitness )
	{
		swap(i, r);
		swapdown(r);
	}
}
void PQueue::swap(int a, int b)
{
	Board* tmp = q[a];
	q[a] = q[b];
	q[b] = tmp;
}
int PQueue::parent(int i)
{
	return (i+1)/2-1;
}
int PQueue::childL(int i)
{
	return 2*i+1;
}
int PQueue::childR(int i)
{
	return 2*i+2;
}




