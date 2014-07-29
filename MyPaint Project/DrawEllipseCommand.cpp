#include "DrawEllipseCommand.h"
#include <algorithm>
#include "useful.h"


using namespace std;

DrawEllipseCommand::DrawEllipseCommand(const SDL_Point & fp, const SDL_Point & sp, const SDL_Colour & col, int bw):
	_firstPoint(fp), _secondPoint(sp), _colour(col), _brushWidth(bw)
{
	if (_secondPoint.x < _firstPoint.x)
		swap(_firstPoint.x,_secondPoint.x);
	if (_secondPoint.y < _firstPoint.y)
		swap(_secondPoint.y,_firstPoint.y);
}

DrawEllipseCommand::~DrawEllipseCommand()
{
}

void DrawEllipseCommand::execute(SDL_Renderer * renderer)
{
	// x, y, width and height respectively
	int h = _secondPoint.y - _firstPoint.y, w = _secondPoint.x - _firstPoint.x;

	SDL_Rect rect = {_firstPoint.x, _firstPoint.y, w, h};
	rect.x -= 1 + _brushWidth / 2;
	rect.y -= 1 + _brushWidth / 2;
	rect.h += 2 +_brushWidth / 2 * 2;
	rect.w += 2 + _brushWidth / 2 * 2;

	SDL_SetRenderDrawColor(renderer,_colour);

	SDL_RenderDrawEllipse(renderer,&rect,_brushWidth);
}
