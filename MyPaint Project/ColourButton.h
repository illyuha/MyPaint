#ifndef COLOUR_BUTTON
#define COLOUR_BUTTON

#include "GuiElement.h"


class ColourButton : public GuiElement
{
private:
	SDL_Rect _viewRect;
	SDL_Colour _colour;
	
	void doRender(SDL_Renderer *);
	void doAttachObserver(IGuiObserver *);
	bool containsPoint(const SDL_Point &);
	void doInitChildren();
	void doAttachModel(Editor *);
	
public:
	ColourButton(const SDL_Rect &, const SDL_Colour &);
	~ColourButton();

	void notify();
	
	bool tryHandleMouseClick(const SDL_Point &);
	bool tryHandleMouseHover(const SDL_Point &);
	bool tryHandleMouseRelease(const SDL_Point &);

	SDL_Colour getColour()
	{
		return _colour;
	}

};


#endif