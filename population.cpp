#include "pqueue.cpp"
#include "population.h"


Population::Population()
{

}

Population::Population(Genome*** breed, int sets)
{
	int boardsPerSet = POPULATION_SIZE / sets;
	q = PQueue(POPULATION_SIZE);
	long total = 0;
	Board* newBoard;
	for( int i=0 ; i<sets ; i++ )
	{
		Genome** parents = breed[i];
		for( int j=0 ; j<boardsPerSet ; j++ )
		{
			newBoard = new Board(parents);
			total += *(newBoard->fitness);
			q.push(newBoard);
		}
	}



	averageFitness = (float) total / POPULATION_SIZE;
	bestFitness = *q.peek()->fitness;
	bestGenomes = new Genome**[sets];
	int n = 0;
	for( int i=0 ; i<sets ; i++ )
	{
		bestGenomes[i] = new Genome*[PARENT_COUNT];
		for( int j=0 ; j<PARENT_COUNT ; j++ )
		{
			bestGenomes[i][j] = q.pop()->genome;
			n ++;
		}
	}
	for( int i=0 ; i<q.size ; i++ )
		delete q.q[i];
		
}






