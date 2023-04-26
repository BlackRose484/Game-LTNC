#pragma once

#include"Base.h"
#include"Common.h"
#include"Bullet.h"

#define N_Pet_Frame 8
#define Pet_Speed 4

class Pet :public Base
{
private:
	int x_pos;
	int y_pos;

	int x_val;
	int y_val;

	int x_map;
	int y_map;

	int pet_w;
	int pet_h;

	bool is_attack;

	int n_frame;
	int n_frame_attack;
	int pet_frame_attack;
	int pet_frame;
	double rolate_angle;

	SDL_RendererFlip pet_flip;

	SDL_Rect pet_clip[20];

	std::vector<Bullet*> list_bullet;

	Uint32 CurrentTime;
	Uint32 LastTime;

public:
	Pet();
	~Pet();

	int GetXPos() { return x_pos; };

	int GetYPos() { return y_pos; };

	void SetPos(const int& x, const int& y) { x_pos = x; y_pos = y; };

	void SetMap(const int& x, const int& y) { x_map = x, y_map = y; };

	void Set_N_frame(const int& x) { n_frame = x; };

	void Set_N_frame_attack(const int& x) { n_frame_attack = x; pet_frame_attack = n_frame*8; };

	void SetAttack(const bool& x) { is_attack = x; };

	void SetPetFlip(SDL_RendererFlip x) { pet_flip = x; };

	std::vector<Bullet*> GetBullet() { return list_bullet; };

	bool LoadImage(std::string path, SDL_Renderer* render);

	void PetMove(const int &x,const int &y);

	void LoadBullet(SDL_Renderer* render, int PoNx, int PoNy);

	void PetShot(SDL_Renderer* render, Map& map_);

	void SetClip();

	void Show(SDL_Renderer* render);
	
	void SetRolateAngle(const double& x) { rolate_angle = x; };

	void Remove_Bullet(const int& idx);
};
