#ifndef MAPS_H
#define MAPS_H
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "timer.h"
#include <iostream>

class Maps {
private:
	CarRender car;
	Sprite hitBox;
	Sprite startingLine, midLine, leftLine, rightLine;
	Texture line;
public:
	Maps(CarRender carR, Sprite hitB) {
		line.loadFromFile("textures/misc/Line.png");
		car = carR;
		hitBox = hitB;
		startingLine.setTexture(line);
		midLine.setTexture(line);
		rightLine.setTexture(line);
		leftLine.setTexture(line);
	}
	bool map1(Timer& timer, int modeChoice, Score& check);
	bool map2(Timer& timer, int modeChoice, Score& check);
};

#endif