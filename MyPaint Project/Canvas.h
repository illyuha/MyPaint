#ifndef CANVAS
#define CANVAS

#include <algorithm>
#include "GuiElement.h"


using namespace std;

// the gui elements on which all the user's drawings are rendered
class Canvas : public GuiElement
{
private:
	SDL_Rect _viewRect;
	
	bool containsPoint(const SDL_Point &);
	void notify();

	// renders the texture obtained from Model (_editor) on the _renderer
	void doRender(SDL_Renderer *);

	void doInitChildren();
	void doAttachObserver(IGuiObserver *);
	void doAttachModel(Editor *);

	Canvas(const Canvas &);
	Canvas & operator=(const Canvas &);

public:
	Canvas(const SDL_Rect &);
	~Canvas();

	// the following functions handle mouse events when necessary
	bool tryHandleMouseClick(const SDL_Point &);
	bool tryHandleMouseHover(const SDL_Point &);
	bool tryHandleMouseRelease(const SDL_Point &);

};


#endif