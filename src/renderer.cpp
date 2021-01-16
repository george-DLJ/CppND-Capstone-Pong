#include "renderer.h"
#include <stdexcept>
#include <iostream>
#include <string>

/**
 * NOTE: constructor requires initialize following resourcres: 
 *       1 - (initialize) SDL
 *       2 - window
 *       3 - renderer
 * 
 * NOTE: implementing RAII: if constructor returns, the object is considered valid.
 *       goal: guarantee an object is never-empty. 
 *       Also: a thrown exception means there isn't any object 
 * TODO: implement move semantics and rule of 5. 
 * TODO: Expand to initialize textures (or create a textures class)
 * */
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    :screen_width_(screen_width),
     screen_height_(screen_height)
    {
        // 1. Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            std::cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << "\n";
            //throw SDL_error(); Does not work!
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
        }

        // 2. Create Window
 		sdl_window_ = SDL_CreateWindow( "Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width_, screen_height_, SDL_WINDOW_SHOWN );
		if( !sdl_window_ )
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			//throw Sdl_error();
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
		}

        // 3. Creater vsynced renderer for window 
		sdl_renderer_ = SDL_CreateRenderer( sdl_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( !sdl_renderer_ )
		{
			std::cout <<  "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			//throw Sdl_error();
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
		}
        
        //4. Initialize renderer color
		SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF );

    }
    
    //TODO: implement rule of 5!
    Renderer::~Renderer() {
        //Destroy window	
        SDL_DestroyRenderer( sdl_renderer_ );
        sdl_renderer_ = nullptr; //TODO:remove when using smart_pointers;
        SDL_DestroyWindow( sdl_window_ );
        sdl_window_ = nullptr; //TODO:remove when using smart_pointers;
        

	    //Quit SDL subsystems
	    //IMG_Quit(); //requires SDL_Image extension
	    SDL_Quit();
    }

/** 
 * TODO: implement generics or interface for multiple componenten?
 * 
 */ 
    void Renderer::Render(Ball &ball,  Paddle &paddleLeft,  Paddle &paddleRight)
    {
        // 1. Clear screen
		SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( sdl_renderer_ );
        // 2. Render objects
        ball.render(sdl_renderer_);
		paddleLeft.render(sdl_renderer_);
		paddleRight.render(sdl_renderer_);
        //TODO: 2.2 render scores.

        // 3. Update screen
		SDL_RenderPresent( sdl_renderer_ );
    }

    //TODO: Optional update window title
    //void Renderer::UpdateWindowTitle(){}

