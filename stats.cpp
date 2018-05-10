const int CHROMOSOME_COUNT = 54;
int PARENT_COUNT = 2, MUTATION_PERCENT = 20, POPULATION_SIZE = 2000, BREEDING_SELECTION = 2;//these four are accepted as program parameters
int BREED_SIZE;
int PARENT_SET_COUNT;


#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#include "board.cpp"
#include "population.cpp"


string solutions[16];
int solCount = 0;
void addSolution(string newSol)
{
	cout << newSol << endl;
	for( int i=0 ; i<solCount ; i++ )
		if( solutions[i] == newSol )
			return;
	solutions[solCount] = newSol;
	solCount ++;
}

struct Response
{
	string solution;
	int genCount;
};

int toInt(char s[])
{
	int x = 0;
	int len = 0;
	while( s[len] != '\0' ) len ++;//find string length
	int power = 1;
	for( int i=len-1 ; i>=0 ; i-- )
	{
		x += ((int)s[i]-48) * power;
		power *= 10;
	}
	return x;
}	


#include "solver.cpp"

int main(int argc, char* argv[])
{
	if( argc >= 2 and argc < 7 )//display options
	{
		cout << "Param options: " << endl;
		cout << "int PARENT_COUNT = 2, MUTATION_PERCENT = 20, POPULATION_SIZE = 2000, BREEDING_SELECTION = 2, TESTS = 5; MAX_GENS = 100" << endl;
		cout << "optional g at end: Print genome sequences only (silence output other than genomes)" << endl;
		return 0;
	}

	bool OUTPUT = true;
	int tests = 5;
	int maxGens = 100;
	if( argc >= 7 )
	{
		PARENT_COUNT = toInt(argv[1]);
		MUTATION_PERCENT = toInt(argv[2]);
		POPULATION_SIZE = toInt(argv[3]);
		BREEDING_SELECTION = toInt(argv[4]);
		tests = toInt(argv[5]);
		maxGens = toInt(argv[6]);

		if( argc >= 8 && argv[7][0] == 'g' )//genomes only
			OUTPUT = false;
	}
	else
	{
		cout << "No options provided; using default" << endl;
	}

	BREED_SIZE = POPULATION_SIZE * BREEDING_SELECTION / 100;
	PARENT_SET_COUNT = BREED_SIZE / PARENT_COUNT;

	if( OUTPUT )
	{
		cout << "using options: "<<endl;
		cout << "parent count: " << PARENT_COUNT << endl;
		cout << "mutation percent: " << MUTATION_PERCENT << endl;
		cout << "population size: " << POPULATION_SIZE << endl;
		cout << "breeding selection percent: " << BREEDING_SELECTION << endl;
		cout << "number of tests: " << tests << endl;
		cout << "maximum generations per test: " << maxGens << endl;
		cout << endl;
	}


	srand(time(NULL));
	long totalGens = 0;
	int succeededTests = 0;
	Response response;
	for( int i=0 ; i<tests ; i++ )
	{
		response = solve(PARENT_COUNT, MUTATION_PERCENT, POPULATION_SIZE, BREEDING_SELECTION, maxGens);
		//if genCount < 1 then Population failed to yield solution
		//within given generation requirement.
		if( response.genCount > 0 )
		{
			totalGens += response.genCount;
			addSolution(response.solution);
			succeededTests ++;
		}

	}

	if( OUTPUT )
	{
		cout << "Average generations for solution: " << totalGens / (float) succeededTests << endl;
		cout << "Average generations including failures: " << ((tests-succeededTests)*maxGens + totalGens) / (float) tests << endl;
		cout << "Found solutions: " << solCount << endl;
		cout << "Success rate within generation limit: " << succeededTests / (float) tests * 100 << "%" << endl;
		for( int i=0 ; i<solCount ; i++ )
			cout << "winning genome " << solutions[i] << endl;
		cout << endl;
	}

	return 0;
}


