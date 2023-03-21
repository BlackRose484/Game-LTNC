#pragma once
#include"Common.h"
#include"Base.h"

class Text :public Base
{
private:
	std::string s_val;
	int text_w;
	int text_h;

	SDL_Color color;
public:
	Text();
	~Text();
	void setColor(SDL_Color color_) { color = color_; };
	void setText(const std::string& s) { s_val = s; }
	bool LoadText(TTF_Font* font,SDL_Renderer*render);
};