#ifndef TIMER_H
#define TIMER_H

#include <SFML\System.hpp>

class Timer
{
public:
	
	static void init();
	static float getTime();
	static void update();
	
private:
	Timer();
	~Timer();
	static Timer* get();

	sf::Clock m_clock;
	sf::Time  m_time;
};
#endif