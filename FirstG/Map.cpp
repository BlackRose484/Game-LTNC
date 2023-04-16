#include"Common.h"
#include"Map.h"

void MapGame::LoadMap(std::string path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path.c_str(), "rb");
	if (fp == NULL)
	{
		return;
	}
	map_.max_x = 0;
	map_.max_y = 0;
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &map_.tile[i][j]);
			int val = map_.tile[i][j];
			if (val > 0)
			{
				if (j > map_.max_x)
				{
					map_.max_x = j;
				}
				if (i > map_.max_y)
				{
					map_.max_y = i;
				}
			}
		}
	}

	map_.max_x = (map_.max_x + 1) * TILE_SIZE;
	map_.max_y = (map_.max_y + 1) * TILE_SIZE;

	map_.start_x = 0;
	map_.start_y = 0;

	fclose(fp);
}

void MapGame::LoadTile(SDL_Renderer* render)
{
	char file_img[30];
	FILE* fp = NULL;
	for (int i = 0; i < MAX_TILE; i++)
	{
		sprintf_s(file_img, "map//images//img (%d).png", i);

		fopen_s(&fp, file_img, "rb");

		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);

		tile_mat[i].LoadImage(file_img, render);
	}
}

void MapGame::BuildMap(SDL_Renderer* render)
{
	int x1(0), x2(0);
	int y1(0), y2(0);

	int map_x = 0;
	int map_y = 0;

	map_x = map_.start_x / TILE_SIZE;
	x1 = (map_.start_x % TILE_SIZE) * -1;
	x2 = x1 + WIDTH + ((x1 == 0) ? 0 : TILE_SIZE);

	map_y = map_.start_y / TILE_SIZE;
	y1 = (map_.start_y % TILE_SIZE) * -1;
	y2 = y1 + HEIGHT + ((y1 == 0) ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = map_.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = map_.tile[map_y][map_x];
			if (val > 0)
			{
				tile_mat[val].setRect(j, i);
				tile_mat[val].Render(render);
			}
			map_x++;
		}
		map_y++;
	}
}
