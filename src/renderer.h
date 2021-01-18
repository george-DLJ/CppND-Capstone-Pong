#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h> 
#include <vector>
#include <memory>
#include "IRenderable.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width,
                   const std::size_t screen_height);
        
        ~Renderer();

        void Render(std::vector<IRenderable*> elements); 
      
        void UpdateWindowTitle(int score_left, int score_right, int fps); 

    private: 
        SDL_Window *sdl_window_; 
        SDL_Renderer *sdl_renderer_; 

        const std::size_t screen_width_;
        const std::size_t screen_height_;
};

#endif /* RENDERER_H */