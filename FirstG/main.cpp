//FG

#include"Common.h"
#include"Base.h"
#include"Threat.h"
#include"Map.h"
#include"Player.h"
#include"Text.h"
#include"SP_item.h"
#include"Menu.h"
#include"Time.h"
#include"Boss_AI.h"
#include"Button.h"
#include"Game_Utis.h"
#include"Pet.h"

int hp_player;
int dame_player;
int money;
int have_pet;
int dame_pet;

int plus_hp = 1;
int plus_dame = 5;
int volume = 50;
int volume_chunk = 50;
int temp_volume = 0;
int plus_dame_pet = 5;

int cost_plus_hp = 100;
int cost_plus_dame = 100;
int cost_pet = 2000;
int cost_plus_dame_pet = 200;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("hello game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRender == NULL)
			{
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
				{
					success = false;
				}
			}
		}
	}
	return success;
}

void close()
{
	SDL_DestroyRenderer(gRender);
	SDL_DestroyWindow(gWindow);
	gRender = NULL;
	gWindow = NULL;

	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
}


int main(int arc, char* argv[])
{
	 
	hp_player = get_from_file("Update//hp_player.txt");
	dame_player = get_from_file("Update//dame_player.txt");
	money = get_from_file("Update//money.txt");
	have_pet = get_from_file("Update//have_pet.txt");
	dame_pet = get_from_file("Update//dame_pet.txt");

	if (!init())
	{
		std::cout << "Cant Init" << SDL_GetError;
		return 0;
	}
	else
	{
		//Set Font and Music
		gFont = TTF_OpenFont("font//Neverwinter.ttf", 40);
		gMusic = Mix_LoadMUS("sound//sound1.mp3");
		gChunk = Mix_LoadWAV("asset//sound_effect//switch.wav");
		gChunk1 = Mix_LoadWAV("asset//sound_effect//upgrade_sound_effect.wav");
		chunk_win = Mix_LoadWAV("sound//victory.wav");
		chunk_death = Mix_LoadWAV("sound//complete.wav");
		Mix_PlayMusic(gMusic, -1);
		Mix_VolumeMusic(volume);
		SDL_Color gColor = { 0,0,0,255 };


		//Map
		MapGame map;
		map.LoadMap("map//vip1.txt");
		map.LoadTile(gRender);
		Map k = map.getMap();
		Base bg;
		bg.LoadImage("map//bg.png", gRender);

		//Player 
		Player ex;
		ex.LoadImage("img//Player//right1.png", gRender);
		ex.SetClip();
		ex.setPos(200, 300);

		//Pet
		Pet pet;
		pet.Set_N_frame(8);
		pet.Set_N_frame_attack(10);
		pet.LoadImage("img//Threat//Pet.png", gRender);
		pet.SetAttack(0);
		pet.SetClip();
		pet.SetPos(100, 200);

		//Threat
		std::vector<Threat*> list_Threat = Create_Threat(gRender);

		//Player name
		Text name;		
		//Player score
		Text score;
		//Time
		Text time;
		Time time_game;

		
		//LText name_;
		std::stringstream Name;
		
		//HP Player
		HP HP_player;
		int hp = 0;	
		HP_player.LoadHP("img//Player//hp.png", gRender);
		HP_player.Set_HP_clip();
		HP_player.setRect(0, 0);

		//Clock game
		Clock g_clock;
		g_clock.Load_Clock("img//SP_item//clock.png", gRender);
		g_clock.Set_Clock_Clip();
		g_clock.setRect(WIDTH / 2, HEIGHT / 2);

		//Fire
		Fire g_fire;
		g_fire.Load_Fire("img//SP_item//fire1.png", gRender);
		g_fire.set_Fire_Clip();
		g_fire.set_fire_pos(-900, 900);

		Fire g_fire_p;
		g_fire_p.Load_Fire("img//SP_item//fire.png", gRender);
		g_fire_p.set_Fire_Clip();
		g_fire_p.set_fire_pos(-900, 900);

		//Init game
		bool q = 0;


		//Init menu 
		Base Frame_Menu;
		Frame_Menu.LoadImage("img//Menu//Button//frame_menu.png", gRender);
		Frame_Menu.setRect(WIDTH/2-Frame_Menu.getRect().w/2, HEIGHT/2-Frame_Menu.getRect().h/2);

		bool hello_game = 1;
		bool play = false;
		bool play1 = false;
		bool menu = true;
		bool quitMenu = false;
		bool exitGame = false;
		bool howToPlay = false;
		bool upgrade = false;
		bool option = false;
		bool play_again = false;
		bool select_map = false;
		bool setting = false;
		bool win = false;
		bool lose = false;
		bool mute = false;
		bool back_to_game = false;

		//Some Button For Game
		Button Play_Button;
		Button Help_Button;
		Button Get_Back_Button;
		Button Update_Button;
		Button Option_Button;
		Button Play_Again_Button;
		Button Menu_Button;
		Button Next_Button;
		Button Select_Map_Button;
		Button Map[2];
		Button Quit;
		Button Quit_Menu;
		Button Setting;
		Button IncreaseVolume_;
		Button IncreaseVolumeChunk;
		Button DecreaseVolume_;
		Button DecreaseVolumeChunk;
		Button Update_Player_HP;
		Button Update_Player_Dame;
		Button Mute_;
		Button Back_To_Game;
		Button Unlock_Pet;
		Button Update_Pet_Dame;

		//Text
		Text Cur_Hp;
		Text Cur_Attack;
		Text Cur_Money;
		Text Cur_Pet_Dame;

		//Help Game
		Base Help[8];
		Help[0].LoadImage("img//Menu//help1.png", gRender, 1, 3, 5);
		Help[1].LoadImage("img//Menu//help2.png", gRender, 1, 3, 5);
		Help[2].LoadImage("img//Menu//help3.png", gRender, 1, 3, 5);
		Help[3].LoadImage("img//Menu//help4.png", gRender, 1, 3, 5);
		Help[4].LoadImage("img//Menu//help5.png", gRender, 1, 3, 5);
		Help[5].LoadImage("img//Menu//help6.png", gRender, 1, 3, 5);
		Help[6].LoadImage("img//Menu//help7.png", gRender, 1, 3, 5);
		Help[7].LoadImage("img//Menu//help8.png", gRender, 1, 3, 5);

		int idx_help = 0;

		Base Loading[4];
		Loading[0].LoadImage("img//Menu//loading0.png", gRender, 1, 3, 5);
		Loading[1].LoadImage("img//Menu//loading1.png", gRender, 1, 3, 5);
		Loading[2].LoadImage("img//Menu//loading2.png", gRender, 1, 3, 5);
		Loading[3].LoadImage("img//Menu//loading3.png", gRender, 1, 3, 5);

		Base HelloGame;
		HelloGame.LoadImage("img//Menu//hello_game.png", gRender, 1, 3, 5);

		Base Menu_bg;
		Menu_bg.LoadImage("img//Menu//menu.jpg", gRender, 1, 3, 5);

		Base shadow;
		shadow.LoadImage("img//Player//shadow.png", gRender);

		Base Update_player;
		Update_player.LoadImage("Update//update_kinght.png", gRender, 1, 2, 3);
		Update_player.setRect(WIDTH / 2 - Update_player.getRect().w-100, HEIGHT / 2 - Update_player.getRect().h / 2);

		Base Update_Pet;
		Update_Pet.LoadImage("Update//update_pet.png", gRender, 1, 2, 3);
		Update_Pet.setRect(WIDTH / 2 + 100, HEIGHT / 2 - Update_Pet.getRect().h / 2);

		Base Setting_base;
		Setting_base.LoadImage("Update//setting.png", gRender, 1, 2, 3);
		Setting_base.setRect(WIDTH / 2 - Setting_base.getRect().w / 2, HEIGHT / 2 - Setting_base.getRect().h / 2);

		Base Mini_map;
		Mini_map.LoadImage("map//minimap.png", gRender);
		Mini_map.setRect(0, HEIGHT - 150);

		Base Locate;
		Locate.LoadImage("map//locate.png", gRender);

		Base Money;
		Money.LoadImage("img//SP_item//money.png", gRender);

		int detect_x = INT_MAX;
		int detect_y = INT_MAX;
		int kc = 1e9;
		int PoNx = 1;
		int PoNy = 1;

		//Game Loop
		while (!q)
		{   
			if (hello_game)
			{
				int t = 0;
				while (t <= LOADING)
				{
					HelloGame.Render(gRender);
					SDL_RenderPresent(gRender);
					t++;
				}
				hello_game = false;
			}

			if (menu)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = 1;
					}
					Play_Button.HandlePlay(e, gRender, menu, play, quitMenu, gChunk);
					Help_Button.HandleHowToPlayButton(e, gRender, menu, play, quitMenu, howToPlay, gChunk);
					//Select_Map_Button.SelectMapButton(e, gRender, menu, play, quitMenu, select_map, gChunk);
					Setting.HandleSetting(e, gRender, menu, play, quitMenu, setting, gChunk);
					Update_Button.HandleUpgradeButton(e, gRender, menu, play, howToPlay, upgrade, gChunk);
					Quit_Menu.HandleQuitMenu(e, gRender, menu, play, q, gChunk);
				}

				SDL_SetRenderDrawColor(gRender, 100, 100, 0, 100);
				SDL_RenderClear(gRender);

				Menu_bg.LoadImage("img//Menu//menu.jpg", gRender, 1, 3, 5);
				Menu_bg.Render(gRender);

				Play_Button.setRect(100, 100);
				Play_Button.Render(gRender);

				Help_Button.setRect(100, 200);
				Help_Button.Render(gRender);
			
				//Select_Map_Button.setRect(100, 300);
				//Select_Map_Button.Render(gRender);

				Setting.setRect(100, 300);
				Setting.Render(gRender);

				Update_Button.setRect(100, 400);
				Update_Button.Render(gRender);

				Quit_Menu.setRect(100, 500);
				Quit_Menu.Render(gRender);

				

				SDL_RenderPresent(gRender);
			}

			while (howToPlay)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = true;
						howToPlay = 0;

					}

					Get_Back_Button.HandleGetBackButton(e, gRender, menu, play, quitMenu, howToPlay, upgrade,setting,gChunk);
					Next_Button.NextButton(e, gRender, idx_help, gChunk);
				}
				SDL_SetRenderDrawColor(gRender, 100, 100, 0, 100);
				SDL_RenderClear(gRender);

				Menu_bg.Render(gRender);


				Help[idx_help].setRect(0, 0);
				Help[idx_help].Render(gRender);
				
				Get_Back_Button.setRect(10, 10);
				Get_Back_Button.Render(gRender);

				Next_Button.setRect(WIDTH-Next_Button.get_button_w(), HEIGHT/2-Next_Button.get_button_h()/2);
				Next_Button.Render(gRender);

				SDL_RenderPresent(gRender);
			}

			idx_help = 0;
			bool map1 = 0, map2 = 0;

			if(select_map)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = true;
						select_map = 0;
					}
					Get_Back_Button.HandleGetBackButton(e, gRender, menu, play, quitMenu, select_map, upgrade,setting, gChunk);
					Map[0].ChooseMap1(e, gRender, menu, play, quitMenu, map1,select_map, gChunk);
					Map[1].ChooseMap1(e, gRender, menu, play, quitMenu, map2,select_map, gChunk);
				}
				if (map1)
				{
					map.LoadMap("map//vip1.txt");
					map.LoadTile(gRender);
					Menu_bg.LoadImage("img//Menu//menu.jpg", gRender, 1, 3, 5);
					k = map.getMap();
				}
				else if (map2)
				{
					map.LoadMap("map//Map_New//map_new.txt");
					map.LoadTile(gRender);
					Menu_bg.LoadImage("img//Menu//bg2.jpeg", gRender, 1, 3, 5);
					k = map.getMap();
				}
				Get_Back_Button.setRect(100, 200);
				Map[0].setRect(100, 300);
				Map[1].setRect(500, 300);

				Menu_bg.Render(gRender);
				Get_Back_Button.Render(gRender);
				Map[0].Render(gRender);
				Map[1].Render(gRender);

				SDL_RenderPresent(gRender);
			}

			if (upgrade)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = 1;
					}
					if(have_pet)
					{
						Update_Pet_Dame.HandleUpgrade(e, gRender, cost_plus_dame_pet, dame_pet, plus_dame_pet, money, gChunk1);
						
					}
					else
					{
						Unlock_Pet.UnlockPet(e, gRender,cost_pet, have_pet, money, gChunk1);
					}
					Update_Player_HP.HandleUpgrade(e, gRender, cost_plus_hp, hp_player, plus_hp, money, gChunk1);
					Update_Player_Dame.HandleUpgrade(e, gRender, cost_plus_hp, dame_player, plus_dame, money, gChunk1);
					Get_Back_Button.HandleGetBackButton(e, gRender, menu, play, quitMenu, howToPlay, upgrade,setting, gChunk);
				}
				
				SDL_SetRenderDrawColor(gRender, 0, 0, 0, 255);
				SDL_RenderClear(gRender);

				Menu_bg.LoadImage("img//Menu//upgrade_background.png", gRender);
				Menu_bg.Render(gRender);

				Update_player.Render(gRender);

				SDL_Color Color = { 255,255,255,255 };

				//Update Player
				Cur_Hp.setColor(Color);
				Cur_Attack.setColor(Color);
				Cur_Money.setColor(Color);
				Cur_Pet_Dame.setColor(Color);

				Cur_Hp.setText(convert_to_String(hp_player));
				Cur_Hp.LoadText(gFont, gRender);
				Cur_Hp.setRect(425, 345);
				Cur_Hp.Render(gRender);

				Cur_Attack.setText(convert_to_string(dame_player));
				Cur_Attack.LoadText(gFont, gRender);
				Cur_Attack.setRect(465, 420);
				Cur_Attack.Render(gRender);

				Cur_Money.setText(convert_to_string(money));
				Cur_Money.LoadText(gFont, gRender);
				Cur_Money.setRect(WIDTH-Cur_Money.getRect().w-25, 10);
				Cur_Money.Render(gRender);


				Money.setRect(WIDTH - Cur_Money.getRect().w-75, 10);
				Money.Render(gRender);
				
				
				Update_Player_HP.setRect(530, 340);
				Update_Player_HP.Render(gRender);

				Update_Player_Dame.setRect(530, 420);
				Update_Player_Dame.Render(gRender);



				if(!have_pet)
				{
					Unlock_Pet.setRect(WIDTH / 2 + 100, HEIGHT / 2 - Update_Pet.getRect().h / 2);
					Unlock_Pet.Render(gRender);
				}
				else
				{
					Update_Pet.Render(gRender);

					Update_Pet_Dame.setRect(1355, 421);
					Update_Pet_Dame.Render(gRender);

					Cur_Pet_Dame.setText(convert_to_String(dame_pet));
					Cur_Pet_Dame.LoadText(gFont, gRender);
					Cur_Pet_Dame.setRect(1274, 425);
					Cur_Pet_Dame.Render(gRender);
				}

				Get_Back_Button.setRect(10, 10);
				Get_Back_Button.Render(gRender);

				SDL_RenderPresent(gRender);
			}

			if (setting)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = true;
					}
					Get_Back_Button.HandleGetBackButton(e, gRender, menu, play, quitMenu, howToPlay, upgrade,setting, gChunk);
					IncreaseVolume_.IncreaseVolume(e, gRender, volume, gChunk);
					IncreaseVolumeChunk.IncreaseVolumeChunk(e, gRender, volume_chunk, gChunk);
					DecreaseVolume_.DecreaseMusic(e, gRender, volume, gChunk);
					DecreaseVolumeChunk.DecreaseChunk(e, gRender, volume_chunk, gChunk);
				}

				SDL_SetRenderDrawColor(gRender, 0, 0, 0, 255);
				SDL_RenderClear(gRender);

				Menu_bg.LoadImage("img//Menu//upgrade_background.png", gRender);
				Menu_bg.Render(gRender);

				Setting_base.Render(gRender);

				Get_Back_Button.setRect(10, 10);
				Get_Back_Button.Render(gRender);

				DecreaseVolume_.setRect(620, 361);
				DecreaseVolume_.Render(gRender);

				DecreaseVolumeChunk.setRect(620, 461);
				DecreaseVolumeChunk.Render(gRender);

				IncreaseVolume_.setRect(860, 361);
				IncreaseVolume_.Render(gRender);

				IncreaseVolumeChunk.setRect(860, 461);
				IncreaseVolumeChunk.Render(gRender);

				SDL_RenderPresent(gRender);

			}

			int s = 0;
			if(play)
			{
				time_game.Start();
				
			}

			if (play || play_again)
			{
				int t = 0;
				while (t <= LOADING)
				{
					Loading[(t / 16) % 4].setRect(0, 0);
					Loading[(t / 16) % 4].Render(gRender);
					SDL_RenderPresent(gRender);
					t++;
				}
			}

			while(play)
			{	
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = 1;
						play = 0;
					}
					ex.HandleKey(e, gRender, time_game);
					Option_Button.HandleOptionButton(e, gRender, option, gChunk);
					Mute_.Mute(e, gRender, volume, temp_volume, gChunk);
				}

				//clear
				SDL_SetRenderDrawColor(gRender, 255, 255, 255, 255);
				SDL_RenderClear(gRender);

				
				//Center On Player
				ex.SetMapXY(k.start_x, k.start_y);
				ex.Move(k, gRender, time_game,win,play);

				if (win)
				{
					money += ex.get_Score();
				}

				//Create Map
				bg.Render(gRender);
				map.SetMap(k);
				map.BuildMap(gRender);


				//Display shot
				ex.P_Shot(gRender, k);

				//Display Player
				shadow.setRect(ex.P_getRect().x+12, ex.P_getRect().y+ex.P_getRect().h-20);
				shadow.Render(gRender);
				ex.Show(gRender);
				pet.PetMove(ex.get_x_pos(), ex.get_y_pos());

				if (detect_x < 500 && detect_y < 500)
				{
					if (PoNx == -1 && PoNy == -1)
					{
						double rotate_angle = atan2((double)(detect_y), (double)(detect_x)) * 180 / M_PI;
						pet.SetRolateAngle(rotate_angle);
						pet.SetPetFlip(SDL_FLIP_NONE);
					}
					else if (PoNx == 1 && PoNy == -1)
					{
						double rotate_angle = atan2((double)(detect_y), (double)(detect_x)) * 180 / M_PI;
						rotate_angle = 180 - rotate_angle;
						pet.SetRolateAngle(rotate_angle);
						pet.SetPetFlip(SDL_FLIP_HORIZONTAL);
					}
					else if (PoNx == 1 && PoNy == 1)
					{
						double rotate_angle = atan2((double)(detect_y), (double)(detect_x)) * 180 / M_PI;
						rotate_angle = 180 + rotate_angle;
						pet.SetRolateAngle(rotate_angle);
						pet.SetPetFlip(SDL_FLIP_HORIZONTAL);
					}
					else if (PoNx == -1 && PoNy == 1)
					{
						double rotate_angle = -atan2((double)(detect_y), (double)(detect_x)) * 180 / M_PI;
						pet.SetRolateAngle(rotate_angle);
						pet.SetPetFlip(SDL_FLIP_NONE);
					}
					if(have_pet)
					{
						pet.SetAttack(1);
						pet.LoadBullet(gRender, 1, 1);
						pet.PetShot(gRender, k);
					}
				}
				else
				{
				 pet.SetAttack(0);
				 //pet.SetPetFlip(SDL_FLIP_NONE);

				}
				detect_x = INT_MAX;
				detect_y = INT_MAX;
				kc = 1e9; 	
				pet.SetMap(k.start_x, k.start_y);
				if(have_pet)
				{
					pet.Show(gRender);
				}

				Option_Button.setRect(WIDTH-Option_Button.get_button_w(), HEIGHT-Option_Button.get_button_h());
				Option_Button.Render(gRender);

				Mute_.setRect(WIDTH - Option_Button.get_button_w(), HEIGHT - Option_Button.get_button_h() - Mute_.get_button_h());
				Mute_.Render(gRender);
				
				Mini_map.RenderMiniMap(gRender, k.start_x, k.start_y);
				Locate.setRectLocate((ex.get_x_pos() - k.start_x) / 9-ex.get_x_pos()/250-1, HEIGHT - 150 + (ex.get_y_pos() - k.start_y) / 9 - ex.get_y_pos() / 250);
				Locate.Render(gRender);

				//DisPlay Threat
				for (int i = 0; i < list_Threat.size(); i++)
				{
					Threat* Golem = list_Threat[i];
					if (Golem != NULL)
					{
						std::vector<Bullet*> t_bull = Golem->get_T_bullet();
						Bullet* b_ = t_bull[0];
						b_->set_Map_Bullet(k.start_x, k.start_y);
						Golem->Set_Map_T(k.start_x, k.start_y);
						Golem->Do_Threat(k, gRender);
						Golem->T_move(gRender,ex.get_x_pos(),ex.get_y_pos());
						Golem->T_Make_Bullet(gRender);
						int l = abs(pet.GetYPos() - Golem->get_T_y_pos()) * abs(pet.GetYPos() - Golem->get_T_y_pos()) + abs(pet.GetXPos() - Golem->get_T_x_pos()) * abs(pet.GetXPos() - Golem->get_T_x_pos());
						if (kc > sqrt(l))
						{
							kc = sqrt(l);
							detect_x = abs(pet.GetXPos() - Golem->get_T_x_pos());
							if (detect_x == 0)
							{
								PoNx = 1;
							}
							else
							{
								PoNx = (pet.GetXPos() - Golem->get_T_x_pos()) / detect_x;
							}
							detect_y = abs(pet.GetYPos() - Golem->get_T_y_pos());
							if (detect_y == 0)
							{
								PoNy = 1;
							}
							else
							{
								PoNy = (pet.GetYPos() - Golem->get_T_y_pos()) / detect_y;
							}
						}
						Golem->show(gRender);
					}
					else
					{
						list_Threat.erase(list_Threat.begin() + i);
						Golem = NULL;
					}
				}
				//Get Player Bullet
				std::vector<Bullet*> list_Player_Bullet = ex.getBullet();
				std::vector<Bullet*> list_Pet_bulelt = pet.GetBullet();
				//Check Bullet Attack Threat
				for (int i = 0; i < list_Player_Bullet.size(); i++)
				{
					Bullet* p_bullet = list_Player_Bullet[i];
					if (p_bullet != NULL)
					{
						for (int j = 0; j < list_Threat.size(); j++)
						{
							Threat* threat_ = list_Threat[j];
							if (threat_ != NULL)
							{
								SDL_Rect p_bull = p_bullet->getRect();
								SDL_Rect threat_rect = threat_->T_getRect();
								/*threat_rect.x = threat_->getRect().x;
								threat_rect.y = threat_->getRect().y;
								threat_rect.w = threat_->get_T_w();
								threat_rect.h = threat_->get_T_h();*/
								bool col = Common::CheckCollision(p_bull, threat_rect);
								if (col)
								{
									threat_->Decresae_HP(dame_player);
									ex.Remove_Bullet(i);
									if (threat_->Get_Hp_Threat() <= 0)
									{
										g_fire.set_fire_pos(threat_->get_T_x_pos(), threat_->get_T_y_pos());
										ex.Increase_Score();
										list_Threat.erase(list_Threat.begin() + j);
										threat_ = NULL;
									}
								}

							}
						}
					}
				}
				if(have_pet)
				{
					for (int i = 0; i < list_Pet_bulelt.size(); i++)
					{
						Bullet* p_bullet = list_Pet_bulelt[i];
						if (p_bullet != NULL)
						{
							for (int j = 0; j < list_Threat.size(); j++)
							{
								Threat* threat_ = list_Threat[j];
								if (threat_ != NULL)
								{
									SDL_Rect p_bull = p_bullet->getRect();
									SDL_Rect threat_rect = threat_->T_getRect();
									bool col = Common::CheckCollision(p_bull, threat_rect);
									if (col)
									{
										threat_->Decresae_HP(dame_pet);
										pet.Remove_Bullet(i);
										if (threat_->Get_Hp_Threat() <= 0)
										{
											g_fire.set_fire_pos(threat_->get_T_x_pos(), threat_->get_T_y_pos());
											ex.Increase_Score();
											list_Threat.erase(list_Threat.begin() + j);
											threat_ = NULL;
										}
									}

								}
							}
						}
					}
				}

				//Check Player colis Threat
				for (int i = 0; i < list_Threat.size(); i++)
				{
					Threat* threat_ = list_Threat[i];
					SDL_Rect Player_Rect = ex.P_getRect();
					
					SDL_Rect Player_Rect_Check = ex.P_getRect();
					Player_Rect_Check.x = ex.get_x_pos();
					Player_Rect_Check.y = ex.get_y_pos();

					SDL_Rect Area_T{ threat_->get_T_x_pos() - 500,threat_->get_T_y_pos()-200,1000 + threat_->get_T_w(),threat_->get_T_h()+400};
					bool col2 = Common::CheckCollision(Player_Rect_Check, Area_T);
					if (col2)
					{
						threat_->set_Attack(1);
						threat_->Act_Threat(ex.get_x_pos(), ex.get_y_pos(), k, gRender);
						SDL_Rect Threat_Rect = threat_->T_getRect();
						bool col = Common::CheckCollision(Player_Rect, Threat_Rect);
						if (col)
						{
							hp++;
							g_fire_p.set_fire_pos(ex.get_x_pos(), ex.get_y_pos());
							ex.set_revive_time(30);
							ex.setRect(40000, 40000);
							threat_->Decresae_HP(dame_player);
							if(threat_->Get_Hp_Threat() <= 0)
							{
								g_fire.set_fire_pos(threat_->get_T_x_pos(), threat_->get_T_y_pos());
								ex.Increase_Score();
								list_Threat.erase(list_Threat.begin() + i);
								threat_ = NULL;
							}

							if (hp >= hp_player)
							{
								lose = 1;
								play = 0;
								ex.setPos(250, 300);
								ex.set_status(Player::dir::none);
								ex.set_default_move();
								money += ex.get_Score();
								ex.set_Score();
								hp = 0;
							}
						}
					}
					else
					{
						threat_->set_Attack(0);
					}


				}

				//Check Bullet Threat Attack Player
				for (int i = 0; i < list_Threat.size(); i++)
				{
					Threat* _threat = list_Threat[i];
					if (_threat != NULL)
					{
						std::vector<Bullet*> T_list_bull = _threat->get_T_bullet();
						Bullet* T_bull = T_list_bull[0];
						if (T_bull != NULL)
						{
							SDL_Rect Player_Rect = ex.P_getRect();
							SDL_Rect Bullet_Threat_Rect = T_bull->getRect();
							bool col = Common::CheckCollision(Player_Rect, Bullet_Threat_Rect);
							if (col)
							{
								hp++;
								g_fire_p.set_fire_pos(ex.get_x_pos(), ex.get_y_pos());
								ex.set_revive_time(30);
								ex.setRect(4000, 4000);
								if (hp >= hp_player)
								{
									lose = 1;
									play = 0;
									ex.setPos(250, 300);
									ex.set_status(Player::dir::none);
									ex.set_default_move();
									money += ex.get_Score();
									ex.set_Score();
									//play_again = 1;
									hp = 0;
								}
							}
						}
					}
				}

				//DisPlay fire
				g_fire.set_fire_map(k.start_x, k.start_y);
				g_fire_p.set_fire_map(k.start_x, k.start_y);
				g_fire.Fire_Show(gRender);
				g_fire_p.Fire_Show(gRender);

				//Display HP Player
				HP_player.set_Lv_HP(hp*7/hp_player);
				HP_player.HP_Show(gRender);

				////DisPlay Name Player
				name.setText("hung");
				name.LoadText(gFont, gRender);
				name.setRect(ex.getRect().x + 10, ex.getRect().y - name.getRect().h);
				name.Render(gRender);

				//Display Score Player
				std::string _score = "" + std::to_string(ex.get_Score());
				score.setText(_score);
				score.LoadText(gFont, gRender);
				score.setRect(WIDTH - score.getRect().w, 10);
				score.Render(gRender);

				Money.setRect(WIDTH - score.getRect().w - 50,10);
				Money.Render(gRender);
				////Display Time,Check Time and display clock 

				int t = time_game.get_time() / 1000.f;
				std::string _time = std::to_string(t);
				time.setText(_time);
				time.LoadText(gFont, gRender);
				time.setRect(WIDTH / 2 - 10, 0);
				time.Render(gRender);

				g_clock.setRect(time.getRect().x - g_clock.get_clock_w(), 0);
				g_clock.Clock_Show(gRender);
				/*if (t >= 300)
				{
					ex.setPos(250, 300);
					ex.set_status(Player::dir::none);
					ex.set_default_move();
					ex.set_Score();
				}*/

				while (option)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							q = 1;
							play = 0;
							option = 0;
						}
						Play_Again_Button.HandleReplayButton(e, gRender, menu, play, howToPlay, s, hp, option, play_again, list_Threat, win, gChunk);
						Menu_Button.HandleMenuButton(e, gRender, menu, play, quitMenu, hp, option, play_again, list_Threat, gChunk);
						Quit.HandleQuit(e, gRender, menu, play,option, q, gChunk);
						Back_To_Game.HanldeBackToGame(e, gRender, option, gChunk);
					}
					Frame_Menu.Render(gRender);

					Play_Again_Button.setRect(WIDTH / 2 - Play_Again_Button.get_button_w() / 2, 325);
					Play_Again_Button.Render(gRender);

					Menu_Button.setRect(WIDTH / 2 - Menu_Button.get_button_w() / 2, 425);
					Menu_Button.Render(gRender);

					Quit.setRect(WIDTH / 2 - Quit.get_button_w() / 2, 525);
					Quit.Render(gRender);

					Back_To_Game.setRect(WIDTH / 2 - Quit.get_button_w() / 2, 225);
					Back_To_Game.Render(gRender);


					SDL_RenderPresent(gRender);
				}

				if (play_again||menu)
				{
					if (play_again)
					{
						int t = 0;
						while (t <= LOADING)
						{
							Loading[(t / 16) % 4].setRect(0, 0);
							Loading[(t / 16) % 4].Render(gRender);
							SDL_RenderPresent(gRender);
							t++;
						}
					}
					ex.setPos(200, 300);
					pet.SetPos(100, 200);
					for (int i = 0; i < list_Threat.size(); i++)
					{
						list_Threat[i]->free();
						//delete list_Threat[i];
					}
					list_Threat.erase(list_Threat.begin(), list_Threat.begin() + list_Threat.size());
					list_Threat = Create_Threat(gRender);
					time_game.Start();
					money += ex.get_Score();
					ex.set_Score();
					play_again = 0;

				}


				//Update Screen
				SDL_RenderPresent(gRender);
			}

			if (win)
			{
				Mix_PlayChannel(-1, chunk_win, 1);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = 1;
					}
					Play_Again_Button.HandleReplayButton(e, gRender, menu, play, howToPlay,s, hp, option, play_again, list_Threat,win, gChunk);
					Quit.HandleQuit(e, gRender, menu, play,option, q, gChunk);
				}
				
				SDL_RenderClear(gRender);
				SDL_SetRenderDrawColor(gRender, 255, 255, 255, 255);

				Menu_bg.LoadImage("img//Menu//win.png", gRender);
				Menu_bg.Render(gRender);

				Play_Again_Button.setRect(180, 700);
				Play_Again_Button.Render(gRender);

				Quit.setRect(1100, 700);
				Quit.Render(gRender);

				if (play_again)
				{
					play = 1;
					pet.SetPos(100, 200);
				}
				else if (q)
				{
					money += ex.get_Score();
				}

				SDL_RenderPresent(gRender);
			}

			if (lose)
			{
				Mix_PlayChannel(-1, chunk_death, 1);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						q = 1;
					}
					Play_Again_Button.HandleReplayButton(e, gRender, menu, play, howToPlay, s, hp, option, play_again, list_Threat, lose, gChunk);
					Quit.HandleQuit(e, gRender, menu, play,option, q, gChunk);
				}

				SDL_RenderClear(gRender);
				SDL_SetRenderDrawColor(gRender, 255, 255, 255, 255);

				Menu_bg.LoadImage("img//Menu//lose.png", gRender);
				Menu_bg.Render(gRender);

				Play_Again_Button.setRect(180, 700);
				Play_Again_Button.Render(gRender);

				Quit.setRect(1100, 700);
				Quit.Render(gRender);

				if (play_again)
				{
					play = 1;
					pet.SetPos(100, 200);
				}
				else if (q)
				{
					money += ex.get_Score();
				}

				SDL_RenderPresent(gRender);
			}

			update("Update//hp_player.txt", hp_player);
			update("Update//dame_player.txt", dame_player);
			update("Update//money.txt", money);
			update("Update//have_pet.txt", have_pet);
			update("Update//dame_pet.txt", dame_pet);

		}
			//free player
			ex.free();
			for (int i = 0; i < list_Threat.size(); i++)
			{
				list_Threat[i]->free();
			}
	}
	close();
	return 0;
}