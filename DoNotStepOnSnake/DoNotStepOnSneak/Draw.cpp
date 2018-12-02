#include "Include.h"


bool Draw::init()
{
	//Initialization flag
	bool success = true;

	//Create window
	gWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
			else 
			{
				//Open the font
				gFont = TTF_OpenFont("open-sans\\OpenSans-Regular.ttf", 28);
			}
		}
	}
	return success;
}

void Draw::draw()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//Render white outlined plane
	SDL_Rect outlineRect = { Snake::planeLeftMargin, Snake::planeTopMargin, Snake::planeWidth, Snake::planeHeight };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(gRenderer, &outlineRect);

	//Changing score to int, then it'a able to show on screen
	std::string stringScore = std::to_string(Snake::score);
	//Render text frame
	SDL_Color textColor = { 255, 255, 255 };
	loadFromRenderedText("Score: " + stringScore, textColor);
	render(Snake::planeLeftMargin, Snake::planeHeight + Snake::planeTopMargin);

	if (!(Snake::gameOver)) {
		//Render white filled snake
		for (Body coordination : Snake::snakeBody) {
			SDL_Rect fillSnake = { coordination.x, coordination.y, Snake::size, Snake::size };
			SDL_SetRenderDrawColor(gRenderer, 102, 0xFF, 102, 0x00);
			SDL_RenderFillRect(gRenderer, &fillSnake);
		}
		SDL_Rect fillHead = { Snake::xCoordination, Snake::yCoordination, Snake::size, Snake::size };
		SDL_SetRenderDrawColor(gRenderer, 204, 0xFF, 204, 0x00);
		SDL_RenderFillRect(gRenderer, &fillHead);

		SDL_Rect fillApple = { Snake::apple.x, Snake::apple.y, Snake::size, Snake::size };
		SDL_SetRenderDrawColor(gRenderer, 255, 0x00, 0x00, 0x00);
		SDL_RenderFillRect(gRenderer, &fillApple);
	}
	else
	{
		SDL_Color textColor = { 255, 255, 255 };
		loadFromRenderedText("GAME OVER", textColor);
		render((Snake::planeWidth-mWidth)/2 + Snake::planeLeftMargin, (Snake::planeHeight - mHeight) / 2 + Snake::planeTopMargin);

		loadFromRenderedText("press SPACE to continue", textColor);
		render((Snake::planeWidth - mWidth) / 2 + Snake::planeLeftMargin, (Snake::planeHeight - mHeight) / 2 + Snake::planeTopMargin + mHeight);
	}
	//Update screen
	SDL_RenderPresent(gRenderer);
}

void Draw::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit font
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}


bool Draw::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	//Return success
	return mTexture != NULL;
}

void Draw::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void Draw::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}