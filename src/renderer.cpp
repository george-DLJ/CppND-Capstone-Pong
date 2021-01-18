#include "renderer.h"
#include <stdexcept>
#include <iostream>
#include <string>

/**
 * NOTE: the renderer constructor requires initialize following resourcres: 
 *       1 - (initialize) SDL
 *       2 - window
 *       3 - renderer
 * 
 * NOTE: implementing RAII: if constructor returns, the object is considered valid.
 *       goal: guarantee an object is never-empty. 
 *       Also: a thrown exception means there isn't any object 
 */
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    :screen_width_(screen_width),
     screen_height_(screen_height)
    {
        // 1. Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            std::cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << "\n";
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
        }

        // 2. Create Window
 		sdl_window_ = SDL_CreateWindow( "Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width_, screen_height_, SDL_WINDOW_SHOWN );
		if( !sdl_window_ )
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
		}

        // 3. Creater vsynced renderer for window 
		sdl_renderer_ = SDL_CreateRenderer( sdl_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( !sdl_renderer_ )
		{
			std::cout <<  "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            throw std::runtime_error( "SDL could not initialize! SDL Error: ");
		}
        
        //4. Initialize renderer color
		SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    
    Renderer::~Renderer() {
        //Destroy window	
        SDL_DestroyRenderer( sdl_renderer_ );
        sdl_renderer_ = nullptr; 
        SDL_DestroyWindow( sdl_window_ );
        sdl_window_ = nullptr; 
        
	    //Quit SDL subsystems
	    SDL_Quit();
    }

    /**
     * Using an interface of IRenderable elements, allows us to have 
     * a vector of references to those objects, no matter if they are ball, 
     * or Paddle. 
     * Now this class is decoupled from the game objects.
     * PROBLEM: I couldn't make it work using a vector of smart_pointers.
     */
    void Renderer::Render(std::vector<IRenderable*> elements)
    {
        // 1. Clear screen
		SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( sdl_renderer_ );
        // 2. Render objects
        for(auto e : elements){
            e->Render(sdl_renderer_);
        }
        // 3. Update screen
		SDL_RenderPresent( sdl_renderer_ );
    }

    /**
     * update window title with score and framerate information.
     */ 
    void Renderer::UpdateWindowTitle(int score_left, int score_right, int fps){
        std::string title{"Score: " + std::to_string(score_left) + " : " + std::to_string(score_right) + " FPS: " + std::to_string(fps)};
        SDL_SetWindowTitle(sdl_window_, title.c_str());
    }
