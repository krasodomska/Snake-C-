#pragma once
class ControlsAndMechanics
{
public:
	enum directions { left, right, top, down };
	//check if snake can move in choosed direction
	bool ableToMove(int direction); 
	void controls();
	void move();
	//how ofen snake will step forward
	Uint32 stepTime = SDL_GetTicks();
	bool tailBite();
	bool stepOnApple();
	void createNextApple();
	void randomApple();
	void createSnake(int numberStartingSegment);
};
