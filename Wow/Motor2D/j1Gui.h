#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "p2List.h"
#include "p2Log.h"
#include "j1Module.h"
#include "p2DynArray.h"


#define CURSOR_WIDTH 2

class SDL_Texture;
class SDL_Rect;
class UIElements;
enum UIElementType;
enum ButtonType;
class _TTF_Font;

// TODO 1: Create your structure of classes

// ---------------------------------------------------

class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	//bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	void AddBackground(int x, int y, UIElementType type);
	void AddElementText(int x, int y, UIElementType type, const char* text=nullptr);
	void AddElementTextBox(int x, int y, UIElementType type, const char* text = nullptr);
	void AddElementImage(int x, int y, UIElementType type, SDL_Rect* rect);
	void AddElementButton(int x, int y, UIElementType type, ButtonType btype, const char* text = nullptr);
	void DeleteElements(UIElements* element);


	SDL_Texture* GetAtlas() const;
	SDL_Texture* GetBackground() const;

public:

	p2List<UIElements*> elements;
	SDL_Texture* background=nullptr;
	SDL_Texture* textbox = nullptr;
	p2DynArray<_TTF_Font*> fonts;
	p2DynArray<SDL_Texture*> buttons;
	
private:

	SDL_Texture* atlas=nullptr;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__