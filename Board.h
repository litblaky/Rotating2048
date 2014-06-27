#ifndef _BOARD_H_
#define _BOARD_H_

#include "Grid.h"
#include <vector>

#define BOARD_SIZE 4

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

	void clear();
private:
	void addNumberPiece();
	bool judgeEnd();
	std::vector<Grid *> getFreeGrids();


	Grid grids[BOARD_SIZE][BOARD_SIZE];
	static Board *instance;
};


#endif