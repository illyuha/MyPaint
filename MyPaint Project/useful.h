#ifndef USEFUL
#define USEFUL

#include <SDL.h>
#include <stdexcept>
#include <string>

using namespace std;


class SDLException : public runtime_error
{
public:
	SDLException(string mes):
		runtime_error(string(mes.append(string("SDL Error: ").append(SDL_GetError()))))
	{}
};

int SDL_RenderDrawEllipse(SDL_Renderer *, const SDL_Rect *, int width = 1);
int SDL_RenderDrawLine(SDL_Renderer *, int, int, int, int, int);
int SDL_RenderDrawRect(SDL_Renderer *, const SDL_Rect *, int);

int SDL_SetRenderDrawColor(SDL_Renderer *, const SDL_Colour &);


#endif