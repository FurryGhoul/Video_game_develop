#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;

struct _Mix_Music;
struct Mix_Chunk;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// TODO 1: Create methods to save and load
	// that can be called anytime, even if they 
	// will one execute by the very end of the frame
	// Load / Save

	//Call to Save modules
	const void Call_Save();

	//Call to Load modules
	const void Call_Load();


private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	//Call modules to star load (void to test it)
	void Load_Modules();

	//Call modules to star Save (void to test it)
	void Save_Modules();


public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;
	pugi::xml_document	config_file;
private:

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	
	pugi::xml_document  savegame;
	pugi::xml_node		config;
	pugi::xml_node		app_config;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	bool save = false;
	bool load = false;

};

extern j1App* App;

#endif