#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "UIElements.h"

class UIBackground:public UIElements
{
public:
	
	UIBackground(int x, int y, UIElementType type);
	~UIBackground();

	void Draw();

public:



};

#endif //__BACKGROUND_H__