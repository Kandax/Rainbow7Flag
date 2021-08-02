#pragma once
#include <string>
#include <iostream>


#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "ElapsedTime.h"
#include "Object.h"
#include "PolygonObject.h"


class Game
{
public:
	Game();
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


	PolygonObject mPO1;


};

