#include "main.h"
#include "structs.h"
#include <stdlib.h>
#include <string.h>

void gameOverState(SDL_KeyboardEvent *event) {
	initSnake();
	initApple();
	memset(game.snake, 0, sizeof(game.snake));
	game.gameState = GAME;
	game.score = 0;
	game.currentDir = RIGHT;
}

void gameRunningState(SDL_KeyboardEvent *event) {
	Direction *currDir = &game.currentDir;
	switch (event->key) {
		case SDLK_UP:
			*currDir = game.snake[0].direction == DOWN ? DOWN : UP;
			break;
		case SDLK_DOWN:
			*currDir = game.snake[0].direction == UP ? UP : DOWN;
			break;
		case SDLK_LEFT:
			*currDir = game.snake[0].direction == RIGHT ? RIGHT : LEFT;
			break;
		case SDLK_RIGHT:
			*currDir = game.snake[0].direction == LEFT ? LEFT : RIGHT;
			break;
		default:
			break;
	}
}

void doKeydown(SDL_KeyboardEvent *event) {
	switch (game.gameState) {
		case GAME:
			gameRunningState(event);
			break;
		case GAME_OVER:
			gameOverState(event);
			break;
		default:
			break;
	}
}

void doInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				exit(1);
				break;

			case SDL_EVENT_KEY_DOWN:
				doKeydown(&event.key);
				break;

			default:
				break;
		}
	}
}
