#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "UIElements.h"
#include "UIButton.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{	
	App->gui->AddBackground(0, 0, BACKGROUND, this);

	App->gui->AddElementText(896, 570, TEXT,this,"Account Name");
	MailBox=App->gui->AddElementTextBox(896, 600, TEXTBOX, this, "mail");

	App->gui->AddElementText(896, 700, TEXT, this, "Account Password");
	PaswordBox=App->gui->AddElementTextBox(896, 730, TEXTBOX, this, "pasword");

	App->gui->AddElementText(153, 1000, TEXT, this, "Version 2.0.12 (6546)(Release)");
	App->gui->AddElementText(65, 1025, TEXT, this, "Mar 30 2007");
	App->gui->AddElementText(1860/2, 1030, TEXT, this, "Copyright 2004-2007 Blizzard Entertainment. All Rights Reserved.");

	LogButton = App->gui->AddElementButton(896, 820, BUTTON, BUTTON_1, this, "Login");
	ManAccountButton=App->gui->AddElementButton(100, 850, BUTTON, BUTTON_1, this, "Manage Account");
	CommunityButton=App->gui->AddElementButton(100, 900, BUTTON, BUTTON_1, this, "Community Site");

	CinematicsButton=App->gui->AddElementButton(1590, 750, BUTTON, BUTTON_1, this, "Cinematics");
	CreditsButto=App->gui->AddElementButton(1590, 800, BUTTON, BUTTON_1, this, "Credits");
	TermsButton=App->gui->AddElementButton(1590, 850, BUTTON, BUTTON_1, this, "Terms of Use");
	QuitButton=App->gui->AddElementButton(1590, 1000, BUTTON, BUTTON_1, this, "Quit");

	windbut= App->gui->AddElementButton(100, 50, BUTTON, BUTTON_1, this, "window",true);
	winElements.add(windbut);
	windbut2 = App->gui->AddElementButton(100, 100, BUTTON, BUTTON_1, this, "window", true);
	winElements.add(windbut2);

	window_1 = App->gui->AddElementWindow(100, 200, WINDOWS, this, &winElements);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);
	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (window_1->show)
		{
			window_1->show = false;
			window_1->action = false;
		}
		else
		{
			window_1->show = true;
		}
	}


	
	p2SString title("World of Warcraft");

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		exit = false;

	return exit;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::GUIEvent(UIEvents eventType, UIElements* element)
{
	if (eventType == MOUSE_ENTER)
	{
		if (element == LogButton)
		{
			LogButton->Action();
		}
		if (element == ManAccountButton)
		{
			ManAccountButton->Action();
		}
		if (element == CommunityButton)
		{
			CommunityButton->Action();
		}
		if (element == CinematicsButton)
		{
			CinematicsButton->Action();
		}
		if (element == CreditsButto)
		{
			CreditsButto->Action();
		}
		if (element == TermsButton)
		{
			TermsButton->Action();
		}
		if (element == QuitButton)
		{
			QuitButton->Action();
		}
		if (element == windbut)
		{
			windbut->Action();
		}
	}
	
	if (eventType == MOUSE_LEAVE)
	{
		if (element == LogButton)
		{
			LogButton->Action();
		}
		if (element == ManAccountButton)
		{
			ManAccountButton->Action();
		}
		if (element == CommunityButton)
		{
			CommunityButton->Action();
		}
		if (element == CinematicsButton)
		{
			CinematicsButton->Action();
		}
		if (element == CreditsButto)
		{
			CreditsButto->Action();
		}
		if (element == TermsButton)
		{
			TermsButton->Action();
		}
		if (element == QuitButton)
		{
			QuitButton->Action();
		}
		if (element == windbut)
		{
			windbut->Action();
		}
	}
	if (eventType == MOUSE_CLICK)
	{
		if (element == LogButton)
		{
			LOG("CLICK!!");
		}
		if (element == ManAccountButton)
		{
			LOG("CLICK!!");
		}
		if (element == CommunityButton)
		{
			LOG("CLICK!!");
		}
		if (element == CinematicsButton)
		{
			LOG("CLICK!!");
		}
		if (element == CreditsButto)
		{
			LOG("CLICK!!");
		}
		if (element == TermsButton)
		{
			LOG("CLICK!!");
		}
		if (element == QuitButton)
		{
			exit = false;
		}
		if (element == MailBox)
		{
			MailBox->Action();
		}
		if (element == PaswordBox)
		{
			PaswordBox->Action();
		}
		if (element == window_1)
		{
			window_1->action = true;
		}
	}
	if (eventType == MOUSE_STOP_CLICK)
	{
		if (element == window_1)
		{
			if (window_1->show)
			{
				window_1->action = false;
			}
		}
	}

	return true;
}
