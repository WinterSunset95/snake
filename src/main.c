#include "structs.h"
#include "main.h"
#include <string.h>

Game game;
int main(int argc, char *argv[]) {
	initSDL();

	initSnake();
	initApple();
	loadGraphics();
	TTF_Text *text = TTF_CreateText(game.textEngine, game.font, "Game Over", 100);
	TTF_Text *miniText = TTF_CreateText(game.textEngine, game.font, "Press any key to restart", 100);

	int count = 0;
	int currDir = RIGHT;
	while (1) {
		prepareScene();
		doInput();
		if (count == 0 || count >= 25) {
			count = 0;

			char scoreTxt[10];
			char scorePlaceHolder[100] = "Score: ";
			if (game.gameState == GAME) {
				SDL_itoa(game.score, scoreTxt, 10);
				updateSnake();
				checkCollision();
				strcat(scorePlaceHolder, scoreTxt);
				TTF_SetFontSize(game.font, 30);
				TTF_SetFontOutline(game.font, 1);
				TTF_SetFontStyle(game.font, TTF_STYLE_NORMAL);
				TTF_Text *scoreTxtSdl = TTF_CreateText(game.textEngine, game.font, scorePlaceHolder, 100);
				TTF_SetTextColor(scoreTxtSdl, 250, 90, 0, 255);
				TTF_DrawRendererText(scoreTxtSdl, 5, 0);
			}
			if (game.gameState == GAME_OVER) {
				TTF_SetFontSize(game.font, 100);
				TTF_SetFontOutline(game.font, 5);
				TTF_DrawRendererText(text, 8*40, 8*40);

				TTF_SetFontSize(game.font, 30);
				TTF_SetFontOutline(game.font, 1);
				TTF_DrawRendererText(miniText, 11*40, 11*40);
			}
			drawSnake();
			blit(&game.apple);
			presentScene();
		}
		count++;
		SDL_Delay(10);
	}
}
