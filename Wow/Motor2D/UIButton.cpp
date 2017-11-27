#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UIButton.h"



UIButton::UIButton(int x, int y, UIElementType type, ButtonType buttontype, const char* text):UIElements(x,y,type)
{
	if (text != nullptr)
	{
		buttontext = text;
		ButtonText=App->font->Print(buttontext, { 255, 255, 0 }, App->gui->fonts[1]);
		App->tex->GetSize(ButtonText, sizeTx, sizeTy);
	}
	
	btype = buttontype;
	ButtonTex = App->gui->buttons[0];

	App->tex->GetSize(ButtonTex, size_x, size_y);
}


UIButton::~UIButton()
{
}


void UIButton::Draw()
{
	if (btype == BUTTON_1)
	{
		App->render->Blit(ButtonTex, position.x - App->render->camera.x - size_x, position.y - App->render->camera.y - size_y / 2,2.0f);
		App->render->Blit(ButtonText, position.x - App->render->camera.x- sizeTx /2 , position.y - App->render->camera.y);
		
		if (Iluminate() == true)
		{
			App->render->Blit(App->gui->buttons[1], position.x - App->render->camera.x - size_x-12, position.y - App->render->camera.y - size_y / 2-12, 2.0f);
		}
	}

	Iluminate();

}

bool UIButton::Iluminate()
{
	bool ret = false;
	int x, y;
	
	App->input->GetMousePosition(x, y);
	
	int limit_xl = position.x - App->render->camera.x - (size_x / 2)*2;
	int limit_xr = position.x - App->render->camera.x + (size_x / 2)*2;
	int limit_yu = position.y - App->render->camera.y - (size_y / 2 )* 2;
	int limit_yd = position.y - App->render->camera.y + (size_y / 2) * 2;


	if (x>limit_xl && x<limit_xr)
	{
		if (y > limit_yu && y < limit_yd)
		{
			ret = true;
		}
	}
	
	return ret;
}