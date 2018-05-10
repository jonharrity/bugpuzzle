

//run the GA algorithm to completion or termination to reach the goal genome state

Response solve(int parentCount, int mutationPercent, int populationSize, int breedingSelection, int maxGens)
{
	int breedSize = populationSize * breedingSelection / 100;
	int parentSetCount = breedSize / parentCount;


	Genome*** parents = new Genome**[parentSetCount];
	for( int i=0 ; i<parentSetCount ; i++ )
	{
		parents[i] = new Genome*[parentSetCount];
		for( int j=0 ; j<parentCount ; j++ )
			parents[i][j] = new Genome();
	}


	Population pop;


	Genome* solution;
	float avgFitness = 0.0;
	int bestFitness = 0;
	int genCount = 0;
	int desiredFitness = 24;
	bool didSolve = false;
	do
	{
		pop = Population(parents, parentSetCount);
		genCount ++;
		avgFitness = pop.averageFitness;
		bestFitness = pop.bestFitness;
		parents = pop.bestGenomes;
		if( bestFitness == desiredFitness )
		{
			solution = parents[0][0];
			didSolve = true;
		}

	}
	while( !didSolve && genCount < maxGens);

	Response answer;
    	if( didSolve) 
		answer = {solution->toString(), genCount};
	else
		answer = {"", -1};

	delete parents;

	return answer;
}

