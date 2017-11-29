#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "UITextBox.h"



UITextBox::UITextBox(int x, int y, UIElementType type, const char* text, j1Module* modul): UIElements(x,y,type,modul)
{
	if (text != nullptr)
	{
		HidenText = text;
		hidentexture = App->font->Print(text, { 70,70,70 }, App->gui->fonts[1]);
	}

	App->tex->GetSize(App->gui->textbox, size_x, size_y);
	App->tex->GetSize(hidentexture, sizeTx, sizeTy);

	scale = 2.0f;
}

UITextBox::~UITextBox()
{
}

void UITextBox::Draw()
{
	App->render->Blit(App->gui->textbox, position.x - App->render->camera.x-size_x/2*scale, position.y - App->render->camera.y,scale);
	
	if (hide == false)
	{
		App->render->Blit(hidentexture, position.x - App->render->camera.x - sizeTx / 1.5f, position.y - App->render->camera.y + sizeTy / 2, 1.5f);
	}

	HideText();
}

void UITextBox::HideText()
{
	bool inside = false;
	int x, y;

	App->input->GetMousePosition(x, y);

	int limit_xl = position.x - App->render->camera.x - (size_x / 2) * 2;
	int limit_xr = position.x - App->render->camera.x + (size_x / 2) * 2;
	int limit_yu = position.y - App->render->camera.y - (size_y / 2) * 2;
	int limit_yd = position.y - App->render->camera.y + (size_y / 2) * 2;


	if (x>limit_xl && x<limit_xr)
	{
		if (y > limit_yu && y < limit_yd)
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			{
				hide = true;
			}
		}
	}

	if (x<limit_xl || x>limit_xr || y < limit_yu || y > limit_yd)
	{
		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
		{
			hide = false;
		}
	}
}

