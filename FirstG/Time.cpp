#include"Time.h"

Time::Time()
{
	is_start = 0;
	is_pause = 0;
	Time_Start = 0;
	Time_Pause = 0;
}
Time::~Time()
{

}

void Time:: Start()
{
	is_start = 1;
	is_pause = 0;

	Time_Start = SDL_GetTicks();
	Time_Pause = 0;
}

void Time::Pause()
{
	if (is_start && !is_pause)
	{
		is_pause = 1;
		Time_Pause = SDL_GetTicks() - Time_Start;
		Time_Start = 0;
	}
}

void Time::Un_Pause()
{
	if (is_start && is_pause)
	{
		is_pause = 0;
		Time_Start = SDL_GetTicks() - Time_Pause;
		Time_Pause = 0;
	}
}

Uint32 Time:: get_time()
{
	if (is_start)
	{
		if (!is_pause)
		{
			return SDL_GetTicks() - Time_Start;
		}
		else
		{
			return Time_Pause;
		}
	}
}