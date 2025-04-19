#include "defs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

void initSnake() {
	SnakeCell *snake = game.snake;
	Assets *assets = &game.assets;
	Entity head, body, tail;
	head.x = 10;
	head.y = 10;
	head.texture = assets->headRight;
	body.x = 9;
	body.y = 10;
	body.texture = assets->bodyHorizontal;
	tail.x = 8;
	tail.y = 10;
	tail.texture = assets->tailLeft;
	snake[0].entity = head;
	snake[0].direction = RIGHT;
	snake[1].entity = body;
	snake[2].entity = tail;
};

void initApple() {
	SnakeCell *snake = game.snake;
	Entity *apple = &game.apple;
	int *score = &game.score;
	int x = rand() % (GRID_X);
	int y = rand() % (GRID_Y);

	for (int i=1; i<*score+2; i++) {
		if (snake[i].entity.x == apple->x && snake[i].entity.y == apple->y) {
			//printf("Error\n");
			initApple();
		}
	}

	apple->x = x;
	apple->y = y;
};

void increaseLength() {
	SnakeCell *snake = game.snake;
	int *score = &game.score;
	// This function should be called just before the score is updated
	int currTailX = snake[*score+2].entity.x;
	int currTailY = snake[*score+2].entity.y;
	int prevCellX = snake[*score+1].entity.x;
	int prevCellY = snake[*score+1].entity.y;

	// The new tail should be in the opposite direction;
	if (currTailY < prevCellY) {
		snake[*score+3].entity.x = snake[*score+2].entity.x;
		snake[*score+3].entity.y = snake[*score+2].entity.y - 1;
	} else if (currTailY > prevCellY) {
		snake[*score+3].entity.x = snake[*score+2].entity.x;
		snake[*score+3].entity.y = snake[*score+2].entity.y + 1;
	} else if (currTailX < prevCellX) {
		snake[*score+3].entity.x = snake[*score+2].entity.x - 1;
		snake[*score+3].entity.y = snake[*score+2].entity.y;
	} else if (currTailX > prevCellX) {
		snake[*score+3].entity.x = snake[*score+2].entity.x + 1;
		snake[*score+3].entity.y = snake[*score+2].entity.y;
	}
}

void checkCollision() {
	SnakeCell *snake = game.snake;
	int *score = &game.score;
	Entity *apple = &game.apple;
	GameScreen *gameState = &game.gameState;

	Entity head = snake[0].entity;
	for (int i=4; i<=*score+2; i++) {
		Entity cell = snake[i].entity;
		if (head.x == cell.x && head.y == cell.y) {
			*gameState = GAME_OVER;
		}
	}
	if (head.x == apple->x && head.y == apple->y) {
		initApple();
		increaseLength();
		*score = *score+1;;
	}
}

void updateSnake() {
	SnakeCell *snake = game.snake;
	Assets *assets = &game.assets;
	Direction *currDir = &game.currentDir;
	int *score = &game.score;
	// Move the tail first
	snake[*score+2].entity.x = snake[*score+1].entity.x;
	snake[*score+2].entity.y = snake[*score+1].entity.y;

	// The rest of the body
	for(int i = *score+1; i>0; i--) {
		snake[i].entity.x = snake[i-1].entity.x;
		snake[i].entity.y = snake[i-1].entity.y;
	}

	// Move the head last
	switch(*currDir) {
		case UP:
			snake[0].entity.y = snake[0].entity.y == 0 ? GRID_Y-1 : snake[0].entity.y-1;
			snake[0].entity.texture = assets->headUp;
			break;
		case DOWN:
			snake[0].entity.y = snake[0].entity.y == GRID_Y-1 ? 0 : snake[0].entity.y+1;
			snake[0].entity.texture = assets->headDown;
			break;
		case LEFT:
			snake[0].entity.x = snake[0].entity.x == 0 ? GRID_X-1 : snake[0].entity.x-1;
			snake[0].entity.texture = assets->headLeft;
			break;
		case RIGHT:
			snake[0].entity.x = snake[0].entity.x == GRID_X-1 ? 0 : snake[0].entity.x+1;
			snake[0].entity.texture = assets->headRight;
			break;
	}

	snake[0].direction = *currDir;

	// The tail should face the direction of the cell just before it
	int currTailX = snake[*score+2].entity.x;
	int currTailY = snake[*score+2].entity.y;
	int prevCellX = snake[*score+1].entity.x;
	int prevCellY = snake[*score+1].entity.y;

	if (currTailY < prevCellY) {
		snake[*score+2].entity.texture = assets->tailUp;
	} else if (currTailY > prevCellY) {
		snake[*score+2].entity.texture = assets->tailDown;
	} else if (currTailX < prevCellX) {
		snake[*score+2].entity.texture = assets->tailLeft;
	} else if (currTailX > prevCellX) {
		snake[*score+2].entity.texture = assets->tailRight;
	}

	// Decide the textures for the body
	for (int i = *score+1; i>0; i--) {
		int prevX = snake[i+1].entity.x;
		int prevY = snake[i+1].entity.y;
		int currX = snake[i].entity.x;
		int currY = snake[i].entity.y;
		int nextX = snake[i-1].entity.x;
		int nextY = snake[i-1].entity.y;

		// Same X with previous and next cells? Vertical
		if (prevX == currX && currX == nextX) {
			snake[i].entity.texture = assets->bodyVertical;
		}

		// Same Y with previous and next cells? Horizontal
		if (prevY == currY && currY == nextY) {
			snake[i].entity.texture = assets->bodyHorizontal;
		}

		// currY < nextY = next cell below
		// currY > nextY = next cell above
		// currX < nextX = next cell right
		// currX > nextX = next cell left
		// currY < prevY = prev cell below
		// currY > prevY = prev cell above
		// currX < prevX = prev cell right
		// currX > prevX = prev cell left

		// bottomRight
		// Next cell below, previous cell right
		// Next cell right, previous cell below
		if ((currY < nextY && currX < prevX) || (currX < nextX && currY < prevY)) {
			snake[i].entity.texture = assets->bodyBottomRight;
		}
		// bottomLeft
		// Next cell below, previous cell left
		// Next cell left, previous cell below
		else if ((currY < nextY && currX > prevX) || (currX > nextX && currY < prevY)) {
			snake[i].entity.texture = assets->bodyBottomLeft;
		}
		// topLeft
		// Next cell above, previous cell left
		// Next cell left, previous cell above
		else if ((currY > nextY && currX > prevX) || (currX > nextX && currY > prevY)) {
			snake[i].entity.texture = assets->bodyTopLeft;
		}
		// topRight
		// Next cell above, previous cell right
		// Next cell right, previous cell above
		else if ((currY > nextY && currX < prevX) || (currX < nextX && currY > prevY)) {
			snake[i].entity.texture = assets->bodyTopRight;
		}
	}
}
