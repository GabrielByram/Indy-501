#include "carRender.h"
//using namespace sf; included in header

// draws car based on its position
void CarRender::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform(); // getTransform() is defined by Transformable

	// apply the texture
	states.texture = &cartex;
	/*target.draw(body, states);
	target.draw(wheel1, states);
	target.draw(wheel2, states);
	target.draw(wheel3, states);
	target.draw(wheel4, states);
	target.draw(axle1, states);
	target.draw(axle2, states);*/

	target.draw(carSprite, states);
}

// default constructor
CarRender::CarRender() {
	if (!buffer.loadFromFile("audio/EngingHigh.ogg"))
		return;
	jams.setBuffer(buffer);
	jams.setLoop(true);
	jams.setVolume(8);

	cartex.loadFromFile("textures/objects/car.png");
	carSprite.setTexture(cartex);

	friction = 0.008f;
	accSpeed = 0.02f;
	maxSpeed = 5.f;
	turnSpeed = 0.015f;
	velocity = 0.f, xPos = 860.f, yPos = 280.f;

	carSprite.setPosition(-16, -16); // centers 32 pixle image
	/*body.setPosition(2-8, 6-8);
	wheel1.setPosition(0-8, 0-8);
	wheel2.setPosition(8-8, 0-8);
	wheel3.setPosition(0-8, 12-8);
	wheel4.setPosition(8-8, 12-8);
	axle1.setPosition(2-8, 4-8);
	axle2.setPosition(10-8, 4-8);*/
}

// parameterized constructor
CarRender::CarRender(float baseS, float maxS, float frick, float turnS, Texture& carSpr) {
	if (!buffer.loadFromFile("audio/EngingHigh.ogg"))
		return;
	jams.setBuffer(buffer);
	jams.setLoop(true);
	jams.setVolume(1);

	carSprite.setTexture(carSpr);
	carSprite.setPosition(-16, -16); // centers 32 pixle image

	accSpeed = baseS;
	maxSpeed = maxS;
	friction = frick;
	turnSpeed = turnS;
	//carSprite = carSpr;

	velocity = 0, xPos = 860, yPos = 280;

	/*body.setPosition(2 - 8, 6 - 8);
	wheel1.setPosition(0 - 8, 0 - 8);
	wheel2.setPosition(8 - 8, 0 - 8);
	wheel3.setPosition(0 - 8, 12 - 8);
	wheel4.setPosition(8 - 8, 12 - 8);
	axle1.setPosition(2 - 8, 4 - 8);
	axle2.setPosition(10 - 8, 4 - 8);*/
}

// changes car speed and adjusts car sound based on user input
void CarRender::accelerate(void)
{
	// move forward if not at max speed yet
	if (Keyboard::isKeyPressed(Keyboard::W) && velocity < maxSpeed) {
		if (jams.getStatus() == jams.Stopped)
			jams.play();
		velocity += accSpeed;
		if (jams.getPitch() < 1.5)
			jams.setPitch(jams.getPitch() + deltAudio);
	// reverse
	} else if (Keyboard::isKeyPressed(Keyboard::S) && velocity > -maxSpeed) {
		velocity -= accSpeed;
		if (jams.getPitch() < 1.5)
			jams.setPitch(jams.getPitch() + deltAudio);
	} else if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && jams.getPitch() > 0.5)
		jams.setPitch(jams.getPitch() - deltAudio);
	// turn left
	if (Keyboard::isKeyPressed(Keyboard::A) && velocity != 0) {
		direction -= turnSpeed;
	}
	// turn right
	if (Keyboard::isKeyPressed(Keyboard::D) && velocity != 0) {
		direction += turnSpeed;
	}
	
	// friction
	if (velocity - friction > 0) { 
		velocity -= friction;
	}
	else if (velocity + friction < 0) {
		velocity += friction;
	}
	else {
		velocity = 0;
	}
}

// changes car position based on speed and draws new car position on screen
void CarRender::drive(void)
{
	
	// move car
	xPos += cos(direction) * velocity;
	yPos += sin(direction) * velocity;
	this->setPosition(xPos, yPos);

	// rotate
	this->setRotation(direction * 180.f / 3.14159f);
}


