#include "Canvas.h"
#include "useful.h"
#include "Colours.h"


Canvas::Canvas(const SDL_Rect & rect):
	_viewRect(rect)
{
}

Canvas::~Canvas()
{
}

bool Canvas::containsPoint(const SDL_Point & pos)
{
	int lx = _viewRect.x, rx = _viewRect.x + _viewRect.w, uy = _viewRect.y, dy = _viewRect.y + _viewRect.h;
	return (lx <= pos.x && pos.x <= rx && dy >= pos.y && pos.y >= uy);
}

void Canvas::doInitChildren()
{
	// there are no child elements
}

void Canvas::doRender(SDL_Renderer * renderer)
{
	// obtaining a texture from Editor (Model)
	SDL_Texture * currentTexture = _editor->getCurrentTexture();

	// rendering texture
	SDL_RenderSetViewport(renderer,&_viewRect);
	SDL_Rect r = {0, 0, _viewRect.w, _viewRect.h};
	SDL_RenderCopy(renderer,currentTexture,&_viewRect,&r);	
	SDL_RenderSetViewport(renderer,NULL);
	
	// drawing a black rectangle around the canvas
	SDL_SetRenderDrawColor(renderer,BLACK);
	SDL_RenderDrawRect(renderer,&_viewRect);
}

void Canvas::notify()
{

}

void Canvas::doAttachObserver(IGuiObserver * observer)
{
	_observer = observer;
}

bool Canvas::tryHandleMouseClick(const SDL_Point & pos)
{
	bool handles = containsPoint(pos);
	if (handles)
		_observer->onCanvasMouseButtonPressed(pos);
	return handles;
}

bool Canvas::tryHandleMouseHover(const SDL_Point & pos)
{
	_observer->onCanvasMouseMoved(pos);
	return true;
}

bool Canvas::tryHandleMouseRelease(const SDL_Point & pos)
{
	if (_editor->isDrawing())
		_observer->onCanvasMouseButtonReleased();
	return false;
}

void Canvas::doAttachModel(Editor * editor)
{
	_editor = editor;
}
