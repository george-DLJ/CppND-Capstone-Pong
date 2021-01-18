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

    //dimensions
    static const int kPaddleWidth = 20;
    static const int kPaddleHeight = 100;

    //Max axis velocity
    static const int kPaddleVel = 4; //speed: kPaddleVel (px) * FPS --> px/sec; currently: 4 px * 60 fps = 120 px/s

    //Constructor
    Paddle(const int min_y_pos, const int max_y_pos, const int paddle_center_x);

    //Take key presses and adjust velocity
    void startMovement(Direction direction);
    void stopMovement(Direction direction);

    //Move Paddle
    void move();

    //Show Paddle on screen:
    void render(SDL_Renderer* sdl_renderer);

    const SDL_Rect& getCollider() const;

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