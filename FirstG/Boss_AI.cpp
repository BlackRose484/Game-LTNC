#include"Boss_AI.h"

Boss::Boss()
{
	frame_attack = 64;
}

Boss::~Boss()
{

}

bool Boss::LoadImage(std::string path, SDL_Renderer* render)
{
	int ret = Base::LoadImage(path, render);
	if (ret)
	{
		T_w = O_Rect.w / Boss_Frame;
		T_h = O_Rect.h;
	}
	return ret;
}


void Boss::Set_CLip_T()
{
	if (T_h > 0 && T_w > 0)
	{
		for (int i = 0; i < Boss_Frame; i++)
		{
			T_clip[i].x = i * T_w;
			T_clip[i].y = 0;
			T_clip[i].w = T_w;
			T_clip[i].h = T_h;
		}
	}
}

void Boss::show(SDL_Renderer* render)
{
	if (hp_threat > 0)
	{
		if(!is_attack)
		{
			O_Rect.x = x_pos - T_map_x;
			O_Rect.y = y_pos - T_map_y;

			frame++;
			frame = (frame >= 64) ? 0 : frame;
			SDL_Rect renderQ{ O_Rect.x,O_Rect.y,T_w,T_h };
			SDL_RenderCopyEx(render, OBJ, &T_clip[frame / 8], &renderQ, 0.0, NULL, T_flip);
		}
		else
		{
			O_Rect.x = x_pos - T_map_x;
			O_Rect.y = y_pos - T_map_y;

			frame_attack++;
			frame_attack = (frame_attack >= 128) ? 64 : frame_attack;
			SDL_Rect renderQ{ O_Rect.x,O_Rect.y,T_w,T_h };
			SDL_RenderCopyEx(render, OBJ, &T_clip[frame_attack / 8], &renderQ, 0.0, NULL, T_flip);
		}
	}
}