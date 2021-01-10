#include <SDL.h>

#include "ball.h"

/**
 * 
 * */
Ball::Ball(const int screenWidth, const int screenHeight):mScreenWidth(screenWidth),mScreenHeight(screenHeight),mPosX(0),mPosY(0), mVelX(0), mVelY(0)
{
    //Initialize pos offsets
    //mPosX = 0; //already initialized in list
    //mPosY = 0; //already initialized in list

    //init vel
    //mVelX = 0; //already initialized in list
    //mVelY = 0; //already initialized in list
}

/**
 * TODO: implement a custom eventqeueue to handle moveEvents 
 *       independent from input device selected.
 *       in order to use different input device without change BL.
 * 
 * TODO: move this method to controls class. This method should be on 
 *       the Ball class.
 */ 
void Ball::handleEvent( SDL_Event& e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym)
        {
            case SDLK_UP: 
                mVelY -= BALL_VEL;
            break;
            case SDLK_DOWN: 
                mVelY += BALL_VEL;
            break;
            case SDLK_LEFT: 
                mVelX -= BALL_VEL;
            break;
            case SDLK_RIGHT: 
                mVelX += BALL_VEL;
            break;

        }
    }
    //If a key was released: 
    // When we release a key, we have to undo the velocity change when first pressed it. 
    // e.g. when we pressed right key, we added to the x velocity; so now when we release 
    // the right key here, we subtract from the x velocity to return it to 0.
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += BALL_VEL; break;
            case SDLK_DOWN: mVelY -= BALL_VEL; break;
            case SDLK_LEFT: mVelX += BALL_VEL; break;
            case SDLK_RIGHT: mVelX -= BALL_VEL; break;
        }
    } 
}

void Ball::move()
{
    //Move ball on x axis (left - right):
    mPosX += mVelX;

    // If it is outside boundaries move back
    if((mPosX < 0) || (mPosX + BALL_WIDTH > mScreenWidth ))
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move ball on x axis (up or down):
    mPosY += mVelY;

    // If it is outside boundaries move back
    if((mPosY < 0) || (mPosY + BALL_HEIGHT > mScreenHeight ))
    {
        //Move back
        mPosY -= mVelY;
    }
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
    block.w = BALL_WIDTH;
    block.h = BALL_HEIGHT;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    
    block.x = mPosX ;
    block.y = mPosY ;
    SDL_RenderFillRect(sdl_renderer, &block);
}

