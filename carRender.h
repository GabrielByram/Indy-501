#ifndef CAR_RENDER_H
#define CAR_RENDER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Collision.h"
using namespace sf;
class CarRender : public Drawable, public Transformable{
private:
	SoundBuffer buffer;
	Sound jams;
	float deltAudio = 0.005f;
	// from Gabriel's car class
	float accSpeed, maxSpeed;
	float velocity, direction = 0, friction, turnSpeed;
	float xPos, yPos;

	Texture cartex;
	Sprite carSprite;

	// Oliver's graphics work
	//Texture m_texture;
	/*RectangleShape body = RectangleShape(Vector2f(14, 4));
	RectangleShape wheel1 = RectangleShape(Vector2f(6, 4));
	RectangleShape wheel2 = RectangleShape(Vector2f(6, 4));
	RectangleShape wheel3 = RectangleShape(Vector2f(6, 4));
	RectangleShape wheel4 = RectangleShape(Vector2f(6, 4));
	RectangleShape axle1 = RectangleShape(Vector2f(2, 8));
	RectangleShape axle2 = RectangleShape(Vector2f(2, 8));*/
	virtual void draw(RenderTarget& target, RenderStates states) const;
public:
	// default constructor
	CarRender();
	// parameterized constructor
	CarRender(float baseS, float maxS, float frick, float turnS, Texture& carSpr);
	void accelerate(void);
	void drive(void);
	void getCarSprite(Sprite& sprite) {
		sprite = carSprite;
	}
	float getVelocity(void) {
		return velocity;
	}
	float getxPos(void) {
		return xPos;
	}
	float getyPos(void) {
		return yPos;
	}
	void setxPos(float x) {
		xPos = x;
	}
	void setyPos(float y) {
		yPos = y;
	}
	float getDirection(void) {
		return direction;
	}
	void setDirection(float d) {
		direction = d;
	}
	void setVelocity(float vel) {
		velocity = vel;
	}
	void setFriction(float frick) {
		friction = frick;
	}
	void stopAudio() {
		jams.stop();
	}
};
#endif // !CAR_RENDER_H
