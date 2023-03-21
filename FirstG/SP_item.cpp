#include"Common.h"
#include"Base.h"
#include"SP_item.h"

HP::HP()
{
	hp_w = 0;
	hp_h = 0;

	lv_HP = 0;
}

HP::~HP()
{

}

bool HP::LoadHP(std::string path, SDL_Renderer* render)
{
	SDL_Surface* O_sur = IMG_Load(path.c_str());
	if (O_sur == NULL)return 0;
	else
	{
		SDL_SetColorKey(O_sur, SDL_TRUE, SDL_MapRGB(O_sur->format, 0, 0, 0));
		OBJ = SDL_CreateTextureFromSurface(render, O_sur);
		if (OBJ == NULL)return 0;
		else
		{
			hp_w = O_sur->w;
			hp_h = O_sur->h/N_HP;
		}
		SDL_FreeSurface(O_sur);
	}
	return OBJ != NULL;
}

void HP::Set_HP_clip()
{
	if (hp_w > 0 && hp_h > 0)
	{
		for (int i = 0; i < N_HP; i++)
		{
			HP_clip[i].x = 0;
			HP_clip[i].y = i * hp_h;
			HP_clip[i].w = hp_w;
			HP_clip[i].h = hp_h;
		}
	}
}

void HP::HP_Show(SDL_Renderer* render)
{
	SDL_Rect RenderQ{ O_Rect.x,O_Rect.y,hp_w,hp_h };
	SDL_RenderCopy(render, OBJ, &HP_clip[lv_HP], &RenderQ);
}

///Clock/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Clock::Clock()
{
	clock_h = 0;
	clock_w = 0;
	frame = 0;
}

Clock::~Clock()
{

}

bool Clock::Load_Clock(std::string path, SDL_Renderer* render)
{
	int ret = Base::LoadImage(path, render);
	if (ret)
	{
		clock_w = O_Rect.w / N_Clock;
		clock_h = O_Rect.h;
	}
	return ret;
}

void Clock::Set_Clock_Clip()
{
	if (clock_w > 0 && clock_h > 0)
	{
		for (int i = 0; i < N_Clock; i++)
		{
			Clock_clip[i].x = i * clock_w;
			Clock_clip[i].y = 0;
			Clock_clip[i].w = clock_w;
			Clock_clip[i].h = clock_h;
		}
	}
}

void Clock::Clock_Show(SDL_Renderer* render)
{
	frame++;
	frame = (frame >= 64) ? 0 : frame;
	SDL_Rect RenderQ{ O_Rect.x,O_Rect.y,clock_w,clock_h };
	SDL_RenderCopy(render, OBJ, &Clock_clip[frame/8], &RenderQ);
}

///Fire/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Fire::Fire()
{
	frame = 0;
	fire_w = 0;
	fire_h = 0;
}

Fire::~Fire()
{

}

bool Fire::Load_Fire(std::string path, SDL_Renderer* render)
{
	SDL_Surface* O_sur = IMG_Load(path.c_str());
	if (O_sur == NULL)return 0;
	else
	{
		SDL_SetColorKey(O_sur, SDL_TRUE, SDL_MapRGB(O_sur->format, 255, 255, 255));
		OBJ = SDL_CreateTextureFromSurface(render, O_sur);
		if (OBJ == NULL)return 0;
		else
		{
			fire_w = O_sur->w/N_Fire;
			fire_h = O_sur->h;
		}
		SDL_FreeSurface(O_sur);
	}
	return OBJ != NULL;
}

void Fire::set_Fire_Clip()
{
	if (fire_w > 0 && fire_h > 0)
	{
		for (int i = 0; i < N_Fire; i++)
		{
			Fire_clip[i].x = i*fire_w;
			Fire_clip[i].y = 0;
			Fire_clip[i].w = fire_w;
			Fire_clip[i].h = fire_h;
		}
	}
}

void Fire::Fire_Show(SDL_Renderer* render)
{
	O_Rect.x = x_pos - map_x;
	O_Rect.y = y_pos - map_y;
	frame++;
	frame = (frame >= 56) ? 0 : frame;
	SDL_Rect RenderQ{ O_Rect.x,O_Rect.y,fire_w,fire_h };
	SDL_RenderCopy(render, OBJ, &Fire_clip[frame / 8], &RenderQ);
}