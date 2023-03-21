#pragma once

#include"Base.h"
#include"Common.h"
#include"Threat.h"

#define Boss_Frame 16
#define Boss_Speed 8

class Boss : public Threat
{
private:
	int frame_attack;
public:

	Boss();

	~Boss();

	bool LoadImage(std::string path, SDL_Renderer* render);

	void Set_CLip_T();

	void show(SDL_Renderer*render);
};
