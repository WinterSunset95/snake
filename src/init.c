#include "structs.h"
#include "defs.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initSDL() {
	int renderFlags, windowFlags;
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize sdl: %s\n", SDL_GetError());
		exit(1);
	}

	if (!TTF_Init()) {
		printf("Couldn't initialize fonts: %s\n", SDL_GetError());
		exit(1);
	}

	game.app.window = SDL_CreateWindow("Snake", SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!game.app.window) {
		printf("Couldn't open window: %s\n", SDL_GetError());
		exit(1);
	}

	game.app.renderer = SDL_CreateRenderer(game.app.window, NULL);

	if (!game.app.renderer) {
		printf("Couldn't create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void loadGraphics() {
	game.assets.headUp = loadTexture("../Graphics/head_up.png");
	game.assets.headDown = loadTexture("../Graphics/head_down.png");
	game.assets.headLeft = loadTexture("../Graphics/head_left.png");
	game.assets.headRight = loadTexture("../Graphics/head_right.png");
	game.assets.tailUp = loadTexture("../Graphics/tail_up.png");
	game.assets.tailDown = loadTexture("../Graphics/tail_down.png");
	game.assets.tailLeft = loadTexture("../Graphics/tail_left.png");
	game.assets.tailRight = loadTexture("../Graphics/tail_right.png");
	game.assets.bodyTopLeft = loadTexture("../Graphics/body_topleft.png");
	game.assets.bodyTopRight = loadTexture("../Graphics/body_topright.png");
	game.assets.bodyBottomRight = loadTexture("../Graphics/body_bottomright.png");
	game.assets.bodyBottomLeft = loadTexture("../Graphics/body_bottomleft.png");
	game.assets.bodyHorizontal = loadTexture("../Graphics/body_horizontal.png");
	game.assets.bodyVertical = loadTexture("../Graphics/body_vertical.png");
	game.assets.apple = loadTexture("../Graphics/apple.png");
	game.apple.texture = game.assets.apple;
	game.font = TTF_OpenFont("../Graphics/Montserrat-VariableFont_wght.ttf", 100);
	game.textEngine = TTF_CreateRendererTextEngine(game.app.renderer);
};

void cleanup() {
	SDL_Quit();
	TTF_Quit();
}
