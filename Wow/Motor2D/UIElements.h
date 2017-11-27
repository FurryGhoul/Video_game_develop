#ifndef __UIELEMENTS_H__
#define __UIELEMENTS_H__

#include "j1Gui.h"
#include "p2Point.h"

enum UIElementType
{
	BACKGROUND,
	TEXT,
	IMAGE,
	BUTTON
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

	uint size_x;
	uint size_y;

};

#endif// __UIELEMENTS_H__