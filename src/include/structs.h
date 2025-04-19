#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL3_ttf/SDL_textengine.h"
#include "defs.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

typedef struct {
	Entity entity;
	int prevDir;
	int direction;
	int nextDir;
} SnakeCell;

typedef struct {
	SDL_Texture *headUp;
	SDL_Texture *headDown;
	SDL_Texture *headLeft;
	SDL_Texture *headRight;
	SDL_Texture *tailUp;
	SDL_Texture *tailDown;
	SDL_Texture *tailLeft;
	SDL_Texture *tailRight;
	SDL_Texture *bodyTopLeft;
	SDL_Texture *bodyTopRight;
	SDL_Texture *bodyBottomRight;
	SDL_Texture *bodyBottomLeft;
	SDL_Texture *bodyHorizontal;
	SDL_Texture *bodyVertical;
	SDL_Texture *apple;
} Assets;

typedef enum {
	GAME,
	GAME_OVER
} GameScreen;

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

typedef struct {
	App app;
	SnakeCell snake[GRID_SIZE];
	Assets assets;
	Entity apple;
	TTF_Font *font;
	TTF_TextEngine *textEngine;
	int score;
	Direction currentDir;
	GameScreen gameState;
} Game;

extern Game game;

#endif
