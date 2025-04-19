#ifndef  MAIN_H
#define MAIN_H

#include "structs.h"

// init.c
void initSDL();
void cleanup();
void loadGraphics();

// input.c
void doInput();

// draw.c
void prepareScene();
void presentScene();
SDL_Texture *loadTexture(char *filename);
void blit(Entity *entity);
void drawSnake();

// snake.c
void initSnake();
void initApple();
void updateSnake();
void increaseLength();
void checkCollision();

#endif
