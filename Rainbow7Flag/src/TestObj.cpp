#include "TestObj.h"



static constexpr float M_PI = 3.14159265359f;
static constexpr float ToDegrees = 180 / M_PI;

TestObj::TestObj(b2World* world,float posX, float posY)
	:mScale(16)
	,mWorld(world)
{
	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set(posX / mScale, posY / mScale);

	mBody = mWorld->CreateBody(&mBodyDef);

	float boxSize = 50;

	mSFBodyShape.setSize(sf::Vector2f(boxSize, boxSize));
	mSFBodyShape.setOrigin(sf::Vector2f(boxSize / 2, boxSize / 2));
	mShape.SetAsBox(boxSize / mScale / 2, boxSize / mScale / 2);

	mFixtureDef.shape = &mShape;
	mFixtureDef.friction = 1.f;
	mFixtureDef.density = 10.f;

	mFixture = mBody->CreateFixture(&mFixtureDef);


}

TestObj::~TestObj()
{
	//mBody->DestroyFixture(mFixture);
	//mFixture = nullptr;


	mWorld->DestroyBody(mBody);
	mBody = nullptr;
}

void TestObj::update()
{
	if (mBody != nullptr) {
		mSFBodyShape.setPosition(sf::Vector2f(mBody->GetPosition().x * mScale, mBody->GetPosition().y * mScale));
		mSFBodyShape.setRotation(mBody->GetAngle() * ToDegrees);

	}




}

void TestObj::draw(sf::RenderWindow* window)
{
	if(mBody != nullptr)
		window->draw(mSFBodyShape);
}
