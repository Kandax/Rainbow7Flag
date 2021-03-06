#include "PolygonObject.h"

static constexpr float M_PI = 3.14159265359f;
static constexpr float ToDegrees = 180 / M_PI;


PolygonObject::PolygonObject()
	:mPosition(0,0)
	,mWidth(1)
	,mHeight(1)
	,mScale(16)
	,mWidthCollision(1)
	,mHeightCollision(1)
{
	
}

PolygonObject::PolygonObject(b2World* world, b2BodyType bodyType, float positionX, float positionY, float boxWidthInPixels, float boxHeightInPixels)
	: mWorld(world)
	, mPosition{ positionX, positionY }
	, mWidth(boxWidthInPixels)
	, mHeight(boxHeightInPixels)
	, mScale(16)
	, mWidthCollision(mWidth)
	, mHeightCollision(mHeight)
{

	
	mSfShape.setPointCount(4);
	mSfShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	mSfShape.setPoint(1, sf::Vector2f(mWidth, 0));//1,0
	mSfShape.setPoint(2, sf::Vector2f(mWidth,mHeight));//1,1
	mSfShape.setPoint(3, sf::Vector2f(0, mHeight));//0,1

	mSfShape.setOrigin(sf::Vector2f(mWidth / 2, mHeight / 2));
	

	
	
	mCollisionShape.setPointCount(4);
	mCollisionShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	mCollisionShape.setPoint(1, sf::Vector2f(mWidth, 0));//1,0
	mCollisionShape.setPoint(2, sf::Vector2f(mWidth, mHeight));//1,1
	mCollisionShape.setPoint(3, sf::Vector2f(0, mHeight));//0,1

	mCollisionShape.setOrigin(sf::Vector2f(mWidth / 2, mHeight / 2));

	mCollisionShape.setOutlineColor(sf::Color::Color(0,255,0,200));
	mCollisionShape.setFillColor(sf::Color::Color(0, 255, 0, 50));

	mCollisionShape.setOutlineThickness(1);
	


	mBodyDef.type = bodyType;
	mBodyDef.position.Set(mPosition.x/mScale, mPosition.y / mScale);
	////////////////
	mBodyDef.allowSleep = true;
	///////////////
	mBody = mWorld->CreateBody(&mBodyDef);

	mB2Shape.SetAsBox(mWidthCollision /mScale / 2, mHeightCollision / mScale / 2);

	mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 10.f;
	mFixtureDef.friction = 1.f;

	
	
	mFixture = mBody->CreateFixture(&mFixtureDef);
	

}

PolygonObject::PolygonObject(b2World* world, b2BodyType bodyType, float positionX, float positionY, float boxWidthInPixels, float boxHeightInPixels, float CollisionBoxWidthInPixels, float CollisionBoxHeightInPixels)
	: mWorld(world)
	, mPosition{ positionX, positionY }
	, mWidth(boxWidthInPixels)
	, mHeight(boxHeightInPixels)
	, mScale(16)
	, mWidthCollision(CollisionBoxWidthInPixels)
	, mHeightCollision(CollisionBoxHeightInPixels)
{
	mSfShape.setPointCount(4);
	mSfShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	mSfShape.setPoint(1, sf::Vector2f(mWidth, 0));//1,0
	mSfShape.setPoint(2, sf::Vector2f(mWidth, mHeight));//1,1
	mSfShape.setPoint(3, sf::Vector2f(0, mHeight));//0,1

	mSfShape.setOrigin(sf::Vector2f(mWidth / 2, mHeight / 2));


	mCollisionShape.setPointCount(4);
	mCollisionShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	mCollisionShape.setPoint(1, sf::Vector2f(mWidthCollision, 0));//1,0
	mCollisionShape.setPoint(2, sf::Vector2f(mWidthCollision, mHeightCollision));//1,1
	mCollisionShape.setPoint(3, sf::Vector2f(0, mHeightCollision));//0,1

	mCollisionShape.setOrigin(sf::Vector2f(mWidthCollision / 2, mHeightCollision / 2));

	mCollisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
	mCollisionShape.setFillColor(sf::Color::Color(0, 255, 0, 50));

	mCollisionShape.setOutlineThickness(1);


	mBodyDef.type = bodyType;
	mBodyDef.position.Set(mPosition.x / mScale, mPosition.y / mScale);
	////////////
	mBodyDef.bullet = true;
	////////////

	mBody = mWorld->CreateBody(&mBodyDef);

	mB2Shape.SetAsBox(mWidthCollision / mScale / 2, mHeightCollision / mScale / 2);

	mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 10.f;
	mFixtureDef.friction = 1.f;

	mFixture = mBody->CreateFixture(&mFixtureDef);
	
}

PolygonObject::~PolygonObject()
{
	//mWorld->DestroyBody(mBody);
	mBody = nullptr;
}

void PolygonObject::update()
{


	


	mPosition.Set(mBody->GetPosition().x * mScale, mBody->GetPosition().y * mScale);
	mRotation = mBody->GetAngle() * ToDegrees;


	

	
	mSfShape.setPosition(sf::Vector2f(mPosition.x, mPosition.y));
	mSfShape.setRotation(mRotation);

	mCollisionShape.setPosition(sf::Vector2f(mPosition.x, mPosition.y));
	mCollisionShape.setRotation(mRotation);
	

}

void PolygonObject::draw(sf::RenderWindow* window)
{
	window->draw(mSfShape);
}

void PolygonObject::drawCollision(sf::RenderWindow* window)
{
	if (mBody->IsAwake()) {
		mCollisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
	}
	else {
		mCollisionShape.setOutlineColor(sf::Color::Color(255, 0, 0, 200));
	}



	window->draw(mCollisionShape);
}

void PolygonObject::destroy()
{
	mWorld->DestroyBody(mBody);
	mBody = nullptr;
}

b2Vec2 PolygonObject::getPosition() const
{
	return mPosition;
}

sf::ConvexShape* PolygonObject::getRenderShape()
{
	return &mSfShape;
}

b2Body* PolygonObject::getBody()
{
	return mBody;
}

b2BodyDef& PolygonObject::getBodyDef()
{
	return mBodyDef;
}

b2Fixture* PolygonObject::getFixture()
{
	return mFixture;
}



float PolygonObject::getRotation() const
{
	return mRotation;
}
