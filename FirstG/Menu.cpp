#include"Menu.h"
#include"Time.h"

int Menu::create_menu(std::string path, SDL_Renderer* render,Time &_time_game)
{
	LoadImage(path, render,1,3,5);
	SDL_Event key_;
	TTF_Font *Menu_font = TTF_OpenFont("font//Neverwinter.ttf", 45);
	SDL_Color menu_text_color = { 0,0,0,255 };
	SDL_Color New_color = { 255,69,0,255 };
	// start 
	Text Start_game;
	Start_game.setText("Start Game");
	//Instruc
	Text InStruc;
	InStruc.setText("Guide");

	//exit 
	Text Exit_game;
	Exit_game.setText("Exit Game");
	

	while(1)
	{
		Start_game.LoadText(Menu_font, render);
		Start_game.setRect(100, 200);

		InStruc.LoadText(Menu_font, render);
		InStruc.setRect(Start_game.getRect().x, Start_game.getRect().y + Start_game.getRect().h + 10);

		Exit_game.LoadText(Menu_font, render);
		Exit_game.setRect(InStruc.getRect().x, InStruc.getRect().y + InStruc.getRect().h + 10);


		Render(render);
		Start_game.Render(render);
		InStruc.Render(render);
		Exit_game.Render(render);
		
		while (SDL_PollEvent(&key_))
		{
			if (key_.type == SDL_QUIT)
			{
				return 1;
			}
			else if (key_.type == SDL_KEYDOWN)
			{
				switch (key_.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					LoadImage(path, render);
					break;
				default:
					break;
				}
			}
			else if (key_.type == SDL_MOUSEMOTION)
			{
				//Check inside
				int x_mouse, y_mouse;
				SDL_GetMouseState(&x_mouse, &y_mouse);
				if (Common::Check_Focus(x_mouse, y_mouse, Start_game.getRect()))
				{
					Start_game.setColor(New_color);
				}
				else
				{
					Start_game.setColor(menu_text_color);
				}
				if (Common::Check_Focus(x_mouse, y_mouse, InStruc.getRect()))
				{
					InStruc.setColor(New_color);
				}
				else
				{
					InStruc.setColor(menu_text_color);
				}
				if (Common::Check_Focus(x_mouse, y_mouse, Exit_game.getRect()))
				{
					Exit_game.setColor(New_color);
				}
				else
				{
					Exit_game.setColor(menu_text_color);
				}
			}
			else if (key_.type == SDL_MOUSEBUTTONDOWN)
			{
				int x_mouse, y_mouse;
				SDL_GetMouseState(&x_mouse, &y_mouse);
				if (Common::Check_Focus(x_mouse, y_mouse, Start_game.getRect()))
				{
					switch(key_.button.button)
					{
					case SDL_BUTTON_LEFT:
						_time_game.Start();
						return 0;
						break;
					}
				}
				if (Common::Check_Focus(x_mouse, y_mouse, InStruc.getRect()))
				{
					switch (key_.button.button)
					{
					case SDL_BUTTON_LEFT:
						LoadImage("img//Menu//inst.png", render,1,3,5);
						setRect((WIDTH - getRect().w) / 2, (HEIGHT - getRect().h) / 2);
						Render(render);
					}
				}
				if (Common::Check_Focus(x_mouse, y_mouse,Exit_game.getRect()))
				{
					switch (key_.button.button)
					{
					case SDL_BUTTON_LEFT:
						return 1;
						break;
					}
				}
			}
			
		}
		SDL_RenderPresent(render);
	}
	return -1;
}

//Pause_game////////////////////////////////////////////
Pause_game::Pause_game()
{
	is_pause = 1;
}

Pause_game::~Pause_game()
{

}

int Pause_game:: setPause(SDL_Renderer* render, Time& _time_game)
{
	_time_game.Pause();
	LoadImage("img//Menu//pause.png", render,1,3,5);
	setRect((WIDTH - getRect().w) / 2, (HEIGHT - getRect().h) / 2);
	Render(render);
	SDL_Event pau;
	while (1)
	{
		while (SDL_PollEvent(&pau))
		{
			if (pau.type == SDL_KEYDOWN)
			{
				switch (pau.key.keysym.sym)
				{
				case SDLK_p:
					_time_game.Un_Pause();
					return 0;
					break;

				}
			}
		}
		SDL_RenderPresent(render);
	}
}

int Pause_game::create_pause(SDL_Renderer*render)
{
	while(1)
	{
		if (is_pause)
		{
			Render(render);
			
		}
	}
	return 1;
}
//Result///////////////////////////////////////////////////////////////////////////////////////////////

int Result_game::create_result(std::string path, SDL_Renderer* render, Time& _time_game)
{
	LoadImage(path, render, 1, 3, 5);
	SDL_Event key_re;
	TTF_Font* result_font = TTF_OpenFont("font//Neverwinter.ttf", 45);
	SDL_Color result_text_color = { 255,255,255,255 };
	SDL_Color New_color = { 255,69,0,255 };

	//Retry
	Text Retry;
	Retry.setText("Retry");
	Retry.setColor(result_text_color);
	
	//Quit
	Text Quit;
	Quit.setText("Quit");
	Quit.setColor(result_text_color);

	while (1)
	{
		Retry.LoadText(result_font, render);
		Retry.setRect(200, 700);

		Quit.LoadText(result_font, render);
		Quit.setRect(1180, 700);

		Render(render);
		Retry.Render(render);
		Quit.Render(render);

		while (SDL_PollEvent(&key_re) != 0)
		{
			if (key_re.type == SDL_QUIT)
				return 1;
			else if (key_re.type == SDL_KEYDOWN)
			{
				if (key_re.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			}
			else if (key_re.type == SDL_MOUSEMOTION)
			{
				int x_mouse, y_mouse;
				SDL_GetMouseState(&x_mouse, &y_mouse);
				if (Common::Check_Focus(x_mouse, y_mouse,Retry.getRect()))
				{
					Retry.setColor(New_color);
				}
				else
				{
					Retry.setColor(result_text_color);
				}
				if (Common::Check_Focus(x_mouse, y_mouse,Quit.getRect()))
				{
					Quit.setColor(New_color);
				}
				else
				{
					Quit.setColor(result_text_color);
				}
			}
			else if (key_re.type == SDL_MOUSEBUTTONDOWN)
			{
				int x_mouse, y_mouse;
				SDL_GetMouseState(&x_mouse, &y_mouse);
				if (Common::Check_Focus(x_mouse, y_mouse, Retry.getRect()))
				{
					_time_game.Start();
					return 0;
				}
				if (Common::Check_Focus(x_mouse, y_mouse, Quit.getRect()))
				{
					return 1;
				}
			}
		}
		SDL_RenderPresent(render);
	}

}

