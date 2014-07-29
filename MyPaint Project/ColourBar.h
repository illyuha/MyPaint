#ifndef COLOUR_BAR
#define COLOUR_BAR

#include "ColourButton.h"

// this class stores colour buttons
class ColourBar : public GuiElement
{
private:
	SDL_Rect _viewRect;
	int _buttonWidth, _buttonHeight;

	// adds button to the colour bar
	void addButton(const SDL_Color &);

	void doRender(SDL_Renderer *);
	void doAttachObserver(IGuiObserver *);
	void doInitChildren();
	void doAttachModel(Editor *);

	bool containsPoint(const SDL_Point &);

	// not implemented
	ColourBar(const ColourBar &);
	ColourBar & operator=(const ColourBar &);

public:
	ColourBar(const SDL_Point &, int, int);
	~ColourBar();

	void notify();

	// methods for handling mouse events
	bool tryHandleMouseClick(const SDL_Point &);
	bool tryHandleMouseHover(const SDL_Point &);
	bool tryHandleMouseRelease(const SDL_Point &);

};


#endif