#ifndef EDITOR
#define EDITOR

#include <SDL.h>
#include "ToolTypes.h"
#include <algorithm>
#include <vector>
#include "DrawRectangleCommand.h"
#include "DrawEllipseCommand.h"
#include "DrawLineCommand.h"
//#include "PaintBucketCommand.h"


using namespace std;

// MVC: Model
// stores the necessary drawing information and the clipboard data
// the Model draws into the texture and then passes it to the Window (View) which renders this texture
class Editor
{
private:
	static const int MAX_BRUSH_WIDTH = 33;
	static const int MIN_BRUSH_WIDTH = 1;
	
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	// _drawing is false if a user has pressed the mouse button and is holding it (i.e. drawing something)
	bool _drawing;
	
	// the colour of the brush
	SDL_Color _selectedColour;
	
	// the point where a user has started drawing at
	SDL_Point _startPoint;
	
	// the point the mouse is over at the moment
	SDL_Point _currentPoint;

	// the selected tool type
	ToolType _selectedToolType;

	int _currentBrushWidth;
	
	// array of performed commands (e.g. a "draw rectangle" command)
	vector<IDrawingCommand *> _commands;

	// the command currently performed, i.e. while user is holding a mouse button
	IDrawingCommand * _bufferCommand;

	// this texture stores rendered drawings (from the first (if any) to the current command in the clipboard list (i.e. _commands))
	SDL_Texture * _savedTexture;

	// this texture stores the unfinished drawing
	SDL_Texture * _bufferTexture;

	// index of the last executed (rendered) command
	int _activeCommandIndex;

	// true when a user closes the windows
	bool _close;

	SDL_Renderer * _renderer;
	
	// updates the buffered texture when a user is botn holding and moving the mouse 
	void updateBufferTexture();

	// clears the saved texture
	void resetSavedTexture();

	// deletes all the commands after the current in the "clipboard" array
	void deleteFollowingCommands();

public:
	Editor();
	~Editor();

	bool isDrawing()
	{
		return _drawing;
	}

	void onDrawingStarted(const SDL_Point & p);

	void resetStartPoint()
	{
		_startPoint.x = _startPoint.y = -1;
	}

	void resetCurrentPoint()
	{
		_currentPoint.x = _currentPoint.y = -1;
	}

	ToolType & selectedToolType()
	{
		return _selectedToolType;
	}

	const ToolType & selectedToolType() const
	{
		return _selectedToolType;
	}

	SDL_Colour & selectedColour()
	{
		return _selectedColour;
	}
	
	const SDL_Colour & selectedColour() const
	{
		return _selectedColour;
	}

	// increases the brush width if it is less than the MAX_BRUSH_WIDTH
	void tryIncreaseBrushWidth()
	{
		if (!_drawing)
			_currentBrushWidth = min(_currentBrushWidth+1,MAX_BRUSH_WIDTH);
	}
	
	// decreases the brush width if it is greater than the MIN_BRUSH_WIDTH
	void tryDecreaseBrushWidth()
	{
		if (!_drawing)
			_currentBrushWidth = max(_currentBrushWidth-1,MIN_BRUSH_WIDTH);
	}

	// returns the texture which should be rendered
	SDL_Texture * getCurrentTexture();

	int getScreenWidth()
	{
		return SCREEN_WIDTH;
	}

	int getScreenHeight()
	{
		return SCREEN_HEIGHT;
	}

	void onPositionChanged(const SDL_Point &);

	void onDrawingStopped();

	// called when Ctrl+Z is pressed
	void tryUndoDrawing();
	
	// called when Ctrl+Y is pressed
	void tryRedoDrawing();

	void close()
	{
		_close = true;
	}

	bool shouldClose() const
	{
		return _close;
	}

	void setRenderer(SDL_Renderer * renderer);

};


#endif