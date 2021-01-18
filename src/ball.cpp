#include <SDL.h>

#include "ball.h"

#include <iostream> //DEBUG


/**
 * 
 * */
Ball::Ball(const int screenWidth, const int screenHeight):mScreenWidth(screenWidth),mScreenHeight(screenHeight),mPosX(screenWidth/2),mPosY(0), mVelX(BALL_VEL), mVelY(BALL_VEL)
{
    // initialize collider:
    collider_.w = BALL_DIAMETER;
    collider_.h = BALL_DIAMETER;
    collider_.x = mPosX;
    collider_.y = mPosY;
}


/**
 * TODO: implement a custom eventqeueue to handle moveEvents 
 *       independent from input device selected.
 *       in order to use different input device without change BL.
 * 
 * TODO: move this method to controls class. This method should be on 
 *       the Ball class.
 */ 

void Ball::Move()
{
    //Move ball on x axis (left - right):
    mPosX += mVelX;

    //Move ball on x axis (up or down):
    mPosY += mVelY;

    // update collider pos
    collider_.x = mPosX;
    collider_.y = mPosY;
}

/**
 * TODO: consider move this function to render class or 
 *       separate physics (without SDL) from visualization(with SDL) in two 
 *       classes.
 * 
 * */
void Ball::render(SDL_Renderer* sdl_renderer)
{
    //Show the ball

    SDL_Rect block;
    block.w = BALL_DIAMETER;
    block.h = BALL_DIAMETER;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    
    // Positon of the top left corner of the ball.
    block.x = mPosX ;
    block.y = mPosY ;
    SDL_RenderFillRect(sdl_renderer, &block);
}

const SDL_Rect& Ball::getCollider() const
{
    return collider_;
}

/**
 *  NOTE: consider move this logic to the game controller.
 */
void Ball::Rebound(CollisionSide side)
{
    switch(side)
    {
        case CollisionSide::left_right:
            mVelX *= -1;
            break; 
        case CollisionSide::top_bottom:
            mVelY *= -1;
            break; 
    }
}

/**
 * Assuming vertical and horizontal walls, starting at 0,0, in case there was a collision, 
 * the ball rebounds. That means:
 *  1. the velocity axis perpendicular to the wall is reversed
 *  2. the position component perpendicular to the wall must be reflected. 
 * NOTE: consider move this logic to the game controller.
 *  
 */
void Ball::FieldVerticalRebound(const int field_height)
{
            mVelY *= -1;
            int oldPosY = mPosY; //DEBUG
            mPosY = field_height * (mPosY / (field_height-BALL_DIAMETER)) - (mPosY % (field_height-BALL_DIAMETER));
            //std::cout << "FieldVerticalRebound: OldPosY: " << oldPosY << " PosY: " << mPosY << "; f-height: " << field_height << "; quotient(/)[0,1]: " << mPosY / field_height << "remainder(%)[0-fh): "<< mPosY%field_height <<"\n";
}


/**
 * ReboundCorrection:
 * using reactangular boundary
 * could work without field input if field boundaries are given at construction.
 */
void Ball::FieldRebound(const Ball::BounceDirection direction, const int field_width, const int field_height)
{
    switch(direction)
    {
        case BounceDirection::kVertical:
            {
            mVelY *= -1;
            int oldPosY = mPosY;
            mPosY = field_height * (mPosY / field_height) - (mPosY % field_height);
            std::cout << "FieldVerticalRebound: OldPosY: " << oldPosY << " PosY: " << mPosY << "; f-height: " << field_height << "; quotient(/)[0,1]: " << mPosY/field_height << "remainder(%)[0-fh): "<< mPosY%field_height <<"\n"; 
            }
            break;
        case BounceDirection::kHorizontal:
            {
            mVelX *= -1;
            int oldPosX = mPosX; //DEBUG
            int quotient = mPosX/field_width; //DEBUG
            int remainder = mPosX % field_width;
            mPosX = field_width * (mPosX/field_width) - (mPosX % field_width);
            std::cout << "FieldHorizontalRebound: OldPosX: " << oldPosX << " PosX: " << mPosX << "; f-width: " << field_width << "; quotient(/)[0,1]: " << quotient << "remainder(%)[0-fh): "<< remainder <<"\n"; 
            }
            break;
    }
}


/**
 * Rebound against wall with known direction and wall coordinate
 * xreb = xwall + (xwall - xball); corrects automatically side of rebound
 * requires know where is the wall.
 */
void Ball::WallRebound(const Ball::BounceDirection dir, const int wall_coord)
{
    switch(dir)
    {
        case BounceDirection::kVertical:
            {
            mVelY *= -1;
            int y_ball {mPosY};
            int y_rebounced = wall_coord + (wall_coord - y_ball);
            mPosY = wall_coord + (wall_coord - mPosY); 
            std::cout << "WallRebound: TODO: " <<"\n"; 
            }
            break;
        case BounceDirection::kHorizontal:
            {
            mVelX *= -1;
            int x_ball {mPosX};
            int x_rebounced = wall_coord + (wall_coord - x_ball);
            mPosX =  wall_coord + (wall_coord - mPosX);
            std::cout << "WallRebound: TODO: " <<"\n"; 
            }
            break;

    }
}

/**
 * Sets the ball speed modulus. 
 * NOTICE: 1st approach: both directions speeds are always equal.
 *         this implies the ball always moves in 45 deg angles. 
 * Simplification: get ball directions and replace each axis module with the new given.
 * Real calculation will require change speeds to floats.
 * Then use vector normalization.
 */ 
void Ball::changeSpeed(int speedModule)
{
    if (speedModule > 0 )
    {
        mVelX = mVelX < 0 ?  -speedModule : speedModule;
        mVelY = mVelY < 0 ?  -speedModule : speedModule;
    }
    
}

/**
 * reverses one or both directions of the ball:
 * Case 1- in case of a side rebound the ball changes the x axis only
 * case 2- in case the ball touches top or bottom side of paddle, 
 * then an unrealistic rebouond changing both axis is necessary.
 */
void Ball::changeDirections(bool axisX, bool axisY)
{
    if(axisX)
    {
        mVelX *= -1;
    }
    if(axisY)
    {
        mVelY *= -1;
    }
}

/**
 * Service ball: after a goal there is a new ball service.
 * Ball keep its current vel values
 * just the start position is reset (eventually to the middle of the field).
 * 
 */
void Ball::Service(const int service_pos_x, const int service_pos_y)
{
    mPosX = service_pos_x;
    mPosY = service_pos_y;

    //TODO:
    //1.  reset speed level to 1
    //2. (remember to reset paddles angles)
}
