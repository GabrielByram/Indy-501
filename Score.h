#pragma once
#include "carRender.h"
//#include <iostream>
class Score : public Drawable, public Transformable {
	bool start = true, middle = true, right = false, left = true;
	Text timer_text; int numScore = 0; char strScore[10], numStrScore[3] = "0";
	Font font; Texture m_texture;
	virtual void draw(RenderTarget& target, RenderStates states) const;
public:
	Score();
	void checkPosition(Sprite& car, Sprite& line, Sprite& mid, Sprite& r, Sprite& l);
	void updateScore();
	int getNumScore(void);
};

