#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "UIText.h"
#include "j1Fonts.h"


UIText::UIText(int x, int y, UIElementType type, const char* text):UIElements(x,y,type)
{
	string = text;
	texture=App->font->Print(string, { 255,255,255 }, 0);
	App->tex->GetSize(texture, text_width, text_height);
}

UIText::~UIText()
{
}

void UIText::Draw()
{
	App->render->Blit(texture, position.x-App->render->camera.x-text_width/2, position.y- App->render->camera.y-text_height/2);
	LOG("KHBKBNK");
}
