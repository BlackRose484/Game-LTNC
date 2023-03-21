#include"Common.h"
#include"Game_Utis.h"

using namespace std;

string convert_to_string(int number)
{
    stringstream ss;
    ss << setw(5) << setfill(' ') << number;
    string val_score;
    ss >> val_score;
    return val_score;
}
// apply for health
std::string convert_to_String(int health)
{
    stringstream ss;
    ss << setw(4) << setfill('0') << health;
    string val_score;
    ss >> val_score;
    val_score = val_score;
    return val_score;
}

int get_from_file(const char* path)
{
    int x;
    std::ifstream file(path);
    string value;
    file >> value;
    x = std::stoi(value);

    return x;
}

void update(const char* path, int& new_value)
{
    std::ofstream file(path);
    file << new_value;

}

std::vector<Threat*> Create_Threat(SDL_Renderer* gRender)
{
	std::vector<Threat*> list_Threat;


	Threat* T_Static = new Threat[50];
	for (int i = 0; i < 50; i++)
	{
		Threat* T_new = T_Static + i;
		if (T_new != NULL)
		{
			T_new->Set_N_frame(8);
			T_new->LoadImage("img//Threat//threat.png", gRender);
			T_new->Set_T_pos(i * 400 + 1000, i * 400 + 100);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(500);

			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);

			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Threat.push_back(T_new);
		}
	}

	Threat* T_K = new Threat[10];
	for (int i = 0; i < 10; i++)
	{
		Threat* T_new = T_K + i;
		if (T_new != NULL)
		{
			T_new->Set_N_frame(5);
			T_new->Set_N_frame_attack(11);
			T_new->LoadImage("img//Threat//T_wolf.png", gRender);
			T_new->Set_T_pos(i * 300 + 500, i * 500 + 300);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(200);


			T_new->Set_T_dir_move(1);
			T_new->Set_T_move(1);
			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);
			T_new->Set_T_Dis_move(left, right);


			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Threat.push_back(T_new);
		}
	}

	Threat* T_Snail = new Threat[10];
	for (int i = 0; i < 10; i++)
	{
		Threat* T_new = T_Snail + i;
		if (T_new != NULL)
		{
			T_new->Set_N_frame(8);
			T_new->LoadImage("img//Threat//snail_threat.png", gRender);
			T_new->Set_T_pos(i * 700 + 1500, i * 600 + 1630);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(50);


			T_new->Set_T_dir_move(1);
			T_new->Set_T_move(1);
			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);
			T_new->Set_T_Dis_move(left, right);


			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Threat.push_back(T_new);
		}
	}

	Threat* T_Bee = new Threat[100];
	for (int i = 0; i < 100; i++)
	{
		Threat* T_new = T_Bee + i;
		if (T_new != NULL)
		{

			T_new->Set_N_frame(8);
			T_new->LoadImage("img//Threat//bee_threat.png", gRender);
			T_new->Set_T_pos(i * 1000 + 1500, i * 200 + 1800);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(100);


			T_new->Set_T_dir_move(1);
			T_new->Set_T_move(1);
			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);
			T_new->Set_T_Dis_move(left, right);


			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Threat.push_back(T_new);
		}
	}

	Threat* T_Dragon = new Threat[10];
	for (int i = 0; i < 10; i++)
	{
		Threat* T_new = T_Dragon + i;
		if (T_new != NULL)
		{

			T_new->Set_N_frame(16);
			T_new->LoadImage("img//Threat//T_Dragon.png", gRender);
			T_new->Set_T_pos(i * 750 + 900, i * 400 + 1900);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(400);


			T_new->Set_T_dir_move(1);
			T_new->Set_T_move(1);
			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);
			T_new->Set_T_Dis_move(left, right);

			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Threat.push_back(T_new);
		}
	}


	return list_Threat;
}


std::vector<Boss*> Create_Boss(SDL_Renderer* gRender)
{
	std::vector<Boss*> list_Boss;

	Boss* T_Dragon = new Boss[10];
	for (int i = 0; i < 10; i++)
	{
		Boss* T_new = T_Dragon + i;
		if (T_new != NULL)
		{
			T_new->LoadImage("img//Threat//T_dragon.png", gRender);
			T_new->Set_T_pos(800+200*i, 200*i);
			T_new->Set_CLip_T();
			T_new->Set_Hp_Threat(400);


			T_new->Set_T_dir_move(1);
			T_new->Set_T_move(1);

			int left = T_new->get_T_x_pos() - 200;
			int right = T_new->get_T_x_pos() + 200;
			T_new->set_Area(left - 300, right + 300);
			T_new->Set_T_Dis_move(left, right);

			Bullet* T_bullet = new Bullet;
			T_bullet->LoadImage("img//Threat//shot.png", gRender);
			T_new->T_Load_Bullet(T_bullet, gRender);

			list_Boss.push_back(T_new);
		}
	}
	return list_Boss;
}