#pragma once
#include <iostream>
#include <vector>

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"


class Component
{
public:
	Component();
	Component(b2Body* body, float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels);
	Component(b2Body* body, float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels, float CollisionBoxWidthInPixels, float CollisionBoxHeightInPixels);
	~Component();
public:
	sf::ConvexShape& getRenderShape();
	sf::ConvexShape& getRenderCollisionShape();
	b2Fixture* getFixture();


public:
	sf::ConvexShape renderShape;
	sf::ConvexShape renderCollisionShape;

	b2Fixture* fixture;

private:

	b2PolygonShape mB2Shape;
	b2BodyDef mBodyDef;
	float mScale = 16;
	b2FixtureDef mFixtureDef;
	b2Body* mBody;
};

