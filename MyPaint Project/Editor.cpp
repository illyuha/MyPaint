#include "Editor.h"
#include "Colours.h"
#include "useful.h"


Editor::Editor():
	_drawing(false), _currentBrushWidth(1), _savedTexture(NULL), _bufferCommand(NULL), 
	SCREEN_WIDTH(800), SCREEN_HEIGHT(600), _activeCommandIndex(-1), _close(false), _bufferTexture(NULL)
{
	resetStartPoint();
	resetCurrentPoint();
}

Editor::~Editor()
{
}

SDL_Texture * Editor::getCurrentTexture()
{
	// returns _bufferTexture if user is drawing something by holding the mouse...
	if (_bufferTexture != NULL)
		return _bufferTexture;
	// ... and _savedTexture otherwise
	else
		return _savedTexture;
}

void Editor::deleteFollowingCommands()
{
	for (int i = _activeCommandIndex + 1; i < _commands.size(); ++i)
	{
		delete _commands[i];
		_commands[i] = NULL;
	}
	_commands.resize(_activeCommandIndex+1);
}

void Editor::onDrawingStarted(const SDL_Point & p)
{
	_drawing = true;
	_currentPoint = _startPoint = p;
	if (_savedTexture == NULL)
		resetSavedTexture();
	onPositionChanged(p);
}

void Editor::onPositionChanged(const SDL_Point & p)
{
	if (_drawing)
	{
		_currentPoint = p;
		delete _bufferCommand;
		switch (_selectedToolType)
		{
		case DrawRectangle:
			_bufferCommand = new DrawRectangleCommand(_startPoint,_currentPoint,_selectedColour,_currentBrushWidth);
			break;
		case DrawEllipse:
			_bufferCommand = new DrawEllipseCommand(_startPoint,_currentPoint,_selectedColour,_currentBrushWidth);
			break;
		case DrawLine:
			_bufferCommand = new DrawLineCommand(_startPoint,_currentPoint,_selectedColour,_currentBrushWidth);
			break;
		}
		updateBufferTexture();
	}
}

void Editor::onDrawingStopped()
{
	SDL_DestroyTexture(_savedTexture);
	_savedTexture = _bufferTexture;
	_bufferTexture = NULL;
	
	_drawing = false;

	deleteFollowingCommands();

	++_activeCommandIndex;
	
	_commands.push_back(_bufferCommand);
	_bufferCommand = NULL;
}

void Editor::updateBufferTexture()
{
	SDL_DestroyTexture(_bufferTexture);

	// create a clean texture
	_bufferTexture =
		SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

	// redirect render target to _bufferTexture
	SDL_SetTextureBlendMode(_bufferTexture,SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(_renderer,_bufferTexture);

	if (_savedTexture != NULL)
		// copy the _savedTexture to _bufferTexture
		SDL_RenderCopy(_renderer,_savedTexture,NULL,NULL);

	if (_bufferCommand != NULL)
		// execute current command (e.g. render a line on the _savedTexture)
		_bufferCommand->execute(_renderer);

	SDL_SetRenderTarget(_renderer,NULL);
}

void Editor::tryUndoDrawing()
{
	// "undoes" the last command if there is one
	if (!_drawing && _activeCommandIndex >= 0)
	{
		--_activeCommandIndex;

		// executing all the commands from the first to the current

		SDL_DestroyTexture(_savedTexture);
		resetSavedTexture();

		SDL_SetTextureBlendMode(_savedTexture,SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(_renderer,_savedTexture);

		for (int i = 0; i <= _activeCommandIndex; ++i)
			_commands[i]->execute(_renderer);

		SDL_SetRenderTarget(_renderer,NULL);
	}
}

void Editor::tryRedoDrawing()
{
	// "redoes" the command if possible
	if (!_drawing && ((_activeCommandIndex + 1 < _commands.size()) || _commands.empty()))
	{
		int i = _commands.size() - 1;
		++_activeCommandIndex;

		SDL_SetTextureBlendMode(_savedTexture,SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(_renderer,_savedTexture);

		_commands[_activeCommandIndex]->execute(_renderer);

		SDL_SetRenderTarget(_renderer,NULL);
	}
}

void Editor::resetSavedTexture()
{
	_savedTexture =
		SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);

	// redirecting drawing to texture
	SDL_SetTextureBlendMode(_savedTexture,SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(_renderer,_savedTexture);
	
	// draws a white filled rectangle (i.e. canvas) on the texture
	SDL_SetRenderDrawColor(_renderer,WHITE);
	SDL_Rect r = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_RenderFillRect(_renderer,&r);

	SDL_SetRenderTarget(_renderer,NULL);
}

void Editor::setRenderer(SDL_Renderer * renderer)
{
	_renderer = renderer;
	resetSavedTexture();
}
