#pragma once
class ControlsAndMechanics
{
public:
	//how ofen snake will step forward
	Uint32 stepTime = SDL_GetTicks();
	//snake moving direction
	enum directions { left, right, top, down };
	//check if snake can move in choosed direction
	bool ableToMove(int direction); 
	void controls();
	void move();
	bool tailBite();
	bool stepOnApple();
	void createNextApple();
	void randomApple();
	void createSnake(int numberStartingSegment);
};
