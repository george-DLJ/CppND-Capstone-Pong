#include "controller.h"
#include "SDL.h"
#include "paddle.h"

/**
 *  * TODO: implement a custom eventqeueue to handle moveEvents 
 *       independent from input device selected.
 *       in order to use different input device without change BL.
 */ 
void Controller::HandleInput(bool &running, 
							 Paddle &paddle_left, 
							 Paddle &paddle_right) const {
	//Event handler
	SDL_Event e;

	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			running = false;
		}
		// Check paddles keys:
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			
			//Adjust the velocity
			switch( e.key.keysym.sym)
			{
				// paddle_left keys:
				case SDLK_w: 
					paddle_left.startMovement(Paddle::Direction::kUp);
					break;
				case SDLK_s: 
					paddle_left.startMovement(Paddle::Direction::kDown);
					break;

				// paddle_right keys:
				case SDLK_UP:
          			paddle_right.startMovement(Paddle::Direction::kUp);
          			break;
		        case SDLK_DOWN:
        			paddle_right.startMovement(Paddle::Direction::kDown);
          			break;
			}
		}
		//If a key was released: 
		// When we release a key, we have to undo the velocity change when first pressed it. 
		// e.g. when we pressed right key, we added to the x velocity; so now when we release 
		// the right key here, we subtract from the x velocity to return it to 0.
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
		{
			//Adjust the velocity
			switch( e.key.keysym.sym )
			{
				// paddle_right keys:
				case SDLK_w:
          			paddle_left.stopMovement(Paddle::Direction::kUp);
          			break;
		        case SDLK_s:
        			paddle_left.stopMovement(Paddle::Direction::kDown);
          			break;

				// paddle_right keys:
				case SDLK_UP:
          			paddle_right.stopMovement(Paddle::Direction::kUp);
          			break;
		        case SDLK_DOWN:
        			paddle_right.stopMovement(Paddle::Direction::kDown);
          			break;
			}
		} 

	}
}

// REFACTOR:
// void Controller::HandleInput(bool &running, vector<IControllable> controllableElements)

