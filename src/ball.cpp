#include <SDL.h>

#include "ball.h"



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

void Ball::move()
{
    //Move ball on x axis (left - right):
    mPosX += mVelX;

    // If it is outside boundaries move back
    if((mPosX < 0) || (mPosX + BALL_DIAMETER > mScreenWidth ))
    {
        //1. Move back to screen
        mPosX -= mVelX;
        //2. Reverse speed on that axis:
        mVelX *= -1;

    }

    //Move ball on x axis (up or down):
    mPosY += mVelY;

    // If it is outside boundaries move back
    if((mPosY < 0) || (mPosY + BALL_DIAMETER > mScreenHeight ))
    {
        //Move back
        mPosY -= mVelY;
        //2. Reverse speed on that axis:
        mVelY *= -1;
    }

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
        case CollisionSide::right:
        case CollisionSide::left:
            mVelX *= -1;
            break; 
        case CollisionSide::top:
        case CollisionSide::bottom:
            mVelY *= -1;
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



