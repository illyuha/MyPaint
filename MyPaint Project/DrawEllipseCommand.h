#ifndef DRAW_ELLIPSE_COMMAND
#define DRAW_ELLIPSE_COMMAND

#include "IDrawingCommand.h"


// The Command pattern's concrete Command
class DrawEllipseCommand : public IDrawingCommand
{
private:
	SDL_Point _firstPoint, _secondPoint;
	SDL_Colour _colour;
	int _brushWidth;

	DrawEllipseCommand(const DrawEllipseCommand &);
	DrawEllipseCommand & operator=(const DrawEllipseCommand &);

public:
	// the brush colour, brush width and two points are necessary to draw an ellipse
	DrawEllipseCommand(const SDL_Point &, const SDL_Point &, const SDL_Colour &, int);
	~DrawEllipseCommand();
	void execute(SDL_Renderer *);

};


#endif