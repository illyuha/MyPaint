#include "Colours.h"


bool operator==(const SDL_Colour & f, const SDL_Colour & s)
{
	return f.a == s.a && f.r == s.r && f.g == s.g && f.b == s.b;
}

bool operator!=(const SDL_Colour & f, const SDL_Colour & s)
{
	return !(f == s);
}


int SDL_SetRenderDrawColor(SDL_Renderer * renderer, const SDL_Colour & colour)
{
	return SDL_SetRenderDrawColor(renderer,colour.r,colour.g,colour.b,colour.a);
}
