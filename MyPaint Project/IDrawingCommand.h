#ifndef I_DRAWING_COMMAND
#define I_DRAWING_COMMAND

#include <SDL.h>


// The Command pattern's abstract Command
class IDrawingCommand
{
public:
	virtual ~IDrawingCommand()
	{}
	virtual void execute(SDL_Renderer *) = 0;

};


#endif