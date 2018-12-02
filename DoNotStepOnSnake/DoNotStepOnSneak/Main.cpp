#include "Include.h"

Draw draw;
ControlsAndMechanics game;
int main(int argc, char* args[])
{
	//Start SDL and prepare first window
	draw.init();
	game.randomApple();
	game.createSnake(Snake::numberStartingSegments);
	//While application is running
	while (!Snake::quit)
	{
		game.move();
		game.controls();
		draw.draw();
	}
	draw.close();
	
	return 0;
}