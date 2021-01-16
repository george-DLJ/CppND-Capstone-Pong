#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(int fieldWidth, int fieldHeight)
    : field_(fieldWidth, fieldHeight),
      ball_(fieldWidth, fieldHeight),
      paddle_left_(0, fieldHeight, 20),
      paddle_right_(0, fieldHeight, fieldWidth - 20),
      score_{0,0},
      volleys_(0) {
}

//void Game::Run(Controller const &controller, Renderer &renderer,               std::size_t target_frame_duration)
void Game::Run(const Controller &controller, Renderer &renderer) // First approach without frame_calc 
{
//  Uint32 title_timestamp = SDL_GetTicks();
//  Uint32 frame_start;
//  Uint32 frame_end;
//  Uint32 frame_duration;
//  int frame_count = 0;
  
  bool running = true;

    // Game loop:
    while (running) //playing, playingPoint
    {
    //frame_start = SDL_GetTicks();

    // 1. Handle User Input:
    controller.HandleInput(running, paddle_left_, paddle_right_);
    // 2. Update:
    Update();
    // 3. Render:
    // TODO: render once every x milliseconds.
    renderer.Render(ball_, paddle_left_, paddle_right_);

    //frame_end = SDL_GetTicks();

    //// Keep track of how long each loop through the input/update/render cycle
    //// takes.
    //frame_count++;
    //frame_duration = frame_end - frame_start;

    //// After every second, update the window title.
    //if (frame_end - title_timestamp >= 1000) {
    //  renderer.UpdateWindowTitle(score, frame_count);
    //  frame_count = 0;
    //  title_timestamp = frame_end;
    //}

    // // If the time for this frame is too small (i.e. frame_duration is
    // // smaller than the target ms_per_frame), delay the loop to
    // // achieve the correct frame rate.
    // if (frame_duration < target_frame_duration) {
    //   SDL_Delay(target_frame_duration - frame_duration);
    // }
  }
}


void Game::Update() {
  // 1. Update movements
  // 1.1 Update Ball
  ball_.move();  
  // 1.2 Update Paddles
  paddle_left_.move();
  paddle_right_.move();  
  // 2. CheckCollisions:
  // 2.1 CheckFieldCollisions
  CheckFieldCollisions(ball_, field_);
  // 2.2 CheckPaddleCollisions
  CheckPaddleCollision(ball_, paddle_left_);
  CheckPaddleCollision(ball_, paddle_right_);
  // 3. Set Difficulty
  // ball speed and paddle angles:
  // CheckGameLevel(++_volleys);  
}

Score Game::GetScore() const { return score_; }

void Game::CheckFieldCollisions(Ball &ball, const Field &field)
{
  
}

void Game::CheckPaddleCollision(Ball &ball, Paddle &paddle)
{
  if (CheckCollision(ball.getCollider(), paddle.getCollider()))
  {
    // rebound ball
    ball.Rebound(Ball::CollisionSide::left);

    // increase volleys count
    ++volleys_;
  }
  // 
  // 
  // 
}

// Check gameLevel:
//  if volleys == 4
//  1. increase speed to SPEED_LEVEL_2
//  2. increase Paddles angles (set to ANGLE_LEVEL_2)

//  if volleys == 12 
//  1. increase ball speed: set to SPEED_LEVEL_3
//  2. increase Paddles angles (set to ANGLE_LEVEL_3...)
 
// Based on lazyfoo tutorial collision method.
// Alternative: use SDL_IntersectRect() 
// TODO: refactor names 
// TODO: reimplement using SDL_intersect-
bool Game::CheckCollision(const SDL_Rect &a, const SDL_Rect &b)
{
  //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //Here is where the collision detection happens. This code calculates the top/bottom and left/right of each of the collison boxes.
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}