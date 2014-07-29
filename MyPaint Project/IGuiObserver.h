#ifndef I_GUI_OBSERVER
#define I_GUI_OBSERVER

#include "ToolTypes.h"
#include <SDL.h>


class IGuiObserver
{
public:
	virtual ~IGuiObserver()
	{}
	virtual void onCanvasMouseButtonPressed(const SDL_Point &) = 0;
	virtual void onCanvasMouseMoved(const SDL_Point &) = 0;
	virtual void onCanvasMouseButtonReleased() = 0;
	virtual void onToolButtonClicked(ToolType) = 0;
	virtual void onColourButtonClicked(const SDL_Colour &) = 0;
	
};


#endif