#pragma once

#include <vector>
#include <iostream>


#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Object.h"
#include "Component.h"





class PolygonObject : public Object
{
public:
	PolygonObject();	
	PolygonObject(b2World* world, b2BodyType bodyType, float positionX, float positionY, float boxWidthInPixels, float boxHeightInPixels);
	PolygonObject(b2World* world, b2BodyType bodyType, float positionX, float positionY, float boxWidthInPixels, float boxHeightInPixels,float CollisionBoxWidthInPixels, float CollisionBoxHeightInPixels);
	~PolygonObject();
	void update();
	void draw(sf::RenderWindow* window);
	void drawCollision(sf::RenderWindow* window);
	void destroy();


	b2Vec2 getPosition() const;


	sf::ConvexShape* getRenderShape();

	b2Body* getBody();
	b2BodyDef& getBodyDef();
	b2Fixture* getFixture();

	Component& getComponent(int id);
	void addComponent(float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels);


	float getRotation() const;
	void deleteParentFixture();

private:
	
	
	
	
	float mWidth;
	float mHeight;

	float mWidthCollision;
	float mHeightCollision;

	float mScale;
	float mRotation;

	b2Vec2 mPosition;
	b2World* mWorld;

	b2PolygonShape mB2Shape;

	std::vector<Component> mCompontents;

	sf::ConvexShape mSfShape;
	sf::ConvexShape mCollisionShape;

	b2Fixture* mFixture;
	

};

