#include "NumberPiece.h"
#include "Board.h"
#include "Game.h"
#include <sstream>

using namespace std;

NumberPiece::NumberPiece()
{
	if (rand() % 4 == 0) {
		number = 4;
	}
	else {
		number = 2;
	}
}


NumberPiece::~NumberPiece()
{
}

NumberPiece *NumberPiece::create(int row, int col)
{
	NumberPiece *number_piece = new NumberPiece();

	ostringstream file;
	file << "piece" << number_piece->number << ".png";
	Texture2D *image = TextureCache::getInstance()->addImage(file.str());

	if (number_piece->initWithTexture(image)) {
		number_piece->autorelease();

		number_piece->updatePosition(row, col, 1);

		ostringstream os;
		os << number_piece->number;
		LabelTTF *label = LabelTTF::create(os.str(), "Arial", 40);
		label->setPosition(Vec2(50, 50));
		number_piece->addChild(label, 0, 0);

		Game::pieces_layer->addChild(number_piece);

		return number_piece;
	}

	CC_SAFE_DELETE(number_piece);
	return NULL;
}

void NumberPiece::doubleNumber()
{
	number *= 2;

	Game::grade += number;
	Game::updateGrade();

	ostringstream file;
	file << "piece" << number << ".png";
	Texture2D *image = TextureCache::getInstance()->addImage(file.str());

	setTexture(image);

	ostringstream os;
	os << number;

	LabelTTF *label = (LabelTTF *)getChildByTag(0);
	label->setString(os.str());

	ScaleTo *act1 = ScaleTo::create(0.05, 0.8, 0.8);
	ScaleTo *act2 = ScaleTo::create(0.05, 1, 1);

	runAction(Sequence::create(act1, act2, NULL));
}

void NumberPiece::updatePosition(int row, int col, int act)
{
	x = 250 + col * NUMBER_PIECE_SIZE;
	y = 150 + (BOARD_SIZE - 1 - row) * NUMBER_PIECE_SIZE;

	if (act == 0) {
		MoveTo *act = MoveTo::create(0.05, Vec2(x, y));
		runAction(act);
	}
	else if(act == 1) {
		setPosition(x, y);

		ScaleTo *act1 = ScaleTo::create(0.05, 0.8, 0.8);
		ScaleTo *act2 = ScaleTo::create(0.05, 1, 1);

		runAction(Sequence::create(act1, act2, NULL));
	}
}

int NumberPiece::getNumber()
{
	return number;
}