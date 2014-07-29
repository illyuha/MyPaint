#ifndef I_GUI_OBSERVABLE
#define I_GUI_OBSERVABLE

#include "IGuiObserver.h"


class IGuiObservable
{
public:
	virtual ~IGuiObservable()
	{}
	virtual void notify() = 0;
	virtual void attachObserver(IGuiObserver *) = 0;

};


#endif