#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIWindow.h"



UIWindow::UIWindow(int x, int y, UIElementType type, j1Module* modul,p2List<UIElements*>* elementslist):UIElements(x,y,type,modul)
{

}


UIWindow::~UIWindow()
{
}
