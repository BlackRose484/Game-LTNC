#pragma once

#include"Common.h"
#include"Base.h"
#include"Threat.h"

class Button :public Base
{
private:
	int w_frame;
	int h_frame;
public:
	Button();
	~Button();
	
	bool LoadImage(std::string path, SDL_Renderer* render, Uint8 cR = 255, Uint8 cG = 255, Uint8 cB = 255);

	int get_button_w() const { return w_frame; };
	int get_button_h() const { return h_frame; };

	bool isInside(SDL_Event& e);

	void HandlePlay(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play,bool &quitMenu,Mix_Chunk* sound_effect);

	void HandleHowToPlayButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& HowToPlay, Mix_Chunk* sound_effect);

	void HandleGetBackButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& howToPlay, bool& upgrade, Mix_Chunk* sound_effect);

	void HandleQuitButton(SDL_Event& e, SDL_Renderer* render, bool& quit_game, bool& play, Mix_Chunk* sound_effect);

	void HandleReplayButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& howToPlay, int& score, int& health ,bool& option,bool &play_again, std::vector<Threat*>& p_list_enemy,bool &win, Mix_Chunk* sound_effect);

	void HandleMenuButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit_menu, int& health,bool& option, bool& play_again, std::vector<Threat*>& p_list_enemy, Mix_Chunk* sound_effect);

	void HandleUpgradeButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& HowToPlay, bool& upgrade, Mix_Chunk* sound_effect);

	void HandleUpgrade(SDL_Event& e, SDL_Renderer* render, int& money_needed_to_upgrade, int& current_upgraded, int& upgrade_plus, int& current_money, Mix_Chunk* sound_effect);

	void HandleOptionButton(SDL_Event& e, SDL_Renderer* render, bool& option, Mix_Chunk* sound_effect);

	void NextButton(SDL_Event& e, SDL_Renderer* render, int& idx_hep, Mix_Chunk* sound_effect);

	void SelectMapButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& select_map, Mix_Chunk* sound_effect);

	void ChooseMap1(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& map1, bool& select_map, Mix_Chunk* sound_effect);

	void ChooseMap2(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& map2, bool& select_map, Mix_Chunk* sound_effect);

	void HandleQuit(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, Mix_Chunk* sound_effect);

	void HandleQuitMenu(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, Mix_Chunk* sound_effect);

	void Mute(SDL_Event& e, SDL_Renderer* render, int& volume, int& temp_volume, Mix_Chunk* sound_effect);
};