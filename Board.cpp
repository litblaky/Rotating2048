#include "Board.h"
#include "Game.h"

using namespace std;

Board *Board::instance = NULL;

Board *Board::getInstance()
{
	if (!instance) {
		instance = new Board();
	}

	return instance;
}

void Board::clear()
{
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			grids[i][j].setPos(i, j);
			grids[i][j].setNumberPiece(NULL, true);
		}
	}

	addNumberPiece();
	addNumberPiece();
}

Board::Board()
{
	clear();
}


Board::~Board()
{
}

void Board::moveUp()
{
	bool can_move = false;

	for (int col = 0; col < BOARD_SIZE; ++col) {
		int move_step = 0;
		for (int row = 0; row < BOARD_SIZE; ++row) {
			NumberPiece *number_piece = grids[row][col].getNumberPiece();
			
			if (number_piece) {
				bool merge = false;
				//move
				if (move_step) {
					grids[row][col].setNumberPiece(NULL);
					grids[row - move_step][col].setNumberPiece(number_piece, true);

					can_move = true;
				}

				//double
				if (move_step && !grids[row - move_step][col].isFree()) {
					number_piece->doubleNumber();
					merge = true;
				}

				

				if (!merge) {
					for (int j = row + 1; j < BOARD_SIZE; ++j) {
						if (!grids[j][col].isFree()) {
							NumberPiece *next_np = grids[j][col].getNumberPiece();

							if (next_np->getNumber() == number_piece->getNumber()) {
								move_step++;
							}

							break;
						}
					}
				}
			}
			else {
				move_step++;
			}
			
		}

	}

	if (can_move) {
		addNumberPiece();
	}
}

void Board::moveDown()
{
	bool can_move = false;

	for (int col = 0; col < BOARD_SIZE; ++col) {
		int move_step = 0;
		for (int row = BOARD_SIZE - 1; row >= 0; --row) {
			NumberPiece *number_piece = grids[row][col].getNumberPiece();
			
			if (number_piece) {
				bool merge = false;
				//double
				if (move_step && !grids[row + move_step][col].isFree()) {
					number_piece->doubleNumber();
					merge = true;
				}

				//move
				if (move_step) {
					grids[row][col].setNumberPiece(NULL);
					grids[row + move_step][col].setNumberPiece(number_piece, true);

					can_move = true;
				}

				if (!merge) {
					for (int j = row - 1; j >= 0; --j) {
						if (!grids[j][col].isFree()) {
							NumberPiece *next_np = grids[j][col].getNumberPiece();

							if (next_np->getNumber() == number_piece->getNumber()) {
								move_step++;
							}

							break;
						}
					}
				}
			}
			else {
				move_step++;
			}
			
		}

	}

	if (can_move) {
		addNumberPiece();
	}
}

void Board::moveLeft()
{
	bool can_move = false;

	for (int row = 0; row < BOARD_SIZE; ++row) {
		int move_step = 0;
		for (int col = 0; col < BOARD_SIZE; ++col) {
			NumberPiece *number_piece = grids[row][col].getNumberPiece();
			
			if (number_piece) {
				bool merge = false;
				//double
				if (move_step && !grids[row][col - move_step].isFree()) {
					number_piece->doubleNumber();
					merge = true;
				}

				//move
				if (move_step) {
					grids[row][col].setNumberPiece(NULL);
					grids[row][col - move_step].setNumberPiece(number_piece, true);

					can_move = true;
				}

				if (!merge) {
					for (int j = col + 1; j < BOARD_SIZE; ++j) {
						if (!grids[row][j].isFree()) {
							NumberPiece *next_np = grids[row][j].getNumberPiece();

							if (next_np->getNumber() == number_piece->getNumber()) {
								move_step++;
							}

							break;
						}
					}
				}
			}
			else {
				move_step++;
			}
			
		}

	}


	if (can_move) {
		addNumberPiece();
	}
}

void Board::moveRight()
{
	bool can_move = false;

	for (int row = 0; row < BOARD_SIZE; ++row) {
		int move_step = 0;
		for (int col = BOARD_SIZE - 1; col >= 0; --col) {
			NumberPiece *number_piece = grids[row][col].getNumberPiece();
			
			if (number_piece) {
				bool merge = false;
				//double
				if (move_step && !grids[row][col + move_step].isFree()) {
					number_piece->doubleNumber();
					merge = true;
				}
				

				//move
				if (move_step) {
					grids[row][col].setNumberPiece(NULL);
					grids[row][col + move_step].setNumberPiece(number_piece, true);
					
					can_move = true;
				}

				if (!merge) {
					for (int j = col - 1; j >= 0; --j) {
						if (!grids[row][j].isFree()) {
							NumberPiece *next_np = grids[row][j].getNumberPiece();

							if (next_np->getNumber() == number_piece->getNumber()) {
								move_step++;
							}

							break;
						}
					}
				}
			}
			else {
				move_step++;
			}
			
		}
	}

	if (can_move) {
		addNumberPiece();
	}
}

void Board::addNumberPiece()
{
	vector<Grid *> free_grids = getFreeGrids();

	int index = rand() % free_grids.size();

	free_grids[index]->placeNumberPiece();

	if (free_grids.size() == 1) {
		if (judgeEnd()) {
			// lose
			Game::lose();
		}
	}
}

vector<Grid *> Board::getFreeGrids()
{
	vector<Grid *> free_grids;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (grids[i][j].isFree()) {
				free_grids.push_back(&grids[i][j]);
			}
		}
	}

	return free_grids;
}

bool Board::judgeEnd() 
{
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			// compare up-down pairs
			if (i < BOARD_SIZE - 1) {
				if (grids[i][j].getNumberPiece()->getNumber() ==
					grids[i + 1][j].getNumberPiece()->getNumber())
					return false;
			}

			// compare left-right pairs
			if (j < BOARD_SIZE - 1) {
				if (grids[i][j].getNumberPiece()->getNumber() ==
					grids[i][j + 1].getNumberPiece()->getNumber())
					return false;
			}
		}
	}

	return true;
}