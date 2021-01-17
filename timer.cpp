#include "timer.h"

// enables timer to be drawn
void Timer::draw(RenderTarget& target, RenderStates states) const {
	states.transform *= getTransform();

	states.texture = &m_texture;
	target.draw(timer_text, states);
}

// constructor initializes the displayed time to the correct size and position
Timer::Timer() {
	strcpy_s(timer_str, "00:00.0");
	if (!font.loadFromFile("Arial.ttf"));
	timer_text.setFont(font);
	timer_text.setString(timer_str);
	timer_text.setCharacterSize(80);
	timer_text.setFillColor(Color::White);
	timer_text.setStyle(Text::Regular);
	timer_text.setPosition(850.f, 40.f);
}

// Sets initial amount of time on the timer
void Timer::setTimer(int input_minutes, int input_seconds) {
	starting_time = seconds((input_minutes * 60) + input_seconds);
}

// resets timer to the correct starting value
void Timer::startTimer() {
	timer.restart();
}

// increments the time every second, computes correct minutes and seconds,
// then sets the correct text to display
void Timer::countUp(void) {
	numSeconds = timer.getElapsedTime().asSeconds();
	if (numSeconds > 59) {
		minutes = numSeconds / 60;
		numSeconds -= 60 * minutes;
	}
	else {
		minutes = 0;
	}
	secondsStr = std::to_string(numSeconds);
	minutesStr = std::to_string(minutes);
	timeStr = minutesStr + ":";
	if (numSeconds < 10)
		timeStr += "0";
	timeStr += secondsStr;

	timer_text.setString(timeStr);
}

// decrements the time every second, computes correct minutes and seconds,
// then sets the correct text to display
void Timer::countDown() {
	time_left = starting_time - timer.getElapsedTime();
	milliseconds_left = time_left.asMilliseconds();

	if (milliseconds_left > 0) {
		// Get minutes
		minutes_left = milliseconds_left / 60 / 1000;
		minute_str = std::to_string(minutes_left);
		if (minutes_left < 10) {
			minute_str = "0" + minute_str;
		}

		// Get seconds
		seconds_left = (milliseconds_left / 1000) - (minutes_left * 60);
		second_str = std::to_string(seconds_left);
		if (seconds_left < 10) {
			second_str = "0" + second_str;
		}

		// Get milliseconds
		milliseconds_left = (milliseconds_left / 100) % 10;
		millisecond_str = std::to_string(milliseconds_left);

		// Combine all strings
		temp_str = minute_str + ":";
		temp_str += second_str + "." + millisecond_str;
	} else {
		temp_str = "00:00.0";
	}

	// Update timer_text
	timer_text.setString(temp_str);
}
