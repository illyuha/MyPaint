#include "ToolBar.h"


ToolBar::ToolBar(const SDL_Point & pos, int w, int h):
	_buttonWidth(w), _buttonHeight(h)
{
	_viewRect.x = pos.x;
	_viewRect.y = pos.y;
	_viewRect.w = 2 * _buttonWidth;
	_viewRect.h = 0;

	doInitChildren();
}

ToolBar::~ToolBar()
{
	for (int i = 0; i < _children.size(); ++i)
	{
		delete _children[i];
		_children[i] = NULL;
	}
}

bool ToolBar::containsPoint(const SDL_Point & pos)
{
	int lx = _viewRect.x, rx = _viewRect.x + _viewRect.w, uy = _viewRect.y, dy = _viewRect.y + _viewRect.h;
	return (lx <= pos.x && pos.x <= rx && dy >= pos.y && pos.y >= uy);
}

void ToolBar::doRender(SDL_Renderer * renderer)
{
	for (auto & b : _children)
		b->render(renderer);
}

void ToolBar::addButton(ToolType ttype)
{
	ToolButton * btn = NULL;
	if (_children.size() % 2 == 1)
	{
		SDL_Rect btnRect = {_viewRect.x+_buttonWidth, _viewRect.y+_viewRect.h-_buttonHeight, _buttonWidth, _buttonHeight};
		btn = new ToolButton(btnRect,ttype);
	}
	else
	{
		SDL_Rect btnRect = {_viewRect.x, _viewRect.y+_viewRect.h, _buttonWidth, _buttonHeight};
		btn = new ToolButton(btnRect,ttype);
		_viewRect.h += _buttonHeight;
	}
	_children.push_back(btn);
}

void ToolBar::doInitChildren()
{
	addButton(DrawRectangle);
	addButton(DrawEllipse);
	addButton(DrawLine);
}

void ToolBar::notify()
{
}

void ToolBar::doAttachObserver(IGuiObserver * observer)
{
	for (auto & b : _children)
		b->attachObserver(observer);
}

bool ToolBar::tryHandleMouseClick(const SDL_Point & pos)
{
	bool handles = false;
	if (containsPoint(pos))
		for (auto & b : _children)
		{
			handles = b->tryHandleMouseClick(pos);
			if (handles)
				break;
		}
	return handles;
}

bool ToolBar::tryHandleMouseHover(const SDL_Point &)
{
	return false;
}

bool ToolBar::tryHandleMouseRelease(const SDL_Point &)
{
	return false;
}

void ToolBar::doAttachModel(Editor * editor)
{
	_editor = editor;
}
