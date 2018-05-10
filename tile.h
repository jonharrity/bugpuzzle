

struct BugChunk
{
	int type, half;
};



class Tile
{
public:
	Tile();
	Tile(int id, int ori);

	int bugId;
	int orientation;



	//side: 	NORTH ,     EAST ,        SOUTH ,      WEST (clockwise)
	//bugtype: 	ladybug, grasshopper, beetle (purple), bee (red/yellow)
	//      	   0          1              2                3

	//[ID][SIDE][0] = bugtype
	//[ID][SIDE][1] = head (0) / tail (1)
	static BugChunk bugs[9][4];
};


//the board definition linking tile IDs and bug types to the given picture
BugChunk Tile::bugs[9][4] = 	{
		{ {2,0}, {0,1}, {1,1}, {3,0} },		//1
		{ {3,0}, {3,1}, {1,1}, {0,0} },		//2
		{ {1,0}, {0,0}, {2,1}, {3,1} },		//3
		{ {1,1}, {3,0}, {2,0}, {0,0} },		//4
		{ {0,0}, {0,1}, {1,0}, {2,0} },		//5
		{ {1,0}, {3,0}, {2,1}, {0,0} },		//6
		{ {2,1}, {3,1}, {0,1}, {1,1} },		//7
		{ {2,0}, {3,0}, {1,1}, {0,1} },		//8
		{ {2,0}, {1,1}, {2,1}, {3,0} },		//9
	};


