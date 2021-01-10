/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

#include "ball.h"
#include "paddle.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// //Initialize PNG loading
				// int imgFlags = IMG_INIT_PNG;
				// if( !( IMG_Init( imgFlags ) & imgFlags ) )
				// {
				// 	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				// 	success = false;
				// }
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit(); //requires SDL_Image extension
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			// Create the game objects:
			// The ball that will be moving around on the screen
			// The paddle will move up and down on given X-Pos
			Ball ball(SCREEN_WIDTH,SCREEN_HEIGHT);
			Paddle paddleLeft(SCREEN_WIDTH,SCREEN_HEIGHT, 30);
			Paddle paddleRight(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_WIDTH - Paddle::PADDLE_WIDTH - 30);

			//While application is running
			while( !quit )
			{
				// TODO: move this to a controller class
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the ball
					ball.handleEvent( e );
					paddleLeft.handleEvent(e); 
					paddleRight.handleEvent(e); 
				}

				// TODO: move this to a Game/Logic/Calculation class
				//Move the ball
				ball.move();
				paddleLeft.move();
				paddleRight.move();
				// Check collisions
				// Update scores
				// Manage game events: e.g. increase difficulty level/ball speed.
				// ...


				// TODO: move this to a Render class
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
				ball.render(gRenderer);
				paddleLeft.render(gRenderer);
				paddleRight.render(gRenderer);
				//TODO: render scores.

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}