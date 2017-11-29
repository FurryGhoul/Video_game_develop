#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIText.h"


UIText::UIText(int x, int y, UIElementType type, const char* text, j1Module* modul):UIElements(x,y,type,modul)
{
	string = text;
	texture=App->font->Print(string, { 255,255,0}, App->gui->fonts[0]);
	BlackBackground = App->font->Print(string, { 0,0,0 }, App->gui->fonts[0]);
	App->tex->GetSize(texture, size_x, size_y);
}

UIText::~UIText()
{
}

void UIText::Draw()
{
	App->render->Blit(BlackBackground, position.x - App->render->camera.x - size_x / 2 + 2, position.y - App->render->camera.y+2- size_y / 2);
	App->render->Blit(texture, position.x-App->render->camera.x- size_x /2, position.y- App->render->camera.y- size_y /2);
}
