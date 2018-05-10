


class PQueue
{
public:
	PQueue();
	PQueue(int size);
	void push(Board* x);
	Board* pop();
	int getSize();
	Board* peek();

	int size = 0;
	Board** q;

private:
	void swapup(int i);
	void swapdown(int i);
	int parent(int i);
	int childL(int i);
	int childR(int i);
	void swap(int a, int b);

};


