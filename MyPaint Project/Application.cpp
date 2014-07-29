#include "Application.h"
#include "ToolBar.h"
#include "Colours.h"


Application::Application():
	_editor(), 
	_window(&_editor),
	_controller(&_editor,&_window)
{
	// making the DrawEllipse button active
	_controller.onToolButtonClicked(DrawEllipse);

	// setting the default colour
	_controller.onColourButtonClicked(BLACK);
}

Application::~Application()
{
	void cleanUp();
}

Application & Application::getInstance()
{
	// Meyers' implementation of Singleton
	static Application instance;
	return instance;
}

void Application::run()
{
	// the main loop
	while (!_editor.shouldClose())
	{
		// Controller handles events, modifies the Model
		_controller.handle();

		// View is rendered
		_window.render();
	}
}

