#ifndef TOOL_BAR
#define TOOL_BAR

#include <vector>
#include "ToolButton.h"


using namespace std;

// this class stores tool buttons
class ToolBar : public GuiElement
{
private:
	SDL_Rect _viewRect;
	int _buttonWidth, _buttonHeight;

	// adds tool buttons to the tool bar
	void addButton(ToolType);
	void doRender(SDL_Renderer *);
	void doAttachObserver(IGuiObserver *);
	void doInitChildren();
	bool containsPoint(const SDL_Point &);
	void doAttachModel(Editor *);

	// not implemented
	ToolBar(const ToolBar &);
	ToolBar & operator=(const ToolBar &);

public:
	ToolBar(const SDL_Point &, int, int);
	~ToolBar();
	void notify();
	bool tryHandleMouseClick(const SDL_Point &);
	bool tryHandleMouseHover(const SDL_Point &);
	bool tryHandleMouseRelease(const SDL_Point &);

};


#endif