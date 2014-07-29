#ifndef I_RENDERABLE
#define I_RENDERABLE

#include <SDL.h>


class IRenderable
{
public:
	virtual ~IRenderable()
	{}
	virtual void render(SDL_Renderer *) = 0;

};


#endif