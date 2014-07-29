#include "DrawRectangleCommand.h"
#include <algorithm>
#include "useful.h"


using namespace std;

DrawRectangleCommand::DrawRectangleCommand(const SDL_Point & fp, const SDL_Point & sp, const SDL_Colour & col, int bw):
	_firstPoint(fp), _secondPoint(sp), _colour(col), _brushWidth(bw)
{
	if (_secondPoint.x < _firstPoint.x)
		swap(_firstPoint.x,_secondPoint.x);
	if (_secondPoint.y < _firstPoint.y)
		swap(_secondPoint.y,_firstPoint.y);
}

DrawRectangleCommand::~DrawRectangleCommand()
{
}

void DrawRectangleCommand::execute(SDL_Renderer * renderer)
{
	// x, y, width and height respectively
	SDL_Rect rect = {_firstPoint.x, _firstPoint.y, _secondPoint.x-_firstPoint.x, _secondPoint.y-_firstPoint.y};
	rect.x -= 1 + _brushWidth / 2;
	rect.y -= 1 + _brushWidth / 2;
	rect.h += 2 +_brushWidth / 2 * 2;
	rect.w += 2 + _brushWidth / 2 * 2;

	int bw = _brushWidth;

	SDL_SetRenderDrawColor(renderer,_colour);

	SDL_RenderDrawRect(renderer,&rect,_brushWidth);
}
