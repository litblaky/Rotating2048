#include "Grid.h"
#include "Game.h"

void Grid::placeNumberPiece()
{
	NumberPiece *np = NumberPiece::create(row, col);
	number_piece = np;
}

bool Grid::isFree()
{
	return number_piece == NULL;
}

void Grid::setPos(int r, int c) 
{
	row = r;
	col = c;
}

void Grid::setNumberPiece(NumberPiece *np, bool remove_old)
{

	if (number_piece != NULL && remove_old) {
		Game::pieces_layer->removeChild(number_piece);
	}

	if (np != NULL) {
		np->updatePosition(row, col);
	} 

	number_piece = np;
}

NumberPiece *Grid::getNumberPiece()
{
	return number_piece;
}