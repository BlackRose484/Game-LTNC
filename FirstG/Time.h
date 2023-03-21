#pragma once
#include"Common.h"
#include"Base.h"
#include"Common.h"

class Time : public Base
{
private:
	Uint32 Time_Start;
	Uint32 Time_Pause;
	bool is_pause;
	bool is_start;
public:

	Time();
	~Time();
	void Start();
	void Pause();
	void Un_Pause();

	bool get_Pause()const { return is_pause; };

	Uint32 get_time();
};