#pragma once
#include <stdio.h>
#include "menu.h"

typedef struct Scoreboard_game {
	int difficulty;
	float time;
	int score;
} Scoreboard_game;


class Scoreboard {
	private: 
	FILE *scoreboard;

	public:
	Scoreboard() {
		scoreboard = fopen("scoreboard.txt", "ab+");
	}

	void addGame(Scoreboard_game *game) {
		fwrite(game, sizeof(Scoreboard_game), 1, scoreboard);
		fclose(scoreboard);
	}

	void forEachGame(Menu *menu, void (*callback)(Menu *, Scoreboard_game)) {
		while(!feof(scoreboard)) {
			Scoreboard_game game;
			fread(&game, sizeof(Scoreboard_game), 1, scoreboard);
			callback(menu, game);
		}
		fclose(scoreboard);
	}
};