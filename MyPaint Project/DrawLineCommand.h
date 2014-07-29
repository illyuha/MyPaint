#ifndef DRAW_LINE_COMMAND
#define DRAW_LINE_COMMAND

#include "IDrawingCommand.h"


// The Command pattern's concrete Command
class DrawLineCommand : public IDrawingCommand
{
private:
	SDL_Point _firstPoint, _secondPoint;
	SDL_Colour _colour;
	int _brushWidth;

	DrawLineCommand(const DrawLineCommand &);
	DrawLineCommand & operator=(const DrawLineCommand &);

public:
	// the brush colour, brush width and two points are necessary to draw a line
	DrawLineCommand(const SDL_Point &, const SDL_Point &, const SDL_Colour &, int);
	~DrawLineCommand();
	void execute(SDL_Renderer *);
};


#endif