#ifndef BALL_H_
#define BALL_H_

#include <SDL.h>

class Ball
{
    public:
       enum class CollisionSide{
            left,
            right,
            top,
            bottom,
        };
        enum class SpeedLevel{
            level1 = 1,
            level2 = 2,
            level3 = 3,
        };
        //dimensions
        static const int BALL_DIAMETER = 20;

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

        // return collision box
        const SDL_Rect& getCollider() const;

        // Events that affect the ball
        void Rebound(CollisionSide side);

        void changeSpeed(int speedModule);

        void changeDirections(bool axisX, bool axisY);

    private:
        //The X and Y offsets of the ball
        int mPosX, mPosY;

        //The vel of the ball
        int mVelX, mVelY;

        // Screen width and height
        int mScreenWidth, mScreenHeight;

        // Ball's collison box
        SDL_Rect collider_;

};

#endif /* BALL_H_ */