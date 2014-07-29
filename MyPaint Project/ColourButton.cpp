#include "ColourButton.h"
#include "Colours.h"
#include "useful.h"


ColourButton::ColourButton(const SDL_Rect & rect, const SDL_Colour & colour):
	_viewRect(rect), _colour(colour) 
{
}

ColourButton::~ColourButton()
{
}

bool ColourButton::containsPoint(const SDL_Point & pos)
{
	int lx = _viewRect.x, rx = _viewRect.x + _viewRect.w, uy = _viewRect.y, dy = _viewRect.y + _viewRect.h;
	return (lx <= pos.x && pos.x <= rx && dy >= pos.y && pos.y >= uy);
}

void ColourButton::doRender(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer,_colour);
	SDL_RenderFillRect(renderer,&_viewRect);

	if (_editor->selectedColour() == _colour)
		SDL_SetRenderDrawColor(renderer,ORANGE);
	else
		SDL_SetRenderDrawColor(renderer,BLACK);
	SDL_RenderDrawRect(renderer,&_viewRect);
}

void ColourButton::doInitChildren()
{
	// there are no children elements
}

void ColourButton::notify()
{

}

void ColourButton::doAttachObserver(IGuiObserver * observer)
{
	_observer = observer;
}

void ColourButton::doAttachModel(Editor * editor)
{
	_editor = editor;
}

bool ColourButton::tryHandleMouseClick(const SDL_Point & pos)
{
	bool handles = containsPoint(pos);
	if (handles)
		_observer->onColourButtonClicked(getColour());
	return handles;
}

bool ColourButton::tryHandleMouseHover(const SDL_Point &)
{
	return false;
}

bool ColourButton::tryHandleMouseRelease(const SDL_Point &)
{
	return false;
}
