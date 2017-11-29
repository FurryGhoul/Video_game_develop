#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIButton.h"



UIButton::UIButton(int x, int y, UIElementType type, ButtonType buttontype, const char* text, j1Module* modul):UIElements(x,y,type,modul)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText=App->font->Print(buttontext, { 255, 255, 0 }, App->gui->fonts[1]);
		App->tex->GetSize(ButtonText, sizeTx, sizeTy);
	}
	
	btype = buttontype;
	ButtonTex = App->gui->buttons[0];
	scale = 2.0f;

	App->tex->GetSize(ButtonTex, size_x, size_y);

	int rect_x = position.x - (size_x / 2)*scale;
	int rect_y = position.y;

	Elementrect = { rect_x,rect_y,(int)size_x*(int)scale,(int)size_y*(int)scale };
	
}


UIButton::~UIButton()
{
}


void UIButton::Draw()
{
	if (btype == BUTTON_1)
	{
		App->render->Blit(ButtonTex, position.x - App->render->camera.x - size_x, position.y - App->render->camera.y,2.0f);
		App->render->Blit(ButtonText, position.x - App->render->camera.x- sizeTx /2 , position.y - App->render->camera.y+sizeTy/2);
		App->render->DrawQuad(Elementrect, 255, 0, 255, 80);
		
		if (Iluminate() == true)
		{
			App->render->Blit(App->gui->buttons[1], position.x - App->render->camera.x - size_x-12, position.y - App->render->camera.y-12, 2.0f);
		}
	}

	Iluminate();

}

bool UIButton::Iluminate()
{
	bool ret = false;
	int x, y;
	
	App->input->GetMousePosition(x, y);

	if (x>Elementrect.x && x<Elementrect.x+Elementrect.w)
	{
		if (y > Elementrect.y && y <Elementrect.y+Elementrect.h)
		{
			ret = true;
		}
	}
	
	return ret;
}