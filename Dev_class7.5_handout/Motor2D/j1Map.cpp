#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
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
	ResetBFS();

	return ret;
}

void j1Map::ResetBFS()
{
	frontier.Clear();
	visited.clear();
	came_from.clear();
	frontier.Push(iPoint(19, 4));
	visited.add(iPoint(19, 4));
}

void j1Map::PropagateBFS()
{
	// TODO 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors

	iPoint center;									//iPoint of the center node
	p2List<iPoint> neighbors;						//List of center's neighbors 
	p2List_item<iPoint>* item;						//item that points in the neighbor's list
	
	if (frontier.Count() != 0)
	{
		frontier.Pop(center);						//takes the data of the first element 
		LOG("X=%d Y=%d",center.x,center.y);			//of the queue and put it in the variable center
		
		for (int i = -1; i < 2; i=i+2)				//bucle that fills the neighbors
		{
			iPoint neighbor_vertical;
			iPoint neighbor_horizontal;

			neighbor_vertical.x = center.x;
			neighbor_vertical.y = center.y + i;
			neighbor_horizontal.x = center.x+i;
			neighbor_horizontal.y = center.y;

			neighbors.add(neighbor_vertical);
			neighbors.add(neighbor_horizontal);
		}
	}
	
	// TODO 2: For each neighbor, if not visited, add it
	// to the frontier queue and visited list
	for (item = neighbors.start; item; item = item->next)
	{
		if (visited.find(item->data) == -1)
		{
			if (IsWalkable(item->data.x, item->data.y) == true)
			{
				frontier.Push(item->data);
				visited.add(item->data);
			}
		}
	}
	
}

void j1Map::DrawBFS()
{
	iPoint point;

	// Draw visited
	p2List_item<iPoint>* item = visited.start;

	while(item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(26);

		SDL_Rect r = tileset->GetTileRect(26);
		iPoint pos = MapToWorld(point.x, point.y);

		App->render->Blit(tileset->texture, pos.x, pos.y, &r);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect r = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		App->render->Blit(tileset->texture, pos.x, pos.y, &r);
	}
	

	p2List_item<iPoint>* item_path = came_from.end;
	iPoint point_path;

	while (item_path)
	{
		point_path = item_path->data;
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect r = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point_path.x, point_path.y);

		App->render->Blit(tileset->texture, pos.x, pos.y, &r);

		item_path = item_path->prev;
	}
}

bool j1Map::IsWalkable(int x, int y) const
{
	// TODO 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)

	p2List_item<MapLayer*>* item;
	p2List_item<Properties::Property*>* layer_prop;

	/*if (x >= 0 && x < data.width && y >= 0 && y < data.height)
	{
		for (item = data.layers.start; item; item = item->next)
		{
			for (layer_prop = item->data->properties.list.start; layer_prop; layer_prop = layer_prop->next)
			{
				if (layer_prop->data->name == "Navigation" && layer_prop->data->value == 1)
				{
					if (item->data->Get(x, y) == 0)
					{
						return true;
					}
				}
			}
		}
	}*/

	if (x >= 0 && x < data.width && y >= 0 && y < data.height)
	{
		for (item = data.layers.start; item; item = item->next)
		{
			if (item->data->name == "Colisions")
				{
					if (item->data->Get(x, y) == 0)
					{
						return true;
					}
				}
			}
		}
	
	return false;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	p2List_item<MapLayer*>* item = data.layers.start;

	for(; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;

		if(layer->properties.Get("Nodraw") != 0)
			continue;

		for(int y = 0; y < data.height; ++y)
		{
			for(int x = 0; x < data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if(tile_id > 0)
				{
					TileSet* tileset = GetTilesetFromTileId(tile_id);

					SDL_Rect r = tileset->GetTileRect(tile_id);
					iPoint pos = MapToWorld(x, y);

					App->render->Blit(tileset->texture, pos.x, pos.y, &r);
				}
			}
		}
	}

	DrawBFS();
}

int Properties::Get(const char* value, int default_value) const
{
	p2List_item<Property*>* item = list.start;

	while(item)
	{
		if(item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return default_value;
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	p2List_item<TileSet*>* item = data.tilesets.start;
	TileSet* set = item->data;

	while(item)
	{
		if(id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tile_width;
		ret.y = y * data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tile_width * 0.5f);
		ret.y = (x + y) * (data.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0,0);

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tile_width;
		ret.y = y / data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		
		float half_width = data.tile_width * 0.5f;
		float half_height = data.tile_height * 0.5f;
		ret.x = int( (x / half_width + y / half_height) / 2);
		ret.y = int( (y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// Remove all layers
	p2List_item<MapLayer*>* item2;
	item2 = data.layers.start;

	while(item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	data.layers.clear();

	// Clean up the pugui tree
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

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for(layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if(ret == true)
			data.layers.add(lay);
	}

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		p2List_item<MapLayer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	LoadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if(layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for(pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool j1Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if(data != NULL)
	{
		pugi::xml_node prop;

		for(prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.add(p);
		}
	}

	return ret;
}

iPoint j1Map::GetMouseTile()
{
	int mouse_x;
	int mouse_y;
	iPoint tile;

	App->input->GetMousePosition(mouse_x, mouse_y);

	tile = WorldToMap(mouse_x-App->render->camera.x, mouse_y-App->render->camera.y);

	return tile;
}

void j1Map::PathToMouse()
{
	iPoint Goal;
	iPoint origin;
	p2List<iPoint> neighbors;


	Goal = GetMouseTile();

	while (frontier.Count() != 0)
	{
		frontier.Pop(origin);


		neighbors.add({ origin.x + 1, origin.y });
		neighbors.add({ origin.x - 1, origin.y });
		neighbors.add({ origin.x, origin.y + 1 });
		neighbors.add({ origin.x, origin.y - 1 });

		for (p2List_item<iPoint>*item = neighbors.start; item; item = item->next)
		{
			if (visited.find(item->data) == -1)
			{
				if (IsWalkable(item->data.x, item->data.y))
				{
					frontier.Push(item->data);
					visited.add(item->data);

					if (came_from.find(item->data) == -1)
					{
						came_from.add(origin);
						LOG("%d,%d",origin.x, origin.y);
					}
				}
			}
		}

		if (origin == Goal)
		{
			break;
		}
	}
}
