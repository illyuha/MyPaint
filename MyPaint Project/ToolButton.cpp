#include "ToolButton.h"
#include "useful.h"
#include "Colours.h"


ToolButton::ToolButton(const SDL_Rect & rect, ToolType ttype):
	_viewRect(rect), _toolType(ttype)
{
}

ToolButton::~ToolButton()
{
}

bool ToolButton::containsPoint(const SDL_Point & pos)
{
	int lx = _viewRect.x, rx = _viewRect.x + _viewRect.w, uy = _viewRect.y, dy = _viewRect.y + _viewRect.h;
	return (lx <= pos.x && pos.x <= rx && dy >= pos.y && pos.y >= uy);
}

void ToolButton::doRender(SDL_Renderer * renderer)
{
	// renders the white background for the button
	SDL_SetRenderDrawColor(renderer,WHITE);
	SDL_RenderFillRect(renderer,&_viewRect);

	// if this tool is selected then the frame is orange...
	if (_editor->selectedToolType() == _toolType)
		SDL_SetRenderDrawColor(renderer,ORANGE);
	else
	// ...otherwise it is black
		SDL_SetRenderDrawColor(renderer,BLACK);

	SDL_RenderDrawRect(renderer,&_viewRect);
	
	SDL_SetRenderDrawColor(renderer,BLACK);
	// drawing an "icon" for the button
	switch (_toolType)
	{
	case DrawRectangle:
		{
			SDL_Rect rect = {0.1*_viewRect.w+_viewRect.x, 0.1*_viewRect.h+_viewRect.y, 0.8*_viewRect.w, 0.7*_viewRect.h};
			SDL_RenderDrawRect(renderer,&rect);
		}
		break;
	case DrawEllipse:
		{
			SDL_Rect rect = {0.1*_viewRect.w+_viewRect.x, 0.1*_viewRect.h+_viewRect.y, 0.7*_viewRect.w, 0.8*_viewRect.h};
			SDL_RenderDrawEllipse(renderer,&rect);
		}
		break;
	case DrawLine:
		{
			SDL_Rect rect = {0.2*_viewRect.w+_viewRect.x, 0.1*_viewRect.h+_viewRect.y, 0.7*_viewRect.w, 0.8*_viewRect.h};
			SDL_RenderDrawLine(renderer,rect.x,rect.y,rect.x+rect.w,rect.y+rect.h);
		}
		break;
	}
}

void ToolButton::doInitChildren()
{
	// there are no children elements
}

void ToolButton::notify()
{

}

void ToolButton::doAttachObserver(IGuiObserver * observer)
{
	_observer = observer;
}

bool ToolButton::tryHandleMouseClick(const SDL_Point & pos)
{
	bool handles = containsPoint(pos);
	if (handles)
		_observer->onToolButtonClicked(getType());
	return handles;
}

bool ToolButton::tryHandleMouseHover(const SDL_Point &)
{
	return false;
}

bool ToolButton::tryHandleMouseRelease(const SDL_Point &)
{
	return false;
}

void ToolButton::doAttachModel(Editor * editor)
{
	_editor = editor;
}
