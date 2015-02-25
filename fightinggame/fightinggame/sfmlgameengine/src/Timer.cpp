#include "Timer.h"

Timer::Timer(){}
Timer::~Timer(){}

sf::Time Timer::getTime()
{
	Timer* ins = Timer::get();
	return ins->m_time;
}
void Timer::update()
{
	Timer* ins  = Timer::get();
	ins->m_time	= ins->m_clock.restart();
}

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯//
//===PRIVATE FUNCTIONS===//
//_______________________//
Timer* Timer::get()
{
	static Timer timer;
	return &timer;
}