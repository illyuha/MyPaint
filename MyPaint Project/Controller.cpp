#include "Controller.h"


Controller::Controller(Editor * editor, Window * window):
	_editor(editor), _window(window)
{
	_window->attachObserverToGuiElements(this);
}

Controller::~Controller()
{
}

void Controller::handle()
{
	SDL_Event ev;

	// while the user has not closed the window, Controller handles events
	while (!_editor->shouldClose() && SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type)
		{
			case SDL_QUIT:
			{
				_editor->close();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				// getting the coordinates of the mouse
				SDL_Point p;
				SDL_GetMouseState(&p.x,&p.y);
				_window->handleMouseClick(p);
			}
			break;
		case SDL_MOUSEMOTION:
			{
				// getting the coordinates of the mouse
				SDL_Point p;
				SDL_GetMouseState(&p.x,&p.y);
				_window->handleMouseHover(p);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			{
				// getting the coordinates of the mouse
				SDL_Point p;
				SDL_GetMouseState(&p.x,&p.y);
				_window->handleMouseRelease(p);
			}
			break;
		case SDL_KEYDOWN:
			{
				// when Ctrl is pressed
				if (SDL_GetModState() & KMOD_CTRL)
				{
					switch (ev.key.keysym.sym)
					{
						// when Z key is pressed
					case SDLK_z:
						_editor->tryUndoDrawing();
						break;
						// when Y key is pressed
					case SDLK_y:
						_editor->tryRedoDrawing();
						break;
					}
				}
				else
				{
					// when + (=) key is pressed the Model should increase/decrease the brush width
					switch (ev.key.keysym.sym)
					{
					case SDLK_EQUALS:
						_editor->tryIncreaseBrushWidth();
						break;
					case SDLK_MINUS:
						_editor->tryDecreaseBrushWidth();
						break;
					}
				}
			}
			break;
		}
	}
}

void Controller::onCanvasMouseButtonPressed(const SDL_Point & pos)
{
	_editor->onDrawingStarted(pos);
}

void Controller::onCanvasMouseMoved(const SDL_Point & pos)
{
	_editor->onPositionChanged(pos);
}

void Controller::onCanvasMouseButtonReleased()
{
	_editor->onDrawingStopped();
}

void Controller::onToolButtonClicked(ToolType ttype)
{
	_editor->selectedToolType() = ttype;
}

void Controller::onColourButtonClicked(const SDL_Colour & colour)
{
	_editor->selectedColour() = colour;
}
