#include "structs.h"
#include "defs.h"
#include <stdio.h>

void prepareScene() {
	App *app = &game.app;
	SDL_SetRenderDrawColor(app->renderer, 96, 255, 128, 255);
	SDL_RenderClear(app->renderer);
}

void presentScene() {
	App *app = &game.app;
	SDL_RenderPresent(app->renderer);
}

SDL_Texture *loadTexture(char *filename) {
	App *app = &game.app;
	SDL_Texture *texture;
	SDL_LogMessage(1, SDL_LOG_CATEGORY_APPLICATION, "Loading: %s", filename);
	texture = IMG_LoadTexture(app->renderer, filename);
	if (texture == NULL) {
		printf("Failed to load texture\n");
		return NULL;
	}
	return texture;
}

void blit(Entity *entity) {
	App *app = &game.app;
	SDL_FRect dest;

	dest.x = entity->x*CELL;
	dest.y = entity->y*CELL;
	dest.h = CELL;
	dest.w = CELL;

	SDL_RenderTexture(app->renderer, entity->texture, NULL, &dest);
}

void writeText(App *app, char *text, int x, int y, int size) {
};

void drawSnake() {
	App *app = &game.app;
	SnakeCell *snake = game.snake;
	int *score = &game.score;
	for (int i=0; i<*score+3; i++) {
		blit(&snake[i].entity);
	}
}
