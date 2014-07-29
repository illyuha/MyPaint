#include <SDL.h>
#include "Application.h"
#include <stdexcept>
#include <iostream>


using namespace std;

int main(int argc, char * argv[])
{
	try
	{
		Application & app = Application::getInstance();
		app.run();
	}
	catch (std::runtime_error & er)
	{
		cerr << er.what();
	}

	// One can draw rectangle, ellipse and line
	// One can increase or decrease the brush width by pressing plus and minus buttons respectively (the maximum allowed width is 33)
	// One can press Ctrl+Z and Ctrl+Y to undo or redo actions
	// One can also select a colour at the palette bar

	// This solution implements the MVC pattern:
	// - Editor is the Model; it stores necessary information about the drawing process
	// - Window is the View; it renders gui elements 
	// - Controller is also an Observer (Observer pattern); GuiElements are Observable and notify the Controller of changes (e.g. button pressed)

	// This application also uses the Command pattern:
	// - Editor is the Invoker
	// - implementations of IDrawingCommands are Concrete Commands

	return 0;
}
