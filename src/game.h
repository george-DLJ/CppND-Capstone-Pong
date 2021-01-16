#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "controller.h"
#include "renderer.h"

#include "ball.h"
#include "paddle.h"


struct Score
{
    int playerLeft{0};
    int playerRight{0};
};

struct Field
{
    int width{0};
    int height{0};
    Field(int w, int h): width(w), height(h){};
};

class Game
{
    public:
    enum class Players{
        playerLeft,
        playerRight
    };
    Game(int field_width, int fiedl_height);
    void Run(const Controller  &controller, Renderer &renderer); //Controller const &controller, Renderer &renderer, std::size_t target_frame_duration

    Score GetScore() const;

    private: 
    void Update();
    void CheckFieldCollisions(Ball &ball, const Field &field);
  
    void CheckPaddleCollision(Ball &ball, Paddle &paddle);


    Field field_;
    Ball ball_;
    Paddle paddle_left_;
    Paddle paddle_right_;
    Score score_;
    int volleys_; //current point volleys (use to control ball speed and paddle angles.)


};

#endif /* GAME_H */