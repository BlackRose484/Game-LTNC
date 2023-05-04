#include"Common.h"
#include"Button.h"

Button::Button()
{
	w_frame = 0;
	h_frame = 0;
}

Button::~Button()
{

}

bool Button::LoadImage(std::string path, SDL_Renderer* render, Uint8 cR, Uint8 cG, Uint8 cB)
{
	int ret = Base::LoadImage(path, render, cR, cG, cB);
	if (ret)
	{
		w_frame = O_Rect.w;
		h_frame = O_Rect.h;
	}
	return ret;
}

bool Button::isInside(SDL_Event& e)
{
	bool inside = true;
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{

		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < O_Rect.x)
		{
			inside = false;
		}
		else if (x > O_Rect.x + w_frame)
		{
			inside = false;
		}
		else if (y < O_Rect.y)
		{
			inside = false;
		}
		else if (y > O_Rect.y + h_frame)
		{
			inside = false;
		}

		return inside;

	}
	return 0;
}

void Button::HandlePlay(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quitMenu, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/play_button_select.png", render,1,3,5);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			play = true;
			quitMenu = true;
			menu = false;
		}

	}
	else
	{
		LoadImage("img/Menu/Button/play_button.png", render,1,3,5);
	}
}

void Button::HandleHowToPlayButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quitMenu, bool& HowToPlay, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/help_button_select.png", render,1,3,5);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			play = false;
			quitMenu = false;
			menu = false;
			HowToPlay = true;
		}
	}
	else
	{
		LoadImage("img/Menu/Button/help_button.png", render,1,3,5);
	}
}

void Button::HandleGetBackButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quitMenu, bool& howToPlay, bool& upgrade,bool &setting, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/return_select.png", render,1,2,3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			play = false;
			quitMenu = false;
			menu = true;
			howToPlay = false;
			upgrade = false;
			setting = false;
		}
	}
	else
	{
		LoadImage("img/Menu/Button/return.png", render);
	}
}

void Button::HandleQuitButton(SDL_Event& e, SDL_Renderer* render, bool& quit_game, bool& play, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("asset/button/quit_red.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			quit_game = true;
			play = false;
		}
	}
	else
	{
		LoadImage("asset/button/quit_black.png", render);
	}
}

void Button::HandleOptionButton(SDL_Event& e, SDL_Renderer* render, bool& option, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/pause_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			option = true;

		}
	}
	else
	{
		LoadImage("img/Menu/Button/pause.png", render);
	}
}

void Button::HandleReplayButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& howToPlay, int& score, int& health,bool& option, bool& play_again, std::vector<Threat*>& p_list_enemy,bool &win, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/play_again_select.png", render,1,2,3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = false;
			howToPlay = false;
			play = true;
			score = 0;
			health =0;
			option = false;
			play_again = 1;
			win = 0;
			// refresh enemy wave
			for (int i = 0; i < p_list_enemy.size(); i++)
			{
				p_list_enemy[i]->free();
			}
			p_list_enemy.erase(p_list_enemy.begin(), p_list_enemy.begin() + p_list_enemy.size());
		}
	}
	else
	{
		LoadImage("img/Menu/Button/play_again.png", render, 1, 2, 3);
	}
}

void Button::HandleMenuButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit_menu, int& health, bool& option,bool &play_again, std::vector<Threat*>& p_list_enemy, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/menu_select.png", render,1,3,5);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = true;
			quit_menu = false;
			play = false;
			health = 0;
			option = false;
			play_again = true;
			// refresh enemy wave
			for (int i = 0; i < p_list_enemy.size(); i++)
			{
				p_list_enemy[i]->free();
			}
			p_list_enemy.erase(p_list_enemy.begin(), p_list_enemy.begin() + p_list_enemy.size());
		}
	}
	else
	{
		LoadImage("img/Menu/Button/menu.png", render, 1, 3, 5);
	}
}

void Button::NextButton(SDL_Event& e, SDL_Renderer* render, int& idx_help, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//left_but.png", render,1,2,3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			idx_help++;
			idx_help = (idx_help > 7) ? 0:idx_help;
		}
	}
	else
	{
		LoadImage("img//Menu//left_but.png", render,1,2,3);
	}
}

void Button::SelectMapButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& select_map, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//select_map.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = false;
			play = false;
			quit = false;
			select_map = true;
		}
	}
	else
	{
		LoadImage("img//Menu//Button//select_map_black.png", render);
	}
}

void Button::ChooseMap1(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& map1,bool&select_map, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//SP_item//fire1.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = true;
			play = false;
			quit = false;
			map1 = true;
			select_map = false;
		}
	}
	else
	{
		LoadImage("img//SP_item//clock.png", render);
	}
}

void Button::ChooseMap2(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& map2, bool& select_map, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		
		LoadImage("img//SP_item//fire1.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = true;
			play = false;
			quit = false;
			map2 = true;
			select_map = false;
		}
	}
	else
	{
		LoadImage("img//SP_item//clock.png", render);
	}
}

