



class Genome
{
public:
	Genome();
	Genome(Genome** parents);
	~Genome();
	string toString();
	int getIntFrom(int start, int end);
	void setIntAt(int start, int end, int x);

private:
	bool* chromosomes;
};
