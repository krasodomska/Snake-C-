#pragma once
class Snake
{
	/*Snake() {}
	Snake(const Snake &o) {}
	static Snake *theInstance;
	*/

public:
	//coordination of the snake head
	static int xCoordination;
	static int yCoordination;
	//list that contains snake body coordinations
	static std::list<Body> snakeBody;
	//size of snake
	static int size;
	static int numberStartingSegments;

	//In which direction snake moves
	static int direction;

	static Body apple;

	static int score;

	// flag if gamer want to quit
	static bool quit;
	// flag if game is over
	static bool gameOver;

	//Plane to play dimensions
	static const int planeWidth = 600;
	static const int planeHeight = 300;
	static const int planeTopMargin = 15;
	static const int planeLeftMargin = 15;


	/*static Snake& getSnake()
	{
		if (!theInstance)
			Snake::theInstance = new Snake();

		return *theInstance;
	}*/
};
