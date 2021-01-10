#include <SDL.h>

#include "paddle.h"

/**
 * The paddle has a fixed xPosition at one of the ends of the screen.
 * PRE: the xPos of the paddle must be within the screen width.
 * */
Paddle::Paddle(const int screenWidth, const int screenHeight, const int xPos):mScreenWidth(screenWidth),mScreenHeight(screenHeight),mPosX(xPos),mPosY(0), mVelX(0), mVelY(0)
{
    //TODO: check that xPos is within screenWidth; consider paddel width!
}

/**
 * TODO: implement a custom eventqeueue to handle moveEvents 
 *       independent from input device selected.
 *       in order to use different input device without change BL.
 * 
 * TODO: move this method to controls class. This method should be on 
 *       the Ball class.
 * 
 * Paddle only reacts to Key up/ key down events
 * TODO: add to constructor to which keys should reacht the paddle, e.g. in 
 * dual player game.
 */ 
void Paddle::handleEvent( SDL_Event& e)
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym)
        {
            case SDLK_w: 
                mVelY -= PADDLE_VEL;
            break;
            case SDLK_s: 
                mVelY += PADDLE_VEL;
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
            case SDLK_w: mVelY += PADDLE_VEL; break;
            case SDLK_s: mVelY -= PADDLE_VEL; break;
        }
    } 
}

/**
 * NOTE: First approach Paddle has its 0,0 point on top-left corner of the square.
 * NOTE: Paddle has no movement on Y axis.
 */
void Paddle::move()
{
    //Move Paddle on Y axis (up or down):
    mPosY += mVelY;

    // If it is outside boundaries move back
    if((mPosY < 0) || (mPosY + PADDLE_HEIGHT > mScreenHeight ))
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
void Paddle::render(SDL_Renderer* sdl_renderer)
{
    //Show the ball

    SDL_Rect block;
    block.w = PADDLE_WIDTH;
    block.h = PADDLE_HEIGHT;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); //Color: Red, opaque
    
    block.x = mPosX ;
    block.y = mPosY ;
    SDL_RenderFillRect(sdl_renderer, &block);
}