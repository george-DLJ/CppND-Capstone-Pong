#ifndef BALL_H_
#define BALL_H_

#include <SDL.h>
#include "IRenderable.h"

class Ball : public IRenderable
{
    public:
       enum class CollisionSide{
            left_right,
            top_bottom,
        };
        // may replace collisionSide!
        enum class BounceDirection{
            kVertical,
            kHorizontal,
        };
        enum class SpeedLevel{
            level1 = 1,
            level2 = 2,
            level3 = 3,
        };
        //dimensions
        static const int BALL_DIAMETER = 20;

        //Max axis velocity
        static const int BALL_VEL = 3; //

        //Constructor
        Ball(const int screenWidth, const int screenHeight);

        //Move Ball
        void Move();

        //Show ball on screen:
        void render(SDL_Renderer* sdl_renderer);

        // return collision box
        const SDL_Rect& getCollider() const;

        // Events that affect the ball
        void Rebound(CollisionSide side);
        void FieldVerticalRebound(const int field_height);
        void FieldRebound(const BounceDirection direction, const int field_width, const int field_height);//const Game::Field fieldSize)
        void WallRebound(const BounceDirection direction, const int wall_coord);

        void changeSpeed(int speedModule);

        void changeDirections(bool axisX, bool axisY);

        void Service(const int service_pos_x, const int service_pos_y);

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