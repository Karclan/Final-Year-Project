#ifndef TIMER_H
#define TIMER_H

#include <SFML\System.hpp>

/*! \brief  Time Class

Time class, class used to get the current time between frames used in updates to scale values around delta time

*/


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