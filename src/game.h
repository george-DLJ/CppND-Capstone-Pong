#ifndef GAME_H
#define GAME_H

#include <vector>
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

        // check collisions between two colliders. 
        // alternative: use SDL_IntersectRect()
        bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b); 

        void ServiceNewBall();

        Field field_;
        Ball ball_;
        Paddle paddle_left_;
        Paddle paddle_right_;
        Score score_;
        int volleys_; //current point volleys (use to control ball speed and paddle angles.)

        constexpr  static float kTargetFrameDuration = 1000.0 / 60.0; //milliseconds per frame at 60 frames per second


};

#endif /* GAME_H */