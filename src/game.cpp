#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(int field_width, int field_height)
    : field_(field_width, field_height),
      ball_(field_width/2, 0), //start position for the ball: middle top of screen
      paddle_left_(0, field_height, kPaddleDistanceFromSide),
      paddle_right_(0, field_height, field_width - kPaddleDistanceFromSide),
      score_{0,0},
      volleys_(0){      
}

void Game::Run(const Controller &controller, Renderer &renderer) // First approach without frame_calc 
{
  // variables for game timing control
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;

  // Variables for window title updates (e.g. scores and framreate)
  Uint32 title_timestamp = SDL_GetTicks();
  int frame_count = 0;
  
  std::vector<IRenderable*> renderables;
  renderables.push_back(&ball_);
  renderables.push_back(&paddle_left_);
  renderables.push_back(&paddle_right_);

  bool running = true;

    // Game loop:
    while (running)
    {
    frame_start = SDL_GetTicks();

    // 1. Handle User Input:
    controller.HandleInput(running, paddle_left_, paddle_right_);
    // 2. Update:
    Update();
    // 3. Render:
    renderer.Render(renderables); 

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score_.playerLeft, score_.playerRight, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < kTargetFrameDuration) {
       SDL_Delay(kTargetFrameDuration - frame_duration);
    }
  }
}

Score Game::GetScore() const { return score_; }

/**
 * Updates the game dynamics as follows:
 * 1. Update game elements moves: ball and both paddles
 * 2. Check if there where collisions between ball and game elements.
 * 3. (Optionally) the difficulty could be increasesd.
 */  
void Game::Update() {
  
  ball_.Move();  
  paddle_left_.Move();
  paddle_right_.Move();  
  
  CheckCollision(ball_, field_);
  CheckCollision(ball_, paddle_left_);
  CheckCollision(ball_, paddle_right_);
}

void Game::CheckCollision(Ball &ball, const Field &field)
{
  const SDL_Rect &ball_collider = ball.GetCollider();
  // Goal on Left player field
  if(ball_collider.x < 0) 
  {
    // Goal for right player:
    // 1- update scores
    // 2- reinit level (volleys, ball speed, paddle angles)
    ++score_.playerRight;
    ServeNewBall();
  }
  else if( ball_collider.x + ball_collider.w > field.width )
  {
    // Goal for left player!
    ++score_.playerLeft;
    ServeNewBall();

  }
  // Rebound on filed top and bottom walls
  else if(ball_collider.y < 0 || ball_collider.y + ball_collider.h > field.height)
  {                             
    ball_.Rebound(Ball::BounceDirection::kVertical);
  }
}

/**
 * Paddle collision is calculated using the SDL_HasIntersection and 
 * when true, the intersection rectange is calculated.
 * The logic is as follows:
 *  - when the intersection is wider than higher --> the collision happened on top or bottom edges;
 *  - when the intersection is higher than wider --> the collision happened on the left or right sides of the paddle.   
 */
void Game::CheckCollision(Ball &ball, Paddle &paddle)
{
  if(SDL_HasIntersection(&(ball.GetCollider()), &(paddle.GetCollider())))
  {
    SDL_Rect collision_intersection;
    if(SDL_IntersectRect(&(ball.GetCollider()), &(paddle.GetCollider()), &collision_intersection))
    {
      if(collision_intersection.h > collision_intersection.w)
      {
        ball.Rebound(Ball::BounceDirection::kHorizontal);
      }
      else
      {
          ball.Rebound(Ball::BounceDirection::kVertical);
      }  
    }
    ++volleys_;
  }
}

/**
 * Serves a new ball and resets game difficulty level
 * NOTE: this function  is called after a point;
 */
void Game::ServeNewBall()
{
      volleys_ = 0;
      ball_.ServeBall(field_.width / 2, field_.height / 2); //sets start position.
}