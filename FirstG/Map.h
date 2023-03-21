#pragma once

#include"Common.h"
#include"Base.h"

#define MAX_TILE 200
class TileMap :public Base
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class MapGame
{
public:
	MapGame() { ; }
	~MapGame() { ; }

	void LoadMap(std::string path);

	void LoadTile(SDL_Renderer* render);

	void BuildMap(SDL_Renderer* render);

	Map getMap() { return map_; }

	void SetMap(Map& mapData)
	{
		map_ = mapData;
	}

private:
	Map map_;
	TileMap tile_mat[MAX_TILE];
};