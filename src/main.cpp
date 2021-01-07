#include <iostream>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 *  lazyfoo.net tutorial
 *  Create a window and after 2 seconds close it
 *  NOTE: While in Delay keyboard input cannot be accepted.
 * 
 * */
int main() {
    std::cout << "Hello Pong!" << "\n";
    
    // The window we will be rendering to
    SDL_Window* window = NULL;
    
    // Surface contained by the window:
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDAL could not initialize! SDL_Error:" << SDL_GetError << "\n";
    }
    else
    {
        // Create Womdpw
        window = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( window == NULL)
        {
             std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
        
        //Destroy window
        SDL_DestroyWindow( window );

        //Quit SDL subsystems
        SDL_Quit();
    } 
    
    
    return 0;
}