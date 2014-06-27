#ifndef _NUMBER_PIECE_H_
#define _NUMBER_PIECE_H_

#include "cocos2d.h"

using namespace cocos2d;

#define NUMBER_PIECE_SIZE 100

class NumberPiece: public Sprite
{
public:
	NumberPiece();
	NumberPiece(int n): number(n) {}
	~NumberPiece();

	static NumberPiece *create(int row, int col);
	void doubleNumber();
	void updatePosition(int row, int col, int act = 0);
	int getNumber();
private:
	int number;
	float x, y;
};

#endif

