#include "Include.h"

void ControlsAndMechanics::controls() {
	SDL_Event event;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			Snake::quit = true;
		}

		else if (event.type == SDL_KEYDOWN)
		{
			//Select direction based on key press
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					if (!(Snake::direction == down))
					{
						Snake::direction = top;
						stepTime = SDL_GetTicks();
					}
					break;

				case SDLK_DOWN:
					if (!(Snake::direction == top)) 
					{
						Snake::direction = down;
						stepTime = SDL_GetTicks();
					}
					break;

				case SDLK_LEFT:
					if (!(Snake::direction == right))
					{
						Snake::direction = left;
						stepTime = SDL_GetTicks();
					}
					break;

				case SDLK_RIGHT:
					if (!(Snake::direction == left))
					{
						Snake::direction = right;
						stepTime = SDL_GetTicks();
					}
					break;
				case SDLK_SPACE:
					Snake::gameOver = false;
					Snake::snakeBody.clear();
					createSnake(Snake::numberStartingSegments);
					Snake::direction = down;
					Snake::score = 0;
					break;
				default:
					break;
			}
		}

	}
}

//check if snake hit wall or bite itself
bool ControlsAndMechanics::ableToMove(int direction) 
{
	if (!tailBite())
	{
		if (direction == top && Snake::yCoordination > Snake::planeTopMargin)
			return true;
		else if (direction == down && Snake::yCoordination < Snake::planeHeight)
			return true;
		else if (direction == right && Snake::xCoordination < Snake::planeWidth)
			return true;
		else if (direction == left && Snake::xCoordination > Snake::planeLeftMargin)
			return true;
		else
			Snake::gameOver = true;
		return false;
	}
	else
		Snake::gameOver = true;
	return false;
}

//control snake movment
void ControlsAndMechanics::move() {
	if (!SDL_TICKS_PASSED(stepTime, SDL_GetTicks()))
	{
		stepTime += 500;
		if (ableToMove(Snake::direction))
		{
			switch (Snake::direction)
			{
				case left:
					Snake::xCoordination -= Snake::size;
					break;
				case right:
					Snake::xCoordination += Snake::size;
					break;
				case top:
					Snake::yCoordination -= Snake::size;
					break;
				case down:
					Snake::yCoordination += Snake::size;
					break;
				default:
					break;
			}
			Snake::snakeBody.push_front(makeSegment(Snake::xCoordination, Snake::yCoordination));
			if (!stepOnApple())
			{
				Snake::snakeBody.pop_back();
			}
			else
			{
				createNextApple();
				Snake::score++;
			}
		}
	}
}

//check if snake bit itself
bool ControlsAndMechanics::tailBite()
{
	std::list<Body>::iterator partOfSnake = Snake::snakeBody.begin();
	++partOfSnake;
	for (partOfSnake; partOfSnake != Snake::snakeBody.end(); ++partOfSnake)
	{
		if (*partOfSnake == Snake::snakeBody.front())
		{
			return true;
		}
	}
	return false;
}

//check if snake head step on apple
bool ControlsAndMechanics::stepOnApple()
{
	return Snake::snakeBody.front() == Snake::apple;
}

//create next apple after snake eat an apple
void ControlsAndMechanics::createNextApple() 
{
	//this prevent showing random apple under snake
	bool appleOnSnake = true;
	while (appleOnSnake)
	{
		randomApple();
		for (Body snakePart : Snake::snakeBody)
		{
			if (snakePart == Snake::apple)
			{
				appleOnSnake = true;
				break;
			}
			else
			{
				appleOnSnake = false;
			}
		}
	}
}

void ControlsAndMechanics::randomApple() 
{
	Snake::apple = makeSegment(((rand() % (Snake::planeWidth / Snake::size)) * Snake::size + Snake::planeTopMargin), ((rand() % (Snake::planeHeight / Snake::size)) * Snake::size + Snake::planeTopMargin));
}

void ControlsAndMechanics::createSnake(int numberStartingSegment)
{
	Snake::xCoordination = Snake::planeLeftMargin;
	Snake::yCoordination = Snake::planeTopMargin;
	int nextSegmentXCoordination = Snake::planeLeftMargin;
	Snake::Snake::snakeBody.push_front(makeSegment(Snake::xCoordination, Snake::yCoordination));
	for (numberStartingSegment; numberStartingSegment > 0; numberStartingSegment--)
	{
		nextSegmentXCoordination += Snake::size;
		Snake::snakeBody.push_back(makeSegment(nextSegmentXCoordination, Snake::yCoordination));
	}
}
