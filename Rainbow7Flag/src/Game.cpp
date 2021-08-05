#include "Game.h"

Game::Game()
	:mWindowWidth(800)
	, mWindowHeight(600)
	, mWindowName("Rainbow7Flag")
	, mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), mWindowName)
	, mEvent()
	, mGravity(0.0f, 10.0f)
	, mWorld(mGravity)
	, mTimeStep(1.0f / 60.0f)
	, mVelocityIterations(6)
	, positionIterations(2)
	, mShowCollision(false)
	, mPO1(&mWorld, b2_dynamicBody, 100, 100, 100, 100)
	, mPOS1(&mWorld, b2_staticBody, 100, 00, 200, 20)
{
	float lSize = 300;

	mPO1.addComponent(10, 10 , lSize/2, lSize/2);

	

}

void Game::run()
{
	while (mWindow.isOpen()) {
		events();
		input();
		updatePhysics();
		update();
		render();
		mETime.run();
		
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1)) {
		mShowCollision = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2)) {
		mShowCollision = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		mWindow.close();
	}


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
	mPOS1.update();
}

void Game::render()
{

	std::cout <<"Time used: "<<mETime.getTimeUsed()<< " Elapsed Time" << mETime.getElapsedTime() << std::endl;

	
	mWindow.clear();
	mPO1.draw(&mWindow);
	mPOS1.draw(&mWindow);
	if (mShowCollision) {
		mPO1.drawCollision(&mWindow);
		mPOS1.drawCollision(&mWindow);
	}
	mWindow.display();



}
