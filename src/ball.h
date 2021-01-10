#ifndef BALL_H_
#define BALL_H_

#include <SDL.h>

class Ball
{
    public:
    //dimensions
    static const int BALL_WIDTH = 20;
    static const int BALL_HEIGHT = 20;

    //Max axis velocity
    static const int BALL_VEL = 1; //

    //Constructor
    Ball(const int screenWidth, const int screenHeight);

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

#endif /* BALL_H_ */