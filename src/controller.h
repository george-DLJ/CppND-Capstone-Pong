#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "paddle.h"

class Controller{
    public:
        // Const method! it cannot change the instance data.
        void HandleInput(bool &running, Paddle &paddle_left, Paddle &paddle_right) const;
    private:
        void MovePaddle(Paddle &paddle);
};

#endif /* CONTROLLER_H */