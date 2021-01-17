#include "Score.h"

// enables score to be drawn
void Score::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform(); // getTransform() is defined by Transformable

	// apply the texture
	states.texture = &m_texture;
	target.draw(timer_text, states);
}

// constructor initializes displayed score to the correct size and position
Score::Score() {
	strcpy_s(strScore, "Score: 0");
	if (!font.loadFromFile("Arial.ttf"));
	timer_text.setFont(font);
	timer_text.setString(strScore);
	timer_text.setCharacterSize(100);
	timer_text.setFillColor(Color::White);
	timer_text.setStyle(Text::Regular);
	timer_text.setPosition(800.f, 480.f);
}

// determine which triggers in a map the car has passed through
void Score::checkPosition(Sprite& car, Sprite& line, Sprite& mid, Sprite& r, Sprite& l) {
	if (!start) {
		if (Collision::BoundingBoxTest(car, line)) {
			start = true;
			right = false;
			updateScore();
		}
	}
	if (!right) {
		if (Collision::BoundingBoxTest(car, r)) {
			right = true;
			middle = false;
		}
	}
	if (!middle) {
		if (Collision::BoundingBoxTest(car, mid)) {
			middle = true;
			left = false;
		}
	}
	if (!left) {
		if (Collision::BoundingBoxTest(car, l)) {
			left = true;
			start = false;
		}
	}
}

// increments the score and sets the displayed text to the correct score
void Score::updateScore() {
	_itoa_s(++numScore, numStrScore, 10);
	int i = -1;
	do {
		i++;
		*(strScore + 7 + i) = *(numStrScore + i);
	} while (*(numStrScore + i) != '\0');
	timer_text.setString(strScore);
}

// getter function for numScore
int Score::getNumScore(void) {
	return numScore;
}
