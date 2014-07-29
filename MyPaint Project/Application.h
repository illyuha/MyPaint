#ifndef APPLICATION
#define APPLICATION

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <SDL.h>
#include "GuiElement.h"
#include "Canvas.h"
#include "Controller.h"
#include "Editor.h"
#include "Window.h"


using namespace std;

// the main class; it creates the Model, the View and the Controller
class Application
{
private:
	// the Model
	Editor _editor;

	// the View
	Window _window;

	// the Controller
	Controller _controller;

	Application();

	Application(const Application &);
	Application & operator=(const Application &);

public:
	static Application & getInstance();

	~Application();

	// the main loop of the applications run here
	void run();

};


#endif