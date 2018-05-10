#include "tile.cpp"
#include "genome.cpp"
#include "board.h"


//list the indexes of a tile adjacent to one given tile
int Board::adjTiles[9][5] = {
		{2,1,3},	//0
		{3,0,2,4},	//1
		{2,1,5},	//2

		{3,0,4,6},	//3
		{4,1,3,5,7},	//4
		{3,2,4,8},	//5
		
		{2,3,7},	//6
		{3,4,6,8},	//7
		{2,5,7}		//8
};

Board::Board()
{
	init(new Genome());
}
Board::Board(Genome** parents)
{
	init(new Genome(parents));
}
Board::Board(Genome* gen)
{
	init(gen);
}
Board::~Board()
{
	delete fitness;
	delete genome;
	delete tiles;
}


void Board::init(Genome* gen)
{
	genome = gen;
	tiles = new Tile[9];
	fillTiles();
	fitness = (int*) malloc(sizeof(int));
	calculateOverallFitness();
}

/*
void Board::evolveGenomes()
{
	Genome** parents = getMostFitGenomes();

	for( int i=0 ; i<9 ; i++ )
		genomes[i] = new Genome(parents);
}
*/

void Board::fillTiles()
{
//	for( int i=0 ; i<9 ; i++ )
//		tiles[i] = getTile(i);

	int genomePos, startId, bugId;
	for( int i=0 ; i<9 ; i++ )
	{
		genomePos = i*4;
		startId = genome->getIntFrom(genomePos, genomePos+4);
		bugId = startId;
		while( isBugTaken(bugId, i) )
			bugId = (bugId + 1) % 9;
		if( startId != bugId )
			genome->setIntAt(genomePos, genomePos+4, bugId);
		tiles[i] = Tile(bugId, getBugOrientation(bugId));
	}
}


bool Board::isBugTaken(int bug, int max)
{
	for( int i=0 ; i<max ; i++ )
		if( tiles[i].bugId == bug )
			return true;
	return false;
}


int Board::getBugOrientation(int bug)
{
	int start = 36 + 2*bug;
	return genome->getIntFrom(start, start+2);

}

void Board::calculateOverallFitness()
{
	(*fitness) = 0;
	for( int i=0 ; i<9 ; i++ )
	{
		(*fitness) += getTileFitness(i);
	}
}

struct Board::Directions
{
	int a, b;
};

//this is the main method evaluating fitness of one individual tile
int Board::getTileFitness(int index)
{
	int bugId = tiles[index].bugId;
	int matching = 0;
	for( int i=1 ; i<=adjTiles[index][0] ; i++ )//one iteration per side of tile
	{
		int otherIndex = adjTiles[index][i];
		int otherBugId = tiles[otherIndex].bugId;

		Directions directions = getDirections(index, otherIndex);
		BugChunk selfPiece = Tile::bugs[bugId][(directions.a+4-tiles[index].orientation) % 4];
		BugChunk otherPiece = Tile::bugs[otherBugId][(directions.b+4-tiles[otherIndex].orientation) % 4];
		if( (selfPiece.type==otherPiece.type) && (selfPiece.half+otherPiece.half==1) )
			matching += 1;
	}
	return matching;
}

Board::Directions Board::getDirections(int a, int b)
{
	bool sameRow = (a/3) == (b/3);
	if( a < b && sameRow )
		return {1,3};
	if( a < b && !sameRow )
		return {2,0};
	if( a > b && sameRow )
		return {3,1};
	if( a > b && !sameRow )
		return {0,2};
	return {-1,-1};
}

