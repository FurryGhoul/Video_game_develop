#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		FillMap(map_file);
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

void j1Map::FillMap(const pugi::xml_document& document) {

	pugi::xml_node aux_node = document.child("map");

	first_map.orientation = String_to_Enum_2(aux_node.attribute("orientation").as_string());
	LOG("orientation --> %d", first_map.orientation);
	first_map.renderorder = String_to_Enum_1(aux_node.attribute("renderorderer").as_string());
	LOG("Renderorder --> %d", first_map.renderorder);
	first_map.width = aux_node.attribute("width").as_uint();
	LOG("width --> %d", first_map.width);
	first_map.height = aux_node.attribute("height").as_uint();
	LOG("height --> %d", first_map.height);
	first_map.tilewidth = aux_node.attribute("tilewidth").as_uint();
	LOG("tilewidth --> %d", first_map.tilewidth);
	first_map.tileheight = aux_node.attribute("tileheight").as_uint();
	LOG("tileheight --> %d", first_map.tileheight);
	first_map.nextobject = aux_node.attribute("nextobjectid").as_uint();
	LOG("nextobject --> %d", first_map.nextobject);


	

	
}

Map_renderorder j1Map::String_to_Enum_1(p2SString str) {
	
	if (str == "right-down")
		return right_down;

	if (str == "right-up")
		return right_up;

	if (str == "left-down")
		return left_down;

	if (str == "left-up")
		return left_up;
}

Map_Orientation j1Map::String_to_Enum_2(p2SString str) {
	
	if (str == "orthogonal")
		return orthogonal;

	if (str == "isometric")
		return isometric;

	if (str == "staggered")
		return staggered;

	if (str == "hexagonal")
		return hexagonal;

}