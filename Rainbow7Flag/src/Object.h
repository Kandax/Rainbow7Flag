#pragma once
#include<box2d/box2d.h>


class Object
{
public:
	

	void setPosition(float x, float y);
	void setRotation(float degrees);

	b2Vec2 getPosition() const;
	float getRotation() const;
	float getRotationInRadians() const;
	b2Body* getBody();
	b2BodyDef& getBodyDef();
	b2FixtureDef& getFixtureDef();


protected:
	b2Vec2 mPosition;
	float mRotation;
	b2World* mWorld;
	b2BodyDef mBodyDef;
	b2Body* mBody;
	b2FixtureDef mFixtureDef;
	
};

