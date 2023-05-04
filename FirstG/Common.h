#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<string>
#include<stdio.h>
#include<sstream>
#include<vector>
#include<fstream>
#include<iomanip>


const int WIDTH = 1520;
const int HEIGHT = 850;
const int Bm = 32;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRender = NULL;
static SDL_Event e;

static TTF_Font* gFont = NULL;
static Mix_Chunk* gChunk = NULL;
static Mix_Chunk* gChunk1 = NULL;
static Mix_Chunk* chunk_win = NULL;
static Mix_Chunk* chunk_death = NULL;
static Mix_Music* gMusic = NULL;

const Uint8 R = 255;
const Uint8 G = 255;
const Uint8 B = 255;
const Uint8 A = 255;

#define MAX_MAP_X 150
#define MAX_MAP_Y 400

#define TILE_SIZE 64

#define SPEED 10
#define BULLET_SPEED 12 
#define LIM_DIS_BULLET 700

#define LIM_DIS_BULLET_T 200
#define T_BULLET_SPEED 4
#define T_SPEED 1

#define LOADING 150



typedef struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
};

typedef struct input
{
	int left, right, up, down, jump;
};

namespace Common
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool Check_Focus(int x, int y, SDL_Rect choose_space);
}

