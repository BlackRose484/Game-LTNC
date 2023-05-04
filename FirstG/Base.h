#pragma once

#include"Common.h"
#include"Base.h"

class Base
{
protected:

	SDL_Texture* OBJ;
	SDL_Rect O_Rect;

public:
	Base();
	~Base();

	void free();

	void setRect(const int &x, const int &y);

	void setRectLocate(const double& x, const double& y);

	SDL_Rect getRect() { return O_Rect; }

	virtual bool LoadImage(std::string path, SDL_Renderer* render,Uint8 cR = 255,Uint8 cG = 255,Uint8 cB = 255);

	void Render(SDL_Renderer* render, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void RenderMiniMap(SDL_Renderer* render, const int& x, const int& y);

};