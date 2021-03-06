#include "Game.h"
#include "Board.h"
#include <sstream>

using namespace std;

Game *Game::game = NULL;
Layer *Game::lose_layer = NULL;
Layer *Game::pieces_layer = NULL;
LabelTTF *Game::grade_label = NULL;
Sprite *Game::layers_sprite[3];
int Game::state = 0;
int Game::grade = 0;

bool Game::initGame()
{
	game = new Game();

	Size s(800, 600);

	if(game->initWithSize(s)) {
		game->setUp();

		return true;
	}

	CC_SAFE_DELETE(game);
	return false;
}

void Game::setUp()
{
	setPosition(0, 0);

	pieces_layer = Layer::create();
	lose_layer = Layer::create();
	Layer *background_layer = Layer::create();

	addChild(background_layer);
	addChild(pieces_layer);
	addChild(lose_layer);

	// show grade
	grade_label = LabelTTF::create("Your grade: 0", "Arial", 30);
	pieces_layer->addChild(grade_label);
	grade_label->setPosition(400, 550);
	updateGrade();


	// set the background layer
	Texture2D *bg_img = TextureCache::getInstance()->addImage("background.png");
	Sprite *bg_sprite = Sprite::createWithTexture(bg_img);
	bg_sprite->setPosition(400, 300);
	background_layer->addChild(bg_sprite);

	Texture2D *layer0_img = TextureCache::getInstance()->addImage("layer0.png");
	layers_sprite[0] = Sprite::createWithTexture(layer0_img);
	layers_sprite[0]->setPosition(400, 300);
	background_layer->addChild(layers_sprite[0]);

	Texture2D *layer1_img = TextureCache::getInstance()->addImage("layer1.png");
	layers_sprite[1] = Sprite::createWithTexture(layer1_img);
	layers_sprite[1]->setPosition(400, 300);
	background_layer->addChild(layers_sprite[1]);

	Texture2D *layer2_img = TextureCache::getInstance()->addImage("layer2.png");
	layers_sprite[2] = Sprite::createWithTexture(layer2_img);
	layers_sprite[2]->setPosition(400, 300);
	background_layer->addChild(layers_sprite[2]);



	// set the lose layer
	Texture2D *lose_img = TextureCache::getInstance()->addImage("lose.png");
	Sprite *lose_sprite = Sprite::createWithTexture(lose_img);
	lose_sprite->setOpacity(180);
	lose_sprite->setPosition(400, 300);
	lose_layer->addChild(lose_sprite);
	lose_layer->runAction(Hide::create());

	// listen keyboard event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=] (EventKeyboard::KeyCode key_code, Event *event) {
		log("Key code %d", key_code);

		Board *board = Board::getInstance();

		if (state == 0) {
			switch (key_code) {
				case 25: board->moveUp(); break;
				case 26: board->moveDown(); break;
				case 23: board->moveLeft(); break;
				case 24: board->moveRight(); break;
				case 56: board->changeLayer(); break;
			}
		}
		else {
			if ((int)key_code == 32) {
				Game::grade = 0;
				Game::updateGrade();

				board->clear();
				Game::lose_layer->runAction(Hide::create());
				state = 0;
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void Game::lose()
{
	lose_layer->runAction(Show::create());
	state = 1;
}

void Game::updateGrade()
{
	ostringstream os;
	os << "Your grade: " << grade;

	grade_label->setString(os.str());
}