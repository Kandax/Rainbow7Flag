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
	, isDestroyedBody(false)
{

	mBodyDef.type = bodyType;
	mBodyDef.position.Set(mPosition.x/mScale, mPosition.y / mScale);
	////////////////
	//mBodyDef.allowSleep = true;
	///////////////
	mBody = mWorld->CreateBody(&mBodyDef);

	mCompontents.push_back(Component(mBody, 0, 0, boxWidthInPixels, boxHeightInPixels));

	mB2Shape.SetAsBox(mWidthCollision /mScale / 2, mHeightCollision / mScale / 2);

	mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 10.f;
	mFixtureDef.friction = 1.f;

	
	
	mCompontents.back().fixture = mBody->CreateFixture(&mFixtureDef);
	

}

PolygonObject::PolygonObject(b2World* world, b2BodyType bodyType, float positionX, float positionY, float boxWidthInPixels, float boxHeightInPixels, float CollisionBoxWidthInPixels, float CollisionBoxHeightInPixels)
	: mWorld(world)
	, mPosition{ positionX, positionY }
	, mWidth(boxWidthInPixels)
	, mHeight(boxHeightInPixels)
	, mScale(16)
	, mWidthCollision(CollisionBoxWidthInPixels)
	, mHeightCollision(CollisionBoxHeightInPixels)
	, isDestroyedBody(false)
{
	


	mBodyDef.type = bodyType;
	mBodyDef.position.Set(mPosition.x / mScale, mPosition.y / mScale);
	////////////////
	//mBodyDef.allowSleep = true;
	///////////////
	mBody = mWorld->CreateBody(&mBodyDef);

	mCompontents.push_back(Component(mBody, 0, 0, boxWidthInPixels, boxHeightInPixels,CollisionBoxWidthInPixels,CollisionBoxHeightInPixels));

	mB2Shape.SetAsBox(mWidthCollision / mScale / 2, mHeightCollision / mScale / 2);

	mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 10.f;
	mFixtureDef.friction = 1.f;



	mCompontents.back().fixture = mBody->CreateFixture(&mFixtureDef);
	
}

PolygonObject::~PolygonObject()
{
	//mCompontents.clear();
	/*if (!isDestroyedBody) {

		mWorld->DestroyBody(mBody);
	}*/
	//mBody = nullptr;
	//mBody->DestroyFixture(mCompontents.back().fixture);
	
	//mWorld->DestroyBody(mBody);
	destroy();

}

void PolygonObject::update()
{


	


	mPosition.Set(mBody->GetPosition().x * mScale, mBody->GetPosition().y * mScale);
	mRotation = mBody->GetAngle() * ToDegrees;

	for (auto& lCompontent : mCompontents) {

		lCompontent.renderShape.setPosition(sf::Vector2f(mPosition.x, mPosition.y));
		lCompontent.renderShape.setRotation(mRotation);

		lCompontent.renderCollisionShape.setPosition(sf::Vector2f(mPosition.x, mPosition.y));
		lCompontent.renderCollisionShape.setRotation(mRotation);
	}	
}

void PolygonObject::draw(sf::RenderWindow* window)
{
	for (int i = mCompontents.size() - 1; i >= 0; --i) {
		window->draw(mCompontents[i].renderShape);
	}
	
}

void PolygonObject::drawCollision(sf::RenderWindow* window)
{
	for (int i = mCompontents.size() - 1; i >= 0; --i) {
		


		if (mBody->IsAwake()) {
			mCompontents[i].renderCollisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
		}
		else {
			mCompontents[i].renderCollisionShape.setOutlineColor(sf::Color::Color(255, 0, 0, 200));
		}

		window->draw(mCompontents[i].renderCollisionShape);
	}

	
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

Component& PolygonObject::getComponent(int id)
{
	return mCompontents.at(id);
}

void PolygonObject::addComponent( float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels)
{
	mCompontents.push_back(Component(mBody, offsetX, offsetY, boxWidthInPixels, boxHeightInPixels));
	mCompontents.back().setStartingFixture();
}

void PolygonObject::addComponent(float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels, float collisionBoxWidthInPixels, float collisionBoxHeightInPixels)
{
	mCompontents.push_back(Component(mBody, offsetX, offsetY, boxWidthInPixels, boxHeightInPixels, collisionBoxWidthInPixels, collisionBoxHeightInPixels));
	mCompontents.back().setStartingFixture();
}



float PolygonObject::getRotation() const
{
	return mRotation;
}

void PolygonObject::deleteParentFixture()
{
	
	if (!isDestroyedBody) {
		mBody->DestroyFixture(mCompontents.front().fixture);
		mFixture = nullptr;
		mWorld->DestroyBody(mBody);
		isDestroyedBody = true;
		std::cout << "is destroyed" << std::endl;
	}
	else {

		std::cout << "is already destroyed" << std::endl;
	}
}
