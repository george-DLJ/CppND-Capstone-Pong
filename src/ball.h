#ifndef BALL_H_
#define BALL_H_

#include <SDL.h>
#include "IRenderable.h"

class Ball : public IRenderable
{
    public:
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
        static const int kBallDiameter = 20;

        //Max axis velocity
        static const int kBAllVel = 3;

        //Constructor
        Ball(const int start_pos_x, const int start_pos_y);

        void Move();

        void Render(SDL_Renderer* sdl_renderer) override;

        // returns the collision box
        const SDL_Rect& GetCollider() const;

        // Events that affect the ball
        void Rebound(BounceDirection direction);
        void FieldVerticalRebound(const int field_height);
        void FieldRebound(const BounceDirection direction, const int field_width, const int field_height);//const Game::Field fieldSize)
        void WallRebound(const BounceDirection direction, const int wall_coord);

        void changeSpeed(int speed);

        void ServeBall(const int service_pos_x, const int service_pos_y);

    private:
        //The X and Y offsets of the ball
        int pos_x_, pos_y_;

        //The velocity of the ball
        int vel_x_, vel_y_;

        // Ball's collison box
        SDL_Rect collider_; //NOTE: it could have different size than render block

        // Ball's render block
        SDL_Rect render_block_; //NOTE: currently a block, but it could be another type e.g. a texture or image. 
};

#endif /* BALL_H_ */