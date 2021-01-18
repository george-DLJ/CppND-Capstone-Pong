#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h" //TODO: clarify < or " ?
#include <vector>
#include <memory>
#include "IRenderable.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width,
                   const std::size_t screen_height);
        
        ~Renderer();

        //void Render(Ball &ball,  Paddle &paddleLeft,  Paddle &paddleRight); //Plan A
        void Render(std::vector<IRenderable*> elements); //Plan B
        void Render();  //Plan C.1 TODO: fix; it fails
                        // use in combi with AddRenderableElement New version: does not need to know the type of elements.

        void AddRenderableElement(std::shared_ptr<IRenderable> element); //Plan C.2 TODO: fix; it fails.
      
        void UpdateWindowTitle(int score_left, int score_right, int fps); 

    private: 
        SDL_Window *sdl_window_; //TODO: use smart_pointers!
        SDL_Renderer *sdl_renderer_; // TODO: use smart_pointers!

        std::vector<std::shared_ptr<IRenderable>> renderable_elements_;

        const std::size_t screen_width_;
        const std::size_t screen_height_;
};

#endif /* RENDERER_H */