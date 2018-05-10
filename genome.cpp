#include "genome.h"
#include <string>


int randInt(int a, int b)//a inclusive, b exclusive
{
	return rand()%(b-a)+a;
}

Genome::Genome()
{
	chromosomes = new bool[CHROMOSOME_COUNT];
	for( int i=0 ; i<CHROMOSOME_COUNT ; i++ )
		chromosomes[i] = false;
}
Genome::~Genome()
{
	delete chromosomes;
}


//crossover function
//print out ranges: middle 2 are 0 sometimes
Genome::Genome(Genome** parents)
{
	chromosomes = new bool[CHROMOSOME_COUNT];
	int dividerCount = PARENT_COUNT - 1;
	int crossover[dividerCount];
	int prev = 1;
	int crossoverSize = dividerCount == 0 ? CHROMOSOME_COUNT : CHROMOSOME_COUNT / dividerCount;
	for( int i=0 ; i<dividerCount ; i++ )
	{
	//	crossover[i] = randInt(prev,CHROMOSOME_COUNT-(PARENT_COUNT-i));
	//	prev = crossover[i];
		crossover[i] = (i+1) * crossoverSize;
	}
	int start = 0;
	int end = crossover[0];
	for( int i=0 ; i<PARENT_COUNT ; i++ )
	{
		for( int j=start ; j<end ; j++ )
		{
			Genome* ptr = parents[i];
			chromosomes[j] = parents[i]->chromosomes[j];
			if( randInt(0,100) < MUTATION_PERCENT )
			{
				chromosomes[j] = !chromosomes[j];
			}
		}
		start = end;
		if( (i+1)<dividerCount )
			end = crossover[i+1];
		else
			end = CHROMOSOME_COUNT;
	}
}

//[start, end)
int Genome::getIntFrom(int start, int end)
{
	int total = 0;
	int power = 1;
	for( int i=start ; i<end ; i++ )
	{
		if( chromosomes[i] )
			total += power;
		power *= 2;
	}
	return total;
}

void Genome::setIntAt(int start, int end, int x)
{
	for( int i=start ; i<end ; i++ )
	{
		chromosomes[i] = x % 2;
		x /= 2;
	}
}

string fromint(int x)
{
	string s = "";
	do
	{
		s = (char)(x%10+48) + s;
		x /= 10;
	}
	while( x > 0 );
	return s;
}

string Genome::toString()
{
	string s = "";
	for( int i=0 ; i<36 ; i+= 4 )
		s += fromint(getIntFrom(i,i+4)+1) + ",";
	s += "|";
	for( int i=36 ; i<54 ; i+= 2 )
		s += fromint(getIntFrom(i, i+2)) + ",";
	return s;
	/*
	string s = "";
	for( int i=0 ; i<CHROMOSOME_COUNT ; i++ )
		if( chromosomes[i] )
			s += "1";
		else
			s += "0";
	return s;*/
}


