#ifndef WINDOW
#define WINDOW

#include <vector>
#include "GuiElement.h"
#include <SDL.h>
#include "useful.h"
#include "Canvas.h"
#include "ToolBar.h"
#include "IGuiObserver.h"
#include "ColourBar.h"


using namespace std;

// MVC: View
// renders all the gui elements
class Window
{
private:
	vector<GuiElement *> _guiElements;

	// necessary SDL pointers
	SDL_Window * _window;
	SDL_Renderer * _renderer;
	
	// pointer to Model
	Editor * _editor;
	
	void init();
	void initGuiElements();
	void cleanUp();
	
	// propagates the Model pointer to all gui elements
	void attachModelToGuiElements();

public:
	Window(Editor *);
	~Window();

	// renders everything that the Model creates/changes
	void render();

	// handling mouse events
	void handleMouseClick(const SDL_Point &);
	void handleMouseHover(const SDL_Point &);
	void handleMouseRelease(const SDL_Point &);

	void attachObserverToGuiElements(IGuiObserver *);

};


#endif