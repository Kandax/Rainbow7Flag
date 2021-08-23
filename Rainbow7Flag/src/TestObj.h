#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"


class TestObj
{
public:

	TestObj(b2World* world,float posX,float posY);
	~TestObj();
	void update();
	void draw(sf::RenderWindow* window);
private:

	float mScale;

	b2World* mWorld;
	b2BodyDef mBodyDef;
	b2Body* mBody;
	sf::RectangleShape mSFBodyShape;

	b2PolygonShape mShape;
	b2FixtureDef mFixtureDef;
	b2Fixture* mFixture;
	b2Fixture* mFixture2;



};

