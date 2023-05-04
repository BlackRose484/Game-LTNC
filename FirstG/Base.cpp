#include"Common.h"
#include"Base.h"

Base::Base()
{
	OBJ = NULL;
	O_Rect.x = 0;
	O_Rect.y = 0;
	O_Rect.w = 0;
	O_Rect.h = 0;
}

Base::~Base()
{
	free();
}

void Base::free()
{
	if (OBJ != NULL)
	{
		//Important
		SDL_DestroyTexture(OBJ);
		OBJ = NULL;
		O_Rect.x = 0;
		O_Rect.y = 0;
		O_Rect.w = 0;
		O_Rect.h = 0;
	}
}

bool Base::LoadImage(std::string path, SDL_Renderer* render,Uint8 cR, Uint8 cG, Uint8 cB)
{
	free();
	SDL_Surface* O_sur = IMG_Load(path.c_str());
	if (O_sur == NULL)return 0;
	else
	{
		SDL_SetColorKey(O_sur, SDL_TRUE, SDL_MapRGB(O_sur->format, cR, cG, cB));
		OBJ = SDL_CreateTextureFromSurface(render,O_sur);
		if (OBJ == NULL)return 0;
		else
		{
			O_Rect.w = O_sur->w;
			O_Rect.h = O_sur->h;
		}
		SDL_FreeSurface(O_sur);
	}
	return OBJ!=NULL;
}

void Base::Render(SDL_Renderer* render, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQ = { O_Rect.x,O_Rect.y,O_Rect.w,O_Rect.h };
	SDL_RenderCopy(render, OBJ, clip, &renderQ);
}

void Base::setRect(const int& x, const int& y)
{
	O_Rect.x = x;
	O_Rect.y = y;
}

void Base::RenderMiniMap(SDL_Renderer* render, const int& x, const int& y)
{
	SDL_Rect clip = { x/9.0,y/9.0,150,150 };
	SDL_Rect renderQ = { O_Rect.x,O_Rect.y,150,150 };
	SDL_RenderCopy(render, OBJ, &clip, &renderQ);
}

void Base::setRectLocate(const double& x, const double& y)
{
	O_Rect.x = x;
	O_Rect.y = y;
}