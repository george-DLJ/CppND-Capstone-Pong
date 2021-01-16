#include <iostream>
//#include <SDL.h>
//#include <stdio.h>
//#include <string>

#include "controller.h"
#include "game.h"
#include "renderer.h"

// //Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;

// //Starts up SDL and creates window
// bool init();

//Loads media
bool loadMedia();

// //Frees media and shuts down SDL
// void close();

// //The window we'll be rendering to
// SDL_Window* gWindow = NULL;

// //The window renderer
// SDL_Renderer* gRenderer = NULL;

//DELETE; moved to renderer class constructor
// bool init()
// {
// 	//Initialization flag
// 	bool success = true;

	
// 	//Initialize SDL
	
// 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
// 	{
// 		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
// 	else
// 	{
// 		//Set texture filtering to linear
// 		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
// 		{
// 			printf( "Warning: Linear texture filtering not enabled!" );
// 		}

// 		//Create window
// 		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
// 		if( gWindow == NULL )
// 		{
// 			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			//Create vsynced renderer for window
// 			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
// 			if( gRenderer == NULL )
// 			{
// 				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
// 				success = false;
// 			}
// 			else
// 			{
// 				//Initialize renderer color
// 				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

// 				// //Initialize PNG loading
// 				// int imgFlags = IMG_INIT_PNG;
// 				// if( !( IMG_Init( imgFlags ) & imgFlags ) )
// 				// {
// 				// 	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
// 				// 	success = false;
// 				// }
// 			}
// 		}
// 	}

// 	return success;
// }


/**
 * use only with SDL_Image library
 */ 
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

/**
 * DELETE! moved to renderer class destructor
 * 
 */
// void close()
// {
// 	//Destroy window	
// 	SDL_DestroyRenderer( gRenderer );
// 	SDL_DestroyWindow( gWindow );
// 	gWindow = NULL;
// 	gRenderer = NULL;

// 	//Quit SDL subsystems
// 	//IMG_Quit(); //requires SDL_Image extension
// 	SDL_Quit();
// }



// int main( int argc, char* args[] )
// {
	// //Start up SDL and create window
	// if( !init() )
	// {
	// 	printf( "Failed to initialize!\n" );
	// }
	// else
	// {
	// 	//Load media
	// 	if( !loadMedia() )
	// 	{
	// 		printf( "Failed to load media!\n" );
	// 	}
	// 	else
	// 	{	
	// 		//Main loop flag
	// 		bool quit = false;

			// //Event handler
			// SDL_Event e;

			// // Create the game objects:
			// // The ball that will be moving around on the screen
			// // The paddle will move up and down on given X-Pos
			// Ball ball(SCREEN_WIDTH,SCREEN_HEIGHT);
			// Paddle paddleLeft(SCREEN_WIDTH,SCREEN_HEIGHT, 30);
			// Paddle paddleRight(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_WIDTH - Paddle::PADDLE_WIDTH - 30);

			// // While application is running
			// while( !quit )
			// {
				// // 1. Handle User Input
				// // TODO: move this to a controller class
				// //Handle events on queue
				// while( SDL_PollEvent( &e ) != 0 )
				// {
				// 	//User requests quit
				// 	if( e.type == SDL_QUIT )
				// 	{
				// 		quit = true;
				// 	}

				// 	//Handle input for the ball
				// 	ball.handleEvent( e ); //removed events; ball is on  its own now!
				// 	paddleLeft.handleEvent(e); 
				// 	paddleRight.handleEvent(e); 
				// }

				// // 2. Update game state	
				// // DONE: move this to a Game.Update class
				// //Move the ball
				// ball.move();
				// paddleLeft.move();
				// paddleRight.move();
				// // Check collisions
				// // Update scores
				// // Manage game events: e.g. increase difficulty level/ball speed.
				// // ...


				// // DONE: moved this to  Renderer.Render() class
				// //Clear screen
				// SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				// SDL_RenderClear( gRenderer );
				// //Render objects
				// ball.render(gRenderer);
				// paddleLeft.render(gRenderer);
				// paddleRight.render(gRenderer);
				// //TODO: render scores.
				// //Update screen
				// SDL_RenderPresent( gRenderer );
	// 		}
	// 	}
	// }

	// //Free resources and close SDL
	// close();

	// return 0;
//}

int main(){
	constexpr std::size_t kScreenWidth{640}; //size_t: is a template for unsigned value; using size_t we let the compiler optimize the type (int, long, etc.).
	constexpr std::size_t kScreenHeight{480};

	Renderer renderer(kScreenWidth, kScreenHeight);
	Controller controller;
	Game game(kScreenWidth, kScreenHeight);
	game.Run(controller, renderer); //TODO: expand, add kMsPerFrame;
	std::cout << "Exiting Pong! " << "\n";
	Score score = game.GetScore();
	std::cout << "Score: " << score.playerLeft << " : " << score.playerRight  << "\n";
	return 0;
}