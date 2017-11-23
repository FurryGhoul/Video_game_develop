#ifndef __UIELEMENTS_H__
#define __UIELEMENTS_H__

#include "j1Gui.h"
#include "p2Point.h"

enum UIElementType
{
	TEXT,
	IMAGE
};

class UIElements:public j1Gui
{
public:
	
	UIElements(int x, int y, UIElementType type);
	~UIElements();

	virtual void Draw() {};

public:

	fPoint position;
	UIElementType type;

};

#endif// __UIELEMENTS_H__