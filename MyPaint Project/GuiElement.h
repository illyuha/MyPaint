#ifndef GUI_ELEMENT
#define GUI_ELEMENT

#include <SDL.h>
#include <vector>
#include "IGuiObservable.h"
#include "IRenderable.h"
#include "Editor.h"


using namespace std;

// the abstract base class for gui elements
class GuiElement : public IRenderable, public IGuiObservable
{
private:

	// renders the gui element to the SDL_Renderer
	virtual void doRender(SDL_Renderer *) = 0;
	virtual void doAttachObserver(IGuiObserver *) = 0;
	virtual void doAttachModel(Editor *) = 0;
	virtual void doInitChildren() = 0;

protected:
	// child elements
	vector<GuiElement *> _children;
	Editor * _editor;
	IGuiObserver * _observer;
	
	virtual void initChildren() final;
	virtual bool containsPoint(const SDL_Point &) = 0;

	GuiElement(const GuiElement &);
	GuiElement & operator=(const GuiElement &);

public:
	GuiElement(IGuiObserver * o = NULL, Editor * e = NULL):
		_observer(o), _editor(e)
	{}

	virtual ~GuiElement()
	{}

	// the following functions handle mouse events
	virtual bool tryHandleMouseClick(const SDL_Point &) = 0;
	virtual bool tryHandleMouseHover(const SDL_Point &) = 0;
	virtual bool tryHandleMouseRelease(const SDL_Point &) = 0;
	
	// NVI
	virtual void render(SDL_Renderer *) override final;
	virtual void attachObserver(IGuiObserver *) override final;
	virtual void attachModel(Editor *) final;

};


#endif