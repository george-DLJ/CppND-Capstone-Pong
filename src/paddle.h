#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL.h>

class Paddle
{
    public:
    // move directions
    enum class Direction{
        kUp,
        kDown,
    };

    //dimensions
    static const int PADDLE_WIDTH = 20;
    static const int PADDLE_HEIGHT = 100;

    //Max axis velocity
    static const int PADDLE_VEL = 2; //

    //Constructor
    Paddle(const int min_y_pos, const int max_y_pos, const int paddle_center_x);

    //Take key presses and adjust velocity
    void handleEvent( SDL_Event& e ); //TODO: remove
    void startMovement(Direction direction);
    void stopMovement(Direction direction);

    //Move Paddle
    void move();

    //Show Paddle on screen:
    void render(SDL_Renderer* sdl_renderer);

    const SDL_Rect& getCollider() const;

    private:
        // compute paddle X position based on width
        static int convert_to_paddle_rect_x(int paddle_center_x, int paddle_width){return paddle_center_x - paddle_width/2;}

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