#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while(item)
	{
		if(item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while(item)
	{
		if(item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	// north
	PathNode neighbor_1(-1, -1, { pos.x,pos.y + 1 }, this);
	if(App->pathfinding->IsWalkable(neighbor_1.pos))
		list_to_fill.list.add(neighbor_1);

	// south
	PathNode neighbor_2(-1, -1, { pos.x,pos.y -1 }, this);
	if(App->pathfinding->IsWalkable(neighbor_2.pos))
		list_to_fill.list.add(neighbor_2);

	// east
	PathNode neighbor_3(-1, -1, { pos.x+1,pos.y}, this);
	if(App->pathfinding->IsWalkable(neighbor_3.pos))
		list_to_fill.list.add(neighbor_3);

	// west
	PathNode neighbor_4(-1, -1, { pos.x-1,pos.y}, this);
	if(App->pathfinding->IsWalkable(neighbor_4.pos))
		list_to_fill.list.add(neighbor_4);

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	// TODO 1: if origin or destination are not walkable, return -1
	int ret=0;
	
	if (!IsWalkable(origin) || !IsWalkable(destination))
	{
		ret=-1;
	}
	
	// TODO 2: Create two lists: open, close
	PathList open, close;

	PathNode start(0, origin.DistanceTo(destination),origin, NULL);

	open.list.add(start);

	while (open.list.count() > 0)
	{
		p2List_item<PathNode>* aux;
		aux = open.GetNodeLowestScore();
		close.list.add(aux->data);
		open.list.del(aux);

		if (aux->data.pos == destination)
		{
			last_path.PushBack(aux->data.pos);
			while (aux != nullptr)
			{
				last_path.PushBack(aux->data.parent->pos);
				aux = aux->prev;
			}
			last_path.Flip();
			break;
		}

		PathList adjacent;
		aux->data.FindWalkableAdjacents(adjacent);

		for (uint i = 0; i < adjacent.list.count(); i++)
		{
			if (close.Find(adjacent.list[i].pos) == NULL)
			{
				adjacent.list[i].CalculateF(destination);

				if (open.Find(adjacent.list[i].pos) != NULL)
				{
					if (open.Find(adjacent.list[i].pos)->data.g > adjacent.list[i].g)
					{
						/*p2List_item<PathNode>* item = open.Find(adjacent.list[i].pos);
						item->data.parent = adjacent.list[i].parent;*/
						open.list.del(open.Find(adjacent.list[i].pos));
						open.list.add(adjacent.list[i]);
					}
				}
				else
				{
					open.list.add(adjacent.list[i]);
				}
			}
		}
	}	

	return ret;
}

