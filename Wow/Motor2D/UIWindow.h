#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "UIElements.h"

class UIWindow : public UIElements
{
public:

	UIWindow(int x, int y, UIElementType type, j1Module* modul, p2List<UIElements*>* elementslist );
	~UIWindow();

private:

	p2List<UIElements*>* windowelements;

};

#endif //__WINDOW_H__
