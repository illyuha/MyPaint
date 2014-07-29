#ifndef CONTROLLER
#define CONTROLLER

#include <SDL.h>
#include "IGuiObserver.h"
#include "Editor.h"
#include "Window.h"


// MVC: Controller
// This class is an Observer; it observes gui elements (the Observer pattern)
class Controller : public IGuiObserver
{
private:
	// the Model
	Editor * _editor;

	// the View
	Window * _window;

public:
	Controller(Editor *, Window *);
	~Controller();
	void handle();

	// invoked when a mouse button is clicked on the canvas
	void onCanvasMouseButtonPressed(const SDL_Point &);
	
	// invoked when the mouse is moved
	void onCanvasMouseMoved(const SDL_Point &);
	
	// invoked when a mouse button is released
	void onCanvasMouseButtonReleased();
	
	// invoked when a user selects a tool
	void onToolButtonClicked(ToolType);
	
	// invoked when a user selects a colour
	void onColourButtonClicked(const SDL_Colour &);

};


#endif