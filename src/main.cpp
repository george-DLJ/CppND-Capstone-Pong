#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h> //Required to open png images!

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 *  lazyfoo.net tutorial - Lesosn 2: show an image on the window.
 *  add some modularity by creating following methiods: 
 *  - bool init() --> initializes the SDL window
 *  - bool loadMedia() --> loads a picture
 *  - void close() --> frees media an closes
 *  NOTE: While in Delay keyboard input cannot be accepted.
 *  NOTE: to use PNG images, the SDL_image library must be installed:
 *       open a terminal and write:
 *          sudo apt-get install libsdl2-image-dev
 *          
 *        see: https://gamedev.stackexchange.com/a/135894
 * */
//
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//private:
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDAL could not initialize! SDL_Error:" << SDL_GetError << "\n";
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    //gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
    gHelloWorld = IMG_Load( "hello_world.png" ); //TODO: configure Library on CMAKE
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main() {
    std::cout << "Hello Pong! - Lazyfoo lesson 2" << "\n";
    

    // Initialize SDL
    if(!init() )
    {
        std::cout << "Failed to initialize" << "\n";
    }
    else
    {
        // setup background color:
        SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xA5, 0x00 ) );
        
        // Load Media:
        if(!loadMedia() ) {
            std::cout << "Failed to load media! ... filling with white surface instead..." << "\n";
            return 0;
        }

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While app is running
        while( !quit )
        {
            // 1. Handle Events
            while ( SDL_PollEvent(&e) != 0 )
            {
                //User request quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }
            //User requiest quit
            if(e.type == SDL_QUIT )
            {
                quit = true;
            }    
            
            // 2. Simulate some work (e.g. calculations)
            SDL_Delay( 100 );

            // 3. Render
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
         }
     }
    return 0;
}