#include "Component.h"


Component::Component()
{
}

Component::Component(b2Body* body, float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels)
	:mBody(body)
{
	
	renderShape.setPointCount(4);
	renderShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	renderShape.setPoint(1, sf::Vector2f(boxWidthInPixels, 0));//1,0
	renderShape.setPoint(2, sf::Vector2f(boxWidthInPixels, boxHeightInPixels));//1,1
	renderShape.setPoint(3, sf::Vector2f(0, boxHeightInPixels));//0,1

	//sfShape.setFillColor(sf::Color::Color(0, 255, 255, 255));

	renderShape.setOrigin(sf::Vector2f(boxWidthInPixels / 2 - offsetX, boxHeightInPixels / 2 - offsetY));


	renderCollisionShape.setPointCount(4);
	renderCollisionShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	renderCollisionShape.setPoint(1, sf::Vector2f(boxWidthInPixels, 0));//1,0
	renderCollisionShape.setPoint(2, sf::Vector2f(boxWidthInPixels, boxHeightInPixels));//1,1
	renderCollisionShape.setPoint(3, sf::Vector2f(0, boxHeightInPixels));//0,1

	renderCollisionShape.setOrigin(sf::Vector2f(boxWidthInPixels / 2 - offsetX, boxHeightInPixels / 2 - offsetY));

	renderCollisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
	renderCollisionShape.setFillColor(sf::Color::Color(0, 255, 0, 50));

	renderCollisionShape.setOutlineThickness(1);



	b2Vec2 offset;
	offset.Set(offsetX / mScale, offsetY / mScale);
	mB2Shape.SetAsBox(boxWidthInPixels / mScale * 0.5f, boxHeightInPixels / mScale * 0.5f, offset, body->GetAngle());

	/*mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 10.f;
	mFixtureDef.friction = 1.f;

	fixture = mBody->CreateFixture(&mFixtureDef);*/

}

Component::Component(b2Body* body, float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels, float collisionBoxWidthInPixels, float collisionBoxHeightInPixels)
	:mBody(body)
{
	renderShape.setPointCount(4);
	renderShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	renderShape.setPoint(1, sf::Vector2f(boxWidthInPixels, 0));//1,0
	renderShape.setPoint(2, sf::Vector2f(boxWidthInPixels, boxHeightInPixels));//1,1
	renderShape.setPoint(3, sf::Vector2f(0, boxHeightInPixels));//0,1

	//sfShape.setFillColor(sf::Color::Color(0, 255, 255, 255));

	renderShape.setOrigin(sf::Vector2f(boxWidthInPixels / 2 - offsetX, boxHeightInPixels / 2 - offsetY));


	renderCollisionShape.setPointCount(4);
	renderCollisionShape.setPoint(0, sf::Vector2f(0, 0));//0,0
	renderCollisionShape.setPoint(1, sf::Vector2f(collisionBoxWidthInPixels, 0));//1,0
	renderCollisionShape.setPoint(2, sf::Vector2f(collisionBoxWidthInPixels, collisionBoxHeightInPixels));//1,1
	renderCollisionShape.setPoint(3, sf::Vector2f(0, collisionBoxHeightInPixels));//0,1

	renderCollisionShape.setOrigin(sf::Vector2f(collisionBoxWidthInPixels / 2 - offsetX, collisionBoxHeightInPixels / 2 - offsetY));

	renderCollisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
	renderCollisionShape.setFillColor(sf::Color::Color(0, 255, 0, 50));

	renderCollisionShape.setOutlineThickness(1);



	b2Vec2 offset;
	offset.Set(offsetX / mScale, offsetY / mScale);
	mB2Shape.SetAsBox(collisionBoxWidthInPixels / mScale * 0.5f, collisionBoxHeightInPixels / mScale * 0.5f, offset, body->GetAngle());

	/*mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = 0.f;
	mFixtureDef.friction = 1.f;

	fixture = mBody->CreateFixture(&mFixtureDef);*/
}

Component::~Component()
{
	//mBody->DestroyFixture(fixture);
}

void Component::setStartingFixture(float density, float friction)
{
	mFixtureDef.shape = &mB2Shape;
	mFixtureDef.density = density;
	mFixtureDef.friction = friction;


	fixture = mBody->CreateFixture(&mFixtureDef);
}

sf::ConvexShape& Component::getRenderShape()
{
	return renderShape;
}

sf::ConvexShape& Component::getRenderCollisionShape()
{
	return renderCollisionShape;
}

b2Fixture* Component::getFixture()
{
	return fixture;
}
