#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL.h>
class Paddle
{
    public:
    //dimensions
    static const int PADDLE_WIDTH = 20;
    static const int PADDLE_HEIGHT = 60;

    //Max axis velocity
    static const int PADDLE_VEL = 1; //

    //Constructor
    Paddle(const int screenWidth, const int screenHeight, const int xPos);

    //Take key presses and adjust velocity
    void handleEvent( SDL_Event& e );

    //Move Ball
    void move();

    //Show ball on screen:
    void render(SDL_Renderer* sdl_renderer);

    private:
    //The X and Y offsets of the ball
    int mPosX, mPosY;

    //The vel of the ball
    int mVelX, mVelY;

    // Screen width and height
    int mScreenWidth, mScreenHeight;

};

#endif /* PADDLE_H */