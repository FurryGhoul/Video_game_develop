#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
enum UIElementType;
class UIWindow;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool GUIEvent(UIEvents eventType, UIElements* element);

private:
	
	SDL_Texture* debug_tex = nullptr;
	
	GuiImage* banner = nullptr;
	
	GuiText* text = nullptr;

	UIElements* MailBox=nullptr;
	UIElements* PaswordBox = nullptr;
	UIElements* LogButton = nullptr;
	UIElements* ManAccountButton = nullptr;
	UIElements* CommunityButton = nullptr;
	UIElements* CinematicsButton = nullptr;
	UIElements* CreditsButto = nullptr;
	UIElements* TermsButton = nullptr;
	UIElements* QuitButton = nullptr;
	UIElements* windbut = nullptr;
	UIElements* windbut2 = nullptr;
	UIElements* window_1 = nullptr;
	UIElements* window_2 = nullptr;

	p2List<UIElements*> winElements;

	bool		exit = true;

};

#endif // __j1SCENE_H__