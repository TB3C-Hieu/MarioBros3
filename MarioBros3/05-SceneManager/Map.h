#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <d3dx10.h>

#include "Utils.h"
#include "Layer.h"
#include "TileSet.h"
#include "tinyXML/tinyxml/tinyxml.h"
#include "GameObject.h"
#include "Game.h"
#include "debug.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class Map
{	
	
	//the cell count of the map
	int width, height;
	//the cell's width and height
	int tilewidth, tileheight;

	LPTILESET tilesets;

	std::vector<LPLAYER> layers;
public:
	Map();
	~Map();

	void AddTileSet(LPTILESET tileset);
	void AddLayer(LPLAYER layer);

	//FilePath is path to the file itself , Path = Path to storage area
	void LoadMapfromTMX(const char* FilePath, const char* Path);

	void Update(DWORD dt);
	void Render();

	void Unload();

	float getMapHeight();
	float getMapWidth();

	LPTILESET GetTilesetbyTileID(int ID);
};

#endif