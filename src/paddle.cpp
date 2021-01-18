#include <SDL.h>

#include "paddle.h"

/**
 * The paddle has a fixed xPosition and it can move only up and down
 * */
Paddle::Paddle(const int min_y_pos, const int max_y_pos, const int paddle_center_x):
    min_y_pos_(min_y_pos),
    max_y_pos_(max_y_pos), 
    x_pos_(convert_to_paddle_rect_x(paddle_center_x, kPaddleWidth)),
    y_pos_(min_y_pos), 
    vel_y_(0)
{
    // initialize collider:
    collider_.w = kPaddleWidth;
    collider_.h = kPaddleHeight;
    collider_.x = x_pos_;
    collider_.y = y_pos_;   
}

void Paddle::StartMovement(Paddle::Direction direction)
{
    switch( direction )
    {
        case Direction::kUp: 
            vel_y_ -= kPaddleVel;
            break;
        case Direction::kDown: 
            vel_y_ += kPaddleVel;
            break;
    }
}

void Paddle::StopMovement(Paddle::Direction direction)
{
    switch( direction )
    {
        case Direction::kUp: 
        case Direction::kDown: 
            vel_y_ = 0;
            break;
    }
}

void Paddle::Move()
{
    //Move Paddle on Y axis (up or down):
    y_pos_ += vel_y_;

    // If it is outside boundaries move back
    if((y_pos_ < 0) || (y_pos_ + kPaddleHeight > max_y_pos_ ))
    {
        //Move back
        y_pos_ -= vel_y_;
    }
    
    // update collider
    // NOTE: collider x.pos is fixed on paddle.
    collider_.y = y_pos_;
}

void Paddle::Render(SDL_Renderer* sdl_renderer)
{
    //Show the paddle
    SDL_Rect block;
    block.w = kPaddleWidth;
    block.h = kPaddleHeight;

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); //Color: Red, opaque
    
    block.x = x_pos_ ;
    block.y = y_pos_ ;
    SDL_RenderFillRect(sdl_renderer, &block);
}

/**
 * NOTE: I need to expose the instance collider Rectangle, but not allow callers to 
 * modify it. 
 * By making the function const (getCollider const) it is avoided changes on members data.
 * 
 * I don't want either copy it each time a collision needs to be calculated.
 * see: https://stackoverflow.com/a/8005559
 *      https://stackoverflow.com/a/751783
 */
const SDL_Rect& Paddle::GetCollider() const
{
    return collider_;
}