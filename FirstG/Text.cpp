#include"Common.h"
#include"Base.h"
#include"Text.h"


Text::Text()
{
	s_val = "";
	text_h = 0;
	text_w = 0;
	color = { 0,0,0,255 };
}

Text::~Text()
{
	free();
}

bool Text::LoadText(TTF_Font* font,SDL_Renderer*render)
{
	free();
	//SDL_Color color = { 255,255,255,255 };
	SDL_Surface* Text_sur = TTF_RenderText_Solid(font, s_val.c_str(), color);
	if (Text_sur == NULL)return 0;
	else
	{
		OBJ = SDL_CreateTextureFromSurface(render, Text_sur);
		if (OBJ == NULL)return 0;
		else
		{
			O_Rect.w = Text_sur->w;
			O_Rect.h = Text_sur->h;
		}
		SDL_FreeSurface(Text_sur);
	}
	return OBJ != NULL;
}