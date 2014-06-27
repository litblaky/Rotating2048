#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"

using namespace cocos2d;

class Game: public Scene
{
public:
	static bool initGame();
	static void lose();
	static void updateGrade();

	static Game *game;
	static Layer *lose_layer;
	static Layer *pieces_layer;
	static LabelTTF *grade_label;

	static int state; // 0 for play, 1 for lose
	static int grade;

	void setUp();
};

#endif