void Button::HandleQuit(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play,bool &option, bool& quit, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		
		LoadImage("img//Menu//Button//quit_select.png", render,1,2,3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = false;
			play = false;
			quit = true;
			option = false;
		}
	}
	else
		LoadImage("img//Menu//Button//quit.png", render,1,2,3);
}

void Button:: HandleQuitMenu(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{

		LoadImage("img//Menu//Button//quit_select_menu.png", render, 1, 2, 3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = false;
			play = false;
			quit = true;
		}
	}
	else
		LoadImage("img//Menu//Button//quit_menu.png", render, 1, 2, 3);
}

void Button:: HandleUpgradeButton(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& HowToPlay, bool& upgrade, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		
		LoadImage("img//Menu//Button//upgrade_select.png", render,1,2,3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			menu = false;
			play = false;
			HowToPlay = false;
			upgrade = true;
		}
	}
	else
	{
		LoadImage("img//Menu//Button//upgrade.png", render,1,2,3);
	}
}

void Button::HandleUpgrade(SDL_Event& e, SDL_Renderer* render, int& money_needed_to_upgrade, int& current_upgraded, int& upgrade_plus, int& current_money, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//upgrade_button_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			if(current_money>=money_needed_to_upgrade)
			{
				current_upgraded += upgrade_plus;
				current_money -= money_needed_to_upgrade;
			}
		}
	}
	else
	{
		LoadImage("img//Menu//Button//upgrade_button.png", render);
	}
}

void Button::Mute(SDL_Event& e, SDL_Renderer* render, int& volume, int& temp_volume, Mix_Chunk* sound_effect)
{
	if (volume)
	{
		if (isInside(e))
		{
			LoadImage("img//Menu//Button//music_select.png", render);
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, sound_effect, 0);
				temp_volume = volume;
				volume = 0;
				Mix_VolumeMusic(volume);
			}
		}
		else
		{
			LoadImage("img//Menu//Button//music.png", render);
		}
	}
	else
	{
		if (isInside(e))
		{
			LoadImage("img/Menu/Button/music_mute_select.png", render, 1, 3, 5);
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, sound_effect, 0);
				volume = temp_volume;
				Mix_VolumeMusic(volume);
			}
		}
		else
		{
			LoadImage("img/Menu/Button/music_mute.png", render, 1, 3, 5);
		}
	}
}

void Button::IncreaseVolumeChunk(SDL_Event& e, SDL_Renderer* render, int& volume, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//upgrade_button_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			volume += 10;
			Mix_VolumeChunk(sound_effect, volume);
		}
	}
	else
	{
		LoadImage("img//Menu//Button//upgrade_button.png", render);
	}
}

void Button::HandleSetting(SDL_Event& e, SDL_Renderer* render, bool& menu, bool& play, bool& quit, bool& setting, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img/Menu/Button/setting_select.png", render, 1, 3, 5);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			play = false;
			quit = false;
			menu = false;
			setting = true;
		}
	}
	else
	{
		LoadImage("img/Menu/Button/setting.png", render, 1, 3, 5);
	}
}

void Button::IncreaseVolume(SDL_Event& e, SDL_Renderer* render, int& volume, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//upgrade_button_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			volume += 10;
			Mix_VolumeMusic(volume);
		}
	}
	else
	{
		LoadImage("img//Menu//Button//upgrade_button.png", render);
	}
}

void Button::HanldeBackToGame(SDL_Event& e, SDL_Renderer* render, bool& option, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//back_to_game_select.png", render,1,3,5);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			option = false;
		}
	}
	else
	{
		LoadImage("img//Menu//Button//back_to_game.png", render,1,3,5);
	}
}

void Button::DecreaseMusic(SDL_Event& e, SDL_Renderer* render, int& volume, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//decrease_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			volume -= 10;
			Mix_VolumeMusic(volume);
		}
	}
	else
	{
		LoadImage("img//Menu//Button//decrease.png", render);
	}
}

void Button::DecreaseChunk(SDL_Event& e, SDL_Renderer* render, int& volume, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("img//Menu//Button//decrease_select.png", render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			volume -= 10;
			Mix_VolumeChunk(sound_effect,volume);
		}
	}
	else
	{
		LoadImage("img//Menu//Button//decrease.png", render);
	}
}

void Button:: UnlockPet(SDL_Event& e, SDL_Renderer* render, int& money_needed_to_unlock, int& be_unlock, int& current_money, Mix_Chunk* sound_effect)
{
	if (isInside(e))
	{
		LoadImage("Update//lock.png", render, 1, 2, 3);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			Mix_PlayChannel(-1, sound_effect, 0);
			if (current_money >= money_needed_to_unlock)
			{
				current_money -= money_needed_to_unlock;
				be_unlock = 1;
			}
		}
	}
	else
	{
		LoadImage("Update//lock_select.png", render, 1, 2, 3);
	}
}