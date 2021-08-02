#include "Game.h"

Game::Game()
	:mWindowWidth(800)
	, mWindowHeight(600)
	, mWindowName("Rainbow7Flag")
	, mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), mWindowName)
	, mEvent()
	, mGravity(0.0f,10.0f)
	, mWorld(mGravity)
	, mTimeStep(1.0f/60.0f)
	, mVelocityIterations(6)
	, positionIterations(2)
	, mPO1(&mWorld, b2_dynamicBody, 100, 100, 100,100)
{
	


}

void Game::run()
{
	while (mWindow.isOpen()) {
		mETime.run();
		events();
		input();
		updatePhysics();
		update();
		render();
		mETime.end();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mPO1.getBody()->SetLinearVelocity(b2Vec2( 10,mPO1.getBody()->GetLinearVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		mPO1.getBody()->SetLinearVelocity(b2Vec2(-10, mPO1.getBody()->GetLinearVelocity().y));
	}


}

void Game::updatePhysics()
{


	//mGravity.Set(0, 10 * mETime.getElapsedTime());
	//mWorld.SetGravity(mGravity);
	
	mWorld.Step(mTimeStep, mVelocityIterations, positionIterations);
	
}

void Game::update()
{

	mPO1.update();
}

void Game::render()
{

	std::cout <<"Time used: "<<mETime.getTimeUsed()<< " Elapsed Time" << mETime.getElapsedTime() << std::endl;

	
	mWindow.clear();
	mPO1.draw(&mWindow);
	mWindow.display();



}
