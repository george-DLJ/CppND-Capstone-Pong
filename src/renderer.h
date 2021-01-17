#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h" //TODO: clarify < or " ?
#include "ball.h"
#include "paddle.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width,
                   const std::size_t screen_height);
        
        ~Renderer();

        void Render(Ball &ball,  Paddle &paddleLeft,  Paddle &paddleRight);
        void UpdateScore(int leftPlayerScore, int rightPlayerScore);
        void UpdateWindowTitle(int score_left, int score_right, int fps); 
      
    private: 
        SDL_Window *sdl_window_; //TODO: use smart_pointers!
        SDL_Renderer *sdl_renderer_; // TODO: use smart_pointers!

        const std::size_t screen_width_;
        const std::size_t screen_height_;
};

#endif /* RENDERER_H */