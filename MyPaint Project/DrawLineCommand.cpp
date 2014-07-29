#include "DrawLineCommand.h"
#include <algorithm>
#include <cmath>
#include "useful.h"


using namespace std;

DrawLineCommand::DrawLineCommand(const SDL_Point & fp, const SDL_Point & sp, const SDL_Colour & col, int bw):
	_firstPoint(fp), _secondPoint(sp), _colour(col), _brushWidth(bw)
{
	if (_secondPoint.y < _firstPoint.y)
		swap(_secondPoint,_firstPoint);
}

DrawLineCommand::~DrawLineCommand()
{
}

void DrawLineCommand::execute(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer,_colour);

	SDL_RenderDrawLine(renderer,_firstPoint.x,_firstPoint.y,_secondPoint.x,_secondPoint.y,_brushWidth);
}
