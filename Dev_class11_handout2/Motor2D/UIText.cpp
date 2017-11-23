#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "UIText.h"
#include "j1Fonts.h"
#include "j1Render.h"


UIText::UIText(int x, int y, UIElementType type):UIElements(x,y,type)
{
	string = "Hola que tal";
	texture=App->font->Print(string, { 255,0,0 }, 0);
}

UIText::~UIText()
{
}

void UIText::Draw()
{
	App->render->Blit(texture, position.x-App->render->camera.x, position.y- App->render->camera.y);
	LOG("KHBKBNK");
}
