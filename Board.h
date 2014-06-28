#ifndef _BOARD_H_
#define _BOARD_H_

#include "Grid.h"
#include <vector>

#define LAYER_NUM 3
#define LAYER_SIZE 8
// 45 degrees in radian
#define ANGLE_UNIT 0.7853981633874483
#define LAYER_LENGTH 50

class Board
{
public:
	Board();
	~Board();
	
	static Board *getInstance();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void changeLayer();

	void clear();
private:
	void addNumberPiece();
	bool judgeEnd();
	std::vector<Grid *> getFreeGrids();


	Grid grids[LAYER_NUM][LAYER_SIZE];
	static Board *instance;
	int layer;
};


#endif