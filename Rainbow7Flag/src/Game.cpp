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
	, mPOS1(&mWorld, b2_staticBody, 300, 300, 200, 20)
{
	float lSize = 100;

	mPO1.addComponent(100, 100 , lSize, lSize);
	//mPO1.getComponent(1).fixture->SetSensor(true);
	mPO1.getComponent(0).renderShape.setFillColor(sf::Color::Color(0,0,255,150));
	mPO1.addComponent(0, -50, 20,50);
	mPO1.getBody()->SetGravityScale(1);
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


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		mMove.Set(0, -10);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		mMove.Set(0, 10);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mMove.Set(10, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		mMove.Set(-10, 0);
	}
	else {
		mMove.Set(0, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		mPO1.getBody()->ApplyTorque(-4000, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		mPO1.getBody()->ApplyTorque(4000, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		mPO1.deleteParentFixture();
	}

}

void Game::updatePhysics()
{


	//mGravity.Set(0, 10 * mETime.getElapsedTime());
	//mWorld.SetGravity(mGravity);
	mPO1.getBody()->SetLinearVelocity(mMove);


	mWorld.Step(mTimeStep, mVelocityIterations, positionIterations);
	
}

void Game::update()
{

	mPO1.update();
	mPOS1.update();
}

void Game::render()
{

	std::cout <<"Time used: "<<mETime.getTimeUsed() * 1000<< " ms Elapsed Time: " << mETime.getElapsedTime() * 1000<< " ms " << std::endl;

	
	mWindow.clear();
	mPO1.draw(&mWindow);
	mPOS1.draw(&mWindow);
	if (mShowCollision) {
		mPO1.drawCollision(&mWindow);
		mPOS1.drawCollision(&mWindow);
	}
	mWindow.display();



}
