#ifndef __UITEXT_H__
#define __UITEXT_H__

#include "p2SString.h"
#include "UIElements.h"

class SDL_Texture;

class UIText:public UIElements
{
public:
	UIText(int x, int y, UIElementType type);
	~UIText();

	void Draw();

public:

	SDL_Texture*	texture;
	const char*		string;
	
};

#endif //__UITENT_H__

