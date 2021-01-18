#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL.h>
#include "IRenderable.h"

class Paddle : public IRenderable
{
    public:
    // move directions
    enum class Direction{
        kUp,
        kDown,
    };

    //Paddle dimensions
    static const int kPaddleWidth = 20;
    static const int kPaddleHeight = 100;

    //Movement velocity
    // NOTE: This number shows the velocity of the paddle on each Game-Loop.
    //       as currently the game operates at around 60 FPS 
    //       this means the paddle moves at:  4 px/g-loop * 60 g-loops/s = 240 px/s
    static const int kPaddleVel = 4; 

    //Constructor
    Paddle(const int min_y_pos, const int max_y_pos, const int paddle_center_x);

    //React to user controls:
    void StartMovement(Direction direction);
    void StopMovement(Direction direction);

    //Move Paddle
    void Move();

    //Show Paddle on screen:
    void Render(SDL_Renderer* sdl_renderer) override;

    const SDL_Rect& GetCollider() const;

    private:
        // compute paddle X position based on width
        static int convert_to_paddle_rect_x(int paddle_center_x, int kPaddleWidth){return paddle_center_x - kPaddleWidth/2;}

        // min and max position of the paddle
        int min_y_pos_;
        int max_y_pos_;
        // Y location of the paddle
        int y_pos_;

        // X location of the paddle
        const int x_pos_;

        //The vel of the paddle
        int vel_y_;

        // collider
        SDL_Rect collider_;
};

#endif /* PADDLE_H */