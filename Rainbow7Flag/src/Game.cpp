#include "Game.h"

Game::Game()
	:mWindowWidth(800)
	, mWindowHeight(600)
	, mWindowName("Rainbow7Flag")
	, mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), mWindowName)
{



}

void Game::run()
{
	while (mWindow.isOpen()) {
		events();
		input();
		updatePhysics();
		update();
		render();
	}

}

void Game::events()
{
	while (mWindow.pollEvent(mEvent)) {
		switch (mEvent.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}


}

void Game::input()
{
}

void Game::updatePhysics()
{
}

void Game::update()
{
}

void Game::render()
{
	mWindow.clear();

	mWindow.display();



}
