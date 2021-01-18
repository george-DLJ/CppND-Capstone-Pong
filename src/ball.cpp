#include <SDL.h>
#include "ball.h"

#include <iostream> //DEBUG

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
 * this function renders the ball. 
 * NOTE: currently is represented by a a square,
 *       but it could be of other type, e.g. Texture, image, etc.
 */ 
void Ball::render(SDL_Renderer* sdl_renderer)
{
    //Set color to render the  ball:
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    
    // Positon of the top left corner of the ball.
    render_block_.x = pos_x_ ;
    render_block_.y = pos_y_ ;
    SDL_RenderFillRect(sdl_renderer, &render_block_);
}

const SDL_Rect& Ball::getCollider() const
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
            vel_y_ *= -1;
            int oldPosY = pos_y_; //DEBUG
            pos_y_ = field_height * (pos_y_ / (field_height-kBallDiameter)) - (pos_y_ % (field_height-kBallDiameter));
            //std::cout << "FieldVerticalRebound: OldPosY: " << oldPosY << " PosY: " << pos_y_ << "; f-height: " << field_height << "; quotient(/)[0,1]: " << pos_y_ / field_height << "remainder(%)[0-fh): "<< pos_y_%field_height <<"\n";
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
            vel_y_ *= -1;
            int oldPosY = pos_y_;
            pos_y_ = field_height * (pos_y_ / field_height) - (pos_y_ % field_height);
            std::cout << "FieldVerticalRebound: OldPosY: " << oldPosY << " PosY: " << pos_y_ << "; f-height: " << field_height << "; quotient(/)[0,1]: " << pos_y_/field_height << "remainder(%)[0-fh): "<< pos_y_%field_height <<"\n"; 
            }
            break;
        case BounceDirection::kHorizontal:
            {
            vel_x_ *= -1;
            int oldPosX = pos_x_; //DEBUG
            int quotient = pos_x_/field_width; //DEBUG
            int remainder = pos_x_ % field_width;
            pos_x_ = field_width * (pos_x_/field_width) - (pos_x_ % field_width);
            //std::cout << "FieldHorizontalRebound: OldPosX: " << oldPosX << " PosX: " << pos_x_ << "; f-width: " << field_width << "; quotient(/)[0,1]: " << quotient << "remainder(%)[0-fh): "<< remainder <<"\n"; 
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
            vel_y_ *= -1;
            int y_ball {pos_y_};
            int y_rebounced = wall_coord + (wall_coord - y_ball);
            pos_y_ = wall_coord + (wall_coord - pos_y_); 
            //std::cout << "WallRebound: TODO: " <<"\n"; 
            }
            break;
        case BounceDirection::kHorizontal:
            {
            vel_x_ *= -1;
            int x_ball {pos_x_};
            int x_rebounced = wall_coord + (wall_coord - x_ball);
            pos_x_ =  wall_coord + (wall_coord - pos_x_);
            //std::cout << "WallRebound: TODO: " <<"\n"; 
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
void Ball::changeSpeed(int speed)
{
    if (speed > 0 )
    {
        vel_x_ = vel_x_ < 0 ?  -speed : speed;
        vel_y_ = vel_y_ < 0 ?  -speed : speed;
    }
    
}

/**
 * Service ball: after a goal there is a new ball service.
 * Ball keep its current vel values
 * just the start position is reset (eventually to the middle of the field).
 * 
 */
void Ball::ServeBall(const int service_pos_x, const int service_pos_y)
{
    pos_x_ = service_pos_x;
    pos_y_ = service_pos_y;

    //TODO:
    //1.  reset speed level to 1
    //2. (remember to reset paddles angles)
}
