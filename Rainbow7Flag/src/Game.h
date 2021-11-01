#pragma once
#include <string>
#include <iostream>
#include <vector>


#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "ElapsedTime.h"
#include "Object.h"
#include "PolygonObject.h"
#include "TestObj.h"


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void events();
	void input();
	void updatePhysics();
	void update();
	void render();

private:

	uint16_t mWindowWidth;
	uint16_t mWindowHeight;
	std::string mWindowName;

	sf::RenderWindow mWindow;
	sf::Event mEvent;
	ElapsedTime mETime;

	b2Vec2 mGravity;
	b2World mWorld;

	float mTimeStep;
	int32 mVelocityIterations;
	int32 positionIterations;


	float mScale;

	PolygonObject mPO1, mPOS1;


	b2BodyDef mBodyDef;
	b2Body* mBody;
	sf::RectangleShape mSFBodyShape;

	b2PolygonShape mShape;
	b2FixtureDef mFixtureDef;
	b2Fixture* mFixture;
	b2Fixture* mFixture2;


	TestObj *mObj1;
	TestObj mObj2;
	std::vector<TestObj> mObjects;
};

