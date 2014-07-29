#include "GuiElement.h"


void GuiElement::render(SDL_Renderer * renderer)
{
	doRender(renderer);
	for (auto & c : _children)
		c->render(renderer);
}

void GuiElement::attachObserver(IGuiObserver * observer) 
{
	doAttachObserver(observer);
	for (auto & c : _children)
		c->attachObserver(observer);
}

void GuiElement::initChildren()
{
	for (auto & c : _children)
		c->initChildren();
}

void GuiElement::attachModel(Editor * editor)
{
	doAttachModel(editor);
	for (auto & c : _children)
		c->attachModel(editor);
}
