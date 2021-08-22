#include "Game.h"


static constexpr float M_PI = 3.14159265359f;
static constexpr float ToDegrees = 180 / M_PI;


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
	, mScale(16)
	, mPO1(&mWorld, b2_dynamicBody, 100, -100, 100,100)
	, mPOS1(&mWorld,b2_staticBody, 100, 600,200,20)
{
	
	



	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set(100/ mScale, 0);

	mBody = mWorld.CreateBody(&mBodyDef);
	float sizeBox = 32;
	mShape.SetAsBox(sizeBox / mScale / 2 ,sizeBox / mScale / 2);
	mSFBodyShape.setSize(sf::Vector2f(sizeBox, sizeBox));
	mSFBodyShape.setOrigin(sf::Vector2f(sizeBox / 2, sizeBox / 2));

	mFixtureDef.shape = &mShape;
	mFixtureDef.density = 1000.f;
	mFixtureDef.friction = 1.f;

	mFixture = mBody->CreateFixture(&mFixtureDef);
	mFixture2 = mBody->CreateFixture(&mFixtureDef);
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
	static bool destroyed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		mPO1.getBody()->SetLinearVelocity(b2Vec2( 10,mPO1.getBody()->GetLinearVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		mPO1.getBody()->SetLinearVelocity(b2Vec2(-10, mPO1.getBody()->GetLinearVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		mPO1.getBody()->SetLinearVelocity(b2Vec2(mPO1.getBody()->GetLinearVelocity().x, -10));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!destroyed) {
			mWorld.DestroyBody(mBody);
			destroyed = true;
		}
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
	mSFBodyShape.setPosition(sf::Vector2f(mBody->GetPosition().x * mScale, mBody->GetPosition().y * mScale));
	mSFBodyShape.setRotation(mBody->GetAngle() * ToDegrees);
}

void Game::render()
{

	std::cout <<"Time used: "<<mETime.getTimeUsed()<< " Elapsed Time" << mETime.getElapsedTime() << std::endl;

	
	mWindow.clear();
	mPO1.draw(&mWindow);
	mPOS1.draw(&mWindow);
	mWindow.draw(mSFBodyShape);
	mWindow.display();



}
