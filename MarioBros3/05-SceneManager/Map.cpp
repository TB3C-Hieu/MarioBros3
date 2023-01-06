#include "Map.h"
#include <iostream>
Map::Map()
{
}

Map::~Map()
{
	Unload();
}

void Map::AddTileSet(LPTILESET tileset)
{
	this->tilesets = tileset;
}

void Map::AddLayer(LPLAYER layer)
{
	this->layers.push_back(layer);
}

void Map::LoadMapfromTMX(const char* FilePath, const char* Path)
{
	TiXmlDocument TMXdoc(FilePath);

	if (TMXdoc.LoadFile())
	{
		TiXmlElement* root = TMXdoc.RootElement();

		root->QueryIntAttribute("width", &this->width);
		root->QueryIntAttribute("height", &this->height);
		root->QueryIntAttribute("tilewidth", &this->tilewidth);
		root->QueryIntAttribute("tileheight", &this->tileheight);

		for (TiXmlElement* TMXtileset = root->FirstChildElement("tileset"); TMXtileset != NULL; TMXtileset = TMXtileset->NextSiblingElement("tileset"))
		{
			LPTILESET tileset = new TileSet(TMXtileset, Path);
			this->AddTileSet(tileset);

			//DebugOut(L"[INFO] load success tileset: %", tileset->getFirstgid());
		}

		for (TiXmlElement* TMXlayer = root->FirstChildElement("layer"); TMXlayer != NULL; TMXlayer = TMXlayer->NextSiblingElement("layer"))
		{
			LPLAYER layer = new Layer(TMXlayer);
			this->AddLayer(layer);

		}

	}
}

void Map::Update(DWORD dt)
{
}

//this funtion is ugly and may be refine // note: multilayer cast error need to be fixed
void Map::Render()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	int start_x, end_x;
	int start_y, end_y;
	start_x = int(cx) / 16;
	end_x = SCREEN_WIDTH / 16 + start_x +2;
	start_y = int(cy) / 16;
	end_y = SCREEN_HEIGHT / 16 + start_y + 2;
	for (int i = start_x; i < end_x; i++)
	{
		for (int j = start_y; j < end_y; j++)
		{
			int x = i * tilewidth;
			int y = j * tileheight;

			for (LPLAYER layer : layers)
			{
				int id = layer->GetTileID(i % width, j % height);
				if (id != 0)
				{
					tilesets->Draw(id - 1, x, y);
				}
			}
		}
	}
}

void Map::Unload()
{
	layers.clear();
}


float Map::getMapHeight()
{
	return this->height * this->tileheight;
}

float Map::getMapWidth()
{
	return this->width * this->tilewidth;
}

LPTILESET Map::GetTilesetbyTileID(int ID)
{
	return tilesets;
}
