#include "carRender.h"
#include <string>

class Timer : public Drawable, public Transformable {
	int minutes = 0, numSeconds = 0;
	std::string secondsStr, minutesStr, timeStr;

	bool start_timer = false;
	int input_seconds = 0;
	int input_minutes = 0;
	//Time current_time = seconds(0);
	//Time starting_time = seconds(0);
	int milliseconds_left = 0;
	int seconds_left = 0;
	int minutes_left = 0;
	Time starting_time = milliseconds(0);
	Time elapsed_time = milliseconds(0);
	Time time_left = milliseconds(0);
	Clock timer;

	char timer_str[8];	// String for timer_text
	std::string minute_str;
	std::string second_str;
	std::string millisecond_str;
	std::string temp_str;
	Font font;
	Text timer_text;

	Texture m_texture;

	virtual void draw(RenderTarget& target, RenderStates states) const;


	// METHODS
public:
	// Constructor
	Timer();

	// getter functions to acces private variables
	Time getCurrentTime(void) {
		 return timer.getElapsedTime();
	}
	int getMinutes(void) {
		return minutes;
	}
	int getSeconds(void) {
		return numSeconds;
	}
	int getMinutesLeft(void) {
		return minutes_left;
	}
	int getSecondsLeft(void) {
		return seconds_left;
	}
	int getMillisecondsLeft(void) {
		return milliseconds_left;
	}

	void countUp(void);
	void setTimer(int input_minutes, int input_seconds);
	void startTimer();
	void countDown();
};