#ifndef DOT_H_
#define DOT_H_

#include <SDL.h>

class Dot
{
    public:
    //dimensions
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Max axis velocity
    static const int DOT_VEL = 10;

    //Constructor
    Dot(const int screenWidth, const int screenHeight);

    //Take key presses and adjust velocity
    void handleEvent( SDL_Event& e );

    //Move Dot
    void move();

    //Show dot on screen:
    void render(SDL_Renderer* sdl_renderer);

    private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The vel of the dot
    int mVelX, mVelY;

    // Screen width and height
    int mScreenWidth, mScreenHeight;

};

#endif /* DOT_H_ */