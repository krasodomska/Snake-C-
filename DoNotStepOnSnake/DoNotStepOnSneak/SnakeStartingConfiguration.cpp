#include "Include.h"

//Snake* Snake::theInstance;
int Snake::xCoordination = Snake::planeLeftMargin;
int Snake::yCoordination = Snake::planeTopMargin;
int Snake::size = 10;
int Snake::numberStartingSegments = 3;
std::list<Body> Snake::snakeBody = { };

bool Snake::quit = false;
int Snake::direction = ControlsAndMechanics::down;
bool Snake::gameOver = false;
Body Snake::apple = makeSegment(0,0);
int Snake::score = 0;