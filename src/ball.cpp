#include <SDL.h>
#include "ball.h"

Ball::Ball(const int start_pos_x, const int start_pos_y):pos_x_(start_pos_x),pos_y_(start_pos_y), vel_x_(kBAllVel), vel_y_(kBAllVel)
{
    // initialize collider:
    collider_.w = kBallDiameter;
    collider_.h = kBallDiameter;
    collider_.x = pos_x_;
    collider_.y = pos_y_;

    // initialize ball render_element size
    render_block_.w = kBallDiameter;
    render_block_.h = kBallDiameter;
}

void Ball::Move()
{
    pos_x_ += vel_x_;
    pos_y_ += vel_y_;

    // update collider pos
    collider_.x = pos_x_;
    collider_.y = pos_y_;
}

/**
 * This function renders the ball. 
 * NOTE: currently is represented by a a square,
 *       but it could be of other type, e.g. Texture, image, etc.
 */ 
void Ball::Render(SDL_Renderer* sdl_renderer)
{
    //Set color to render the  ball (Dark Yellow):
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    
    // Positon of the top left corner of the ball.
    render_block_.x = pos_x_ ;
    render_block_.y = pos_y_ ;
    SDL_RenderFillRect(sdl_renderer, &render_block_);
}

const SDL_Rect& Ball::GetCollider() const
{
    return collider_;
}

void Ball::Rebound(BounceDirection direction)
{
    switch(direction)
    {
        case BounceDirection::kHorizontal:
            pos_x_ -= vel_x_;   //move back
            vel_x_ *= -1;       //reverse velocity component direction
            break; 
        case BounceDirection::kVertical:
            pos_y_ -= vel_y_;   //Move back
            vel_y_ *= -1;       //reverse velocity component direction
            break; 
    }
}

/**
 * Assuming vertical and horizontal walls, starting at 0,0, in case there was a collision, 
 * the ball rebounds. That means:
 *  1. the velocity axis perpendicular to the wall is reversed
 *  2. the position component perpendicular to the wall must be reflected. 
*/
void Ball::FieldVerticalRebound(const int field_height)
{
            pos_y_ -= vel_y_; //Move back
            vel_y_ *= -1; // Reverse vel direction of y component.
}

/**
 * Serves a new ball: after a goal there is a new ball serve.
 * Ball keep its current direction and is just moved to the center of the field.
 */
void Ball::ServeBall(const int service_pos_x, const int service_pos_y)
{
    pos_x_ = service_pos_x;
    pos_y_ = service_pos_y;
}
