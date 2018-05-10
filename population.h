

class Population
{
public:
	Population();
	Population(Genome*** parents, int sets);
	float averageFitness;
	int bestFitness;
	Genome*** bestGenomes;


private:
	void calculateFitnessLevels();

	PQueue q;


};




