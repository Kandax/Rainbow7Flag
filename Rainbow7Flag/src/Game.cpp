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
	, mPO2(&mWorld, b2_dynamicBody, 300,250,50,50,25,25)
{
	float lSize = 100;

	mPO1.addComponent(100, 100 , lSize, lSize);
	//mPO1.getComponent(1).fixture->SetSensor(true);
	mPO1.getComponent(0).renderShape.setFillColor(sf::Color::Color(0,0,255,150));
	//mPO1.addComponent(0, -50, 20,50);
	//mPO1.getBody()->SetGravityScale(0);
	//mPO1.addComponent(200, 100, lSize, lSize, 10, 10);
	//mPO1.getComponent(0).fixture->SetDensity(10000);
	
	for (int i = 0; i < 10; i++) {


	mListOfObjects.push_back(PolygonObject(&mWorld, b2_dynamicBody, 300+ i*10 , 100, 100, 100));
	}


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
		//mPO1.deleteParentFixture();
		if (mListOfObjects.size() > 0) {
			//mListOfObjects.pop_back();
			mListOfObjects.clear();
		}
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
{/*
	if (mListOfObjects.size() > 0) {
		mListOfObjects.pop_back();
	}*/

	mPO1.update();
	mPOS1.update();
	mPO2.update();
	for (int i = 0; i < mListOfObjects.size(); i++) {
		mListOfObjects[i].update();

	}


}

void Game::render()
{

	std::cout <<"Time used: "<<mETime.getTimeUsed() * 1000<< " ms Elapsed Time: " << mETime.getElapsedTime() * 1000<< " ms " << std::endl;

	
	mWindow.clear();
	mPO1.draw(&mWindow);
	mPOS1.draw(&mWindow);
	mPO2.draw(&mWindow);
	for (int i = 0; i < mListOfObjects.size(); i++) {
		mListOfObjects[i].draw(&mWindow);

	}
	if (mShowCollision) {
		mPO1.drawCollision(&mWindow);
		mPOS1.drawCollision(&mWindow);
		mPO2.drawCollision(&mWindow);
		for (int i = 0; i < mListOfObjects.size(); i++) {
			mListOfObjects[i].drawCollision(&mWindow);

		}
	}
	mWindow.display();



}
