#ifndef _GRID_H_
#define _GRID_H_

#include "NumberPiece.h"

#define GRID_SIZE 110

class Grid
{
public:
	Grid(): number_piece(NULL) {}
	Grid(int r, int c): row(r), col(c), number_piece(NULL) {}

	void setPos(int r, int c);
	void placeNumberPiece();
	void setNumberPiece(NumberPiece *np, bool remove_old = false);
	NumberPiece *getNumberPiece();
	bool isFree();
private:
	int row;
	int col;
	NumberPiece *number_piece;
};

#endif