


class Board
{
public:
	Board();
	Board(Genome* gen);
	Board(Genome** parents);
	~Board();
//	Board(const Board&) = delete;
	void fillTiles();

	int* fitness;
	Genome* genome;

private:
	Tile* tiles;
	void init(Genome* gen);
	int getBugId(int index);
	int getBugOrientation(int bug);
	bool isBugTaken(int bug, int max);
	void calculateOverallFitness();
	int getTileFitness(int index);
	struct Directions;
	Directions getDirections(int a, int b);



	static int adjTiles[9][5];
};



