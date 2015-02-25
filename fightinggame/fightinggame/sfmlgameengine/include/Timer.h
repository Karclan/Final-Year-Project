#ifndef TIMER_H
#define TIMER_H

#include <SFML\System.hpp>

class Timer
{
public:
	static void  init();
	static sf::Time getTime();
	
	static void  update();

	
private:
	 Timer();
	~Timer();
	static Timer* get();

	sf::Time  m_time;
	sf::Clock m_clock;
};
#endif