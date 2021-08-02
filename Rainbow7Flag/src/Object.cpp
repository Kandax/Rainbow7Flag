#include "Object.h"

static constexpr float M_PI = 3.14159265359f;
static constexpr float ToDegrees = 180 / M_PI;
static constexpr float ToRadians = M_PI / 180;


void Object::setPosition(float x, float y)
{
	

}

void Object::setRotation(float degrees)
{
}


b2Vec2 Object::getPosition() const
{
	return mPosition;
}

float Object::getRotation() const
{
	return mRotation;
}

float Object::getRotationInRadians() const
{
	return mRotation * ToRadians;
}

b2Body* Object::getBody()
{
	return mBody;
}

b2BodyDef& Object::getBodyDef()
{
	return mBodyDef;
}

b2FixtureDef& Object::getFixtureDef()
{
	return mFixtureDef;
}

