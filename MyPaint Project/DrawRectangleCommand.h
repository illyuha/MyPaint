#ifndef DRAW_RECTANGLE_COMMAND
#define DRAW_RECTANGLE_COMMAND

#include "IDrawingCommand.h"


// The Command pattern' concrete Command
class DrawRectangleCommand : public IDrawingCommand
{
private:
	SDL_Point _firstPoint, _secondPoint;
	SDL_Colour _colour;
	int _brushWidth;

	DrawRectangleCommand(const DrawRectangleCommand &);
	DrawRectangleCommand & operator=(const DrawRectangleCommand &);

public:
	// the brush colour, brush width and two points are necessary to draw a rectangle
	DrawRectangleCommand(const SDL_Point &, const SDL_Point &, const SDL_Colour &, int);
	~DrawRectangleCommand();
	void execute(SDL_Renderer *);

};


#endif