#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include <SDL.h>

/**
 * Create an interface (pure abstract class) to define renderable 
 * elements for the game
 * 
 * Reference: "A tour of C++" 2nd Ed from  B. Stipstrout p.54
 */ 
class IRenderable
{
public:
    // '=0' at the end of the function states that this is a 'pure virtual' function,  
    // this means, that it must be implemented by derived classes.
    virtual void render(SDL_Renderer* sdl_renderer) = 0;

    // Interfaces must always implement virtual destructor:
    // The reason is if the destructor is non-virtual, they will call the interface's destructor 
    // (or the compiler-provided default, if none is specified), instead of the derived class's destructor.
    // see: https://stackoverflow.com/a/270925
    virtual ~IRenderable() {};
};

#endif /* IRENDERABLE_H_ */