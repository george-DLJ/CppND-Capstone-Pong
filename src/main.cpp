#include <iostream>
#include <SDL.h>
//#include <SDL2/SDL_image.h> //Required to open png images!

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Lesson 4 handle key presses:
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

/**
 *  lazyfoo.net tutorial 
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

//Loads individual image (L04)
SDL_Surface *loadSurface(std::string path);

//private:
//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//The images that correspond to a keypress (L04)
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface *gCurrentSurface = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDAL could not initialize! SDL_Error:" << SDL_GetError << "\n";
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

/** 
 * L1 load the helloworld image
 * L3 modified to load pngs 
 * L4 modified to load the images
 * 
 * */
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface e.g splash image
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press_key.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/key_press_up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/key_press_down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/key_press_left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/key_press_right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

void close()
{
    
    //Deallocate surfaces
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }
   
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

/**
 * L04: load different images depending on user input
 * 
 * */
SDL_Surface *loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str()); // BMP are supported on SDL
    // Alternative to load PNGs and other formats (Require SDL_image.h) and in this workspace install the library each time; also requires make changes on CMakeLists.txt.
    //SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "SDL Error: " << SDL_GetError() << "\n";
    }
    return loadedSurface;
}

int main()
{
    // Initialize SDL
    if (!init())
    {
        std::cout << "Failed to initialize"
                  << "\n";
    }
    else
    {
        // setup background color:
        SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xA5, 0x00));

        // Load Media
        if (!loadMedia())
        {
            std::cout << "Failed to load media"
                      << "\n";
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            // set default current surface:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            //While app is running
            while (!quit)
            {
                // 1. Handle Events
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit:
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //User presses a key:
                    else if (e.type = SDL_KEYDOWN)
                    {
                        //select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;
                        case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                        default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }

                // 3. Render
                //Apply the image
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);

                // 4. Simulate some work (e.g. calculations)
                //SDL_Delay( 100 );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}