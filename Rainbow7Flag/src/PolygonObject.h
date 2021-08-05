#pragma once

#include <vector>



#include "Object.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>


struct Component {
	
	Component() {

	}
	Component(b2Body* body, float offsetX, float offsetY, float boxWidthInPixels, float boxHeightInPixels ) 
		
	{
		//mBodyDef.type = bodyType;
	//	mBodyDef.position.Set(offsetX / mScale, offsetY / mScale);
		sfShape.setPointCount(4);
		sfShape.setPoint(0, sf::Vector2f(0, 0));//0,0
		sfShape.setPoint(1, sf::Vector2f(boxWidthInPixels, 0));//1,0
		sfShape.setPoint(2, sf::Vector2f(boxWidthInPixels, boxHeightInPixels));//1,1
		sfShape.setPoint(3, sf::Vector2f(0, boxHeightInPixels));//0,1

		sfShape.setFillColor(sf::Color::Color(0, 255, 255, 255));
		
		sfShape.setOrigin(sf::Vector2f(boxWidthInPixels / 2, boxHeightInPixels / 2));


		collisionShape.setPointCount(4);
		collisionShape.setPoint(0, sf::Vector2f(0, 0));//0,0
		collisionShape.setPoint(1, sf::Vector2f(boxWidthInPixels, 0));//1,0
		collisionShape.setPoint(2, sf::Vector2f(boxWidthInPixels, boxHeightInPixels));//1,1
		collisionShape.setPoint(3, sf::Vector2f(0, boxHeightInPixels));//0,1

		collisionShape.setOrigin(sf::Vector2f(boxWidthInPixels / 2, boxHeightInPixels / 2));

		collisionShape.setOutlineColor(sf::Color::Color(0, 255, 0, 200));
		collisionShape.setFillColor(sf::Color::Color(0, 255, 0, 50));

		collisionShape.setOutlineThickness(1);




		mB2Shape.SetAsBox(boxWidthInPixels * 0.5f, boxHeightInPixels * 0.5f, b2Vec2(offsetX,offsetY),0);
		
		mFixtureDef.shape = &mB2Shape;
		mFixtureDef.density = 10.f;
		mFixtureDef.friction = 1.f;

		fixture = body->CreateFixture(&mFixtureDef);
		fixture->SetSensor(true);
	}
	
	
	sf::ConvexShape sfShape;
	sf::ConvexShape collisionShape;

	b2Fixture* fixture;
private:
	b2PolygonShape mB2Shape;
	b2BodyDef mBodyDef;
	float mScale = 16;
	b2FixtureDef mFixtureDef;

};


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

