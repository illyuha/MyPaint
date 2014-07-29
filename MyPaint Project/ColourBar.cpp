#include "ColourBar.h"
#include "Colours.h"


ColourBar::ColourBar(const SDL_Point & pos, int w, int h):
	_buttonWidth(w), _buttonHeight(h)
{
	_viewRect.x = pos.x;
	_viewRect.y = pos.y;
	_viewRect.h = 2 * _buttonHeight;
	_viewRect.w = 0;
	doInitChildren();
}

ColourBar::~ColourBar()
{
	for (auto & b : _children)
	{
		delete b;
		b = NULL;
	}
}

bool ColourBar::containsPoint(const SDL_Point & pos)
{
	int lx = _viewRect.x, rx = _viewRect.x + _viewRect.w, uy = _viewRect.y, dy = _viewRect.y + _viewRect.h;
	return (lx <= pos.x && pos.x <= rx && dy >= pos.y && pos.y >= uy);
}

void ColourBar::doRender(SDL_Renderer * renderer)
{
	// rendering all the colour buttons
	for (auto & b : _children)
		b->render(renderer);
}

void ColourBar::addButton(const SDL_Color & col)
{
	ColourButton * btn = NULL;
	if (_children.size() % 2 == 1)
	{
		SDL_Rect btnRect = {_viewRect.x+_viewRect.w-_buttonWidth, _viewRect.y+_buttonHeight, _buttonWidth, _buttonHeight};
		btn = new ColourButton(btnRect,col);
	}
	else
	{
		SDL_Rect btnRect = {_viewRect.x+_viewRect.w, _viewRect.y, _buttonWidth, _buttonHeight};
		btn = new ColourButton(btnRect,col);
		_viewRect.w += _buttonWidth;
	}
	_children.push_back(btn);
}

void ColourBar::doInitChildren()
{
	addButton(BLACK);
	addButton(WHITE);
	addButton(BLUE);
	addButton(YELLOW);
	addButton(GREEN);
	addButton(RED);
	addButton(BROWN);
	addButton(PINK);
}

void ColourBar::notify()
{
}

void ColourBar::doAttachObserver(IGuiObserver * observer)
{
	for (auto & b : _children)
		b->attachObserver(observer);
}

bool ColourBar::tryHandleMouseClick(const SDL_Point & pos)
{
	bool handles = containsPoint(pos);
	if (handles)
		for (auto & b : _children)
			b->tryHandleMouseClick(pos);
	return handles;
}

bool ColourBar::tryHandleMouseHover(const SDL_Point &)
{
	return false;
}

bool ColourBar::tryHandleMouseRelease(const SDL_Point &)
{
	return false;
}

void ColourBar::doAttachModel(Editor * editor)
{
	_editor = editor;
}