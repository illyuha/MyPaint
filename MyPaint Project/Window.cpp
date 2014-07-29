#include "Window.h"


Window::Window(Editor * editor):
	_window(NULL), _renderer(NULL), _editor(editor)
{
	init();
	_editor->setRenderer(_renderer);
}

Window::~Window()
{
	cleanUp();
}

void Window::init()
{
	// initializing SDL_Window and SDL_Renderer
	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		throw SDLException("Failed to initialize SDL!");
	}
	else
	{
		_window = SDL_CreateWindow("MyPaint",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,_editor->getScreenWidth(),_editor->getScreenHeight(),SDL_WINDOW_SHOWN);
		if (_window == NULL)
		{
			throw SDLException("Failed to create window!");
		}
		else
		{
			_renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED);
			if (_renderer == NULL)
				throw SDLException("Failed to create renderer!");
			else
			{
				// creating gui elements
				initGuiElements();

				attachModelToGuiElements();
			}
		}
	}
}

void Window::attachModelToGuiElements()
{
	for (auto & e : _guiElements)
		e->attachModel(_editor);
}

void Window::initGuiElements()
{
	// initializing canvas
	SDL_Rect canvasRect;
	int indent = 100;
	canvasRect.x = canvasRect.y = indent;
	canvasRect.h = _editor->getScreenHeight() - 2 * indent;
	canvasRect.w = _editor->getScreenWidth() - 2 * indent;
	Canvas * canvas = new Canvas(canvasRect);
	_guiElements.push_back(canvas);

	// initializing toolbar
	SDL_Point toolBarPos = {10, 110};
	int toolBtnW = 30, toolBtnH = 30;
	ToolBar * toolBar = new ToolBar(toolBarPos,toolBtnW,toolBtnH);
	_guiElements.push_back(toolBar);

	// initializing colour bar
	SDL_Point colourBarPos = {300, 10};
	int colBtnW = toolBtnW, colBtnH = toolBtnH;
	ColourBar * colBar = new ColourBar(colourBarPos,colBtnW,colBtnH);
	_guiElements.push_back(colBar);
}

void Window::cleanUp()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = NULL;
	_window = NULL;
	SDL_Quit();

	for (auto & e : _guiElements)
	{
		delete e;
		e = NULL;
	}
	_guiElements.clear();
}

void Window::render()
{
	// creating blue light-blue background
	SDL_SetRenderDrawColor(_renderer,0x7F,0xC9,0xFF,0xFF);
	SDL_RenderClear(_renderer);

	// rendering all the gui elements
	for (auto & e : _guiElements)
		e->render(_renderer);

	SDL_RenderPresent(_renderer);
}

void Window::handleMouseClick(const SDL_Point & pos)
{
	for (auto & e : _guiElements)
	{
		bool handles = e->tryHandleMouseClick(pos);
		if (handles)
			break;
	}
}

void Window::handleMouseHover(const SDL_Point & pos)
{
	for (auto & e : _guiElements)
	{
		bool handles = e->tryHandleMouseHover(pos);
		if (handles)
			break;
	}
}

void Window::handleMouseRelease(const SDL_Point & pos)
{
	for (auto & e : _guiElements)
	{
		bool handles = e->tryHandleMouseRelease(pos);
		if (handles)
			break;
	}
}

void Window::attachObserverToGuiElements(IGuiObserver * observer)
{
	for (auto & e : _guiElements)
		e->attachObserver(observer);
}
