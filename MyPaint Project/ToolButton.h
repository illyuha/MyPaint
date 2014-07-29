#ifndef TOOL_BUTTON
#define TOOL_BUTTON

#include "GuiElement.h"
#include "ToolTypes.h"

// class for tool buttons
class ToolButton : public GuiElement
{
private:
	SDL_Rect _viewRect;
	ToolType _toolType;
	
	void doRender(SDL_Renderer *);
	void doAttachObserver(IGuiObserver *);
	bool containsPoint(const SDL_Point &);
	void doInitChildren();
	void doAttachModel(Editor *);
	
public:
	ToolButton(const SDL_Rect &, ToolType);
	~ToolButton();
	void notify();
	bool tryHandleMouseClick(const SDL_Point &);
	bool tryHandleMouseHover(const SDL_Point &);
	bool tryHandleMouseRelease(const SDL_Point &);

	ToolType getType()
	{
		return _toolType;
	}

};


#endif