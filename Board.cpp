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
	layer = LAYER_NUM - 1;

	for (int i = 0; i < layer; ++i) {
		Game::layers_sprite[i]->runAction(Hide::create());
	}	
	Game::layers_sprite[layer]->runAction(Show::create());
	

	for (int i = 0; i < LAYER_NUM; ++i) {
		for (int j = 0; j < LAYER_SIZE; ++j) {
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

	for (int col = 0; col < LAYER_SIZE; ++col) {
		int move_step = 0;
		for (int row = 0; row < LAYER_NUM; ++row) {
			NumberPiece *number_piece = grids[row][col].getNumberPiece();
			
			if (number_piece) {
				bool merge = false;
				//double
				if (move_step && !grids[row - move_step][col].isFree()) {
					number_piece->doubleNumber();
					merge = true;
				}

				//move
				if (move_step) {
					grids[row][col].setNumberPiece(NULL);
					grids[row - move_step][col].setNumberPiece(number_piece, true);

					can_move = true;
				}

				

				if (!merge) {
					for (int j = row + 1; j < LAYER_NUM; ++j) {
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

	for (int col = 0; col < LAYER_SIZE; ++col) {
		int move_step = 0;
		for (int row = LAYER_NUM - 1; row >= 0; --row) {
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
	for (int i = 0; i < LAYER_SIZE; ++i) {
		if (grids[layer][i].getNumberPiece() != NULL) {
			can_move = true;
			break;
		}
	}

	if (can_move && getFreeGrids().size() > 0) {

		NumberPiece *first = grids[layer][0].getNumberPiece();
		for (int i = 1; i < LAYER_SIZE; ++i) {
			grids[layer][i - 1].setNumberPiece(grids[layer][i].getNumberPiece());
		}
		grids[layer][LAYER_SIZE - 1].setNumberPiece(first);
		addNumberPiece();
	}
}

void Board::moveRight()
{
	bool can_move = false;
	for (int i = 0; i < LAYER_SIZE; ++i) {
		if (grids[layer][i].getNumberPiece() != NULL) {
			can_move = true;
			break;
		}
	}

	if (can_move && getFreeGrids().size() > 0) {
		NumberPiece *last = grids[layer][LAYER_SIZE - 1].getNumberPiece();
		for (int i = LAYER_SIZE - 2; i >= 0; --i) {
			grids[layer][i + 1].setNumberPiece(grids[layer][i].getNumberPiece());
		}
		grids[layer][0].setNumberPiece(last);
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

void Board::changeLayer()
{
	Game::layers_sprite[layer]->runAction(Hide::create());

	layer--;

	if (layer < 0)
		layer = LAYER_NUM - 1;

	Game::layers_sprite[layer]->runAction(Show::create());

}

vector<Grid *> Board::getFreeGrids()
{
	vector<Grid *> free_grids;

	for (int i = 0; i < LAYER_NUM; ++i) {
		for (int j = 0; j < LAYER_SIZE; ++j) {
			if (grids[i][j].isFree()) {
				free_grids.push_back(&grids[i][j]);
			}
		}
	}

	return free_grids;
}

bool Board::judgeEnd() 
{
	for (int i = 0; i < LAYER_NUM - 1; ++i) {
		for (int j = 0; j < LAYER_SIZE; ++j) {
			// compare up-down pairs
			if (grids[i][j].getNumberPiece()->getNumber() ==
				grids[i + 1][j].getNumberPiece()->getNumber()) {
				return false;
			}
		}
	}

	return true;
}