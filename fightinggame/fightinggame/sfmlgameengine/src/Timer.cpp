#include "Timer.h"

Timer::Timer(){}
Timer::~Timer(){}

float Timer::getTime()
{
	Timer* ins = Timer::get();
	return ins->m_time.asSeconds();
}
void Timer::update()
{
	Timer* ins = Timer::get();
	ins->m_time = ins->m_clock.restart();
}
Timer* Timer::get()
{
	static Timer timer;
	return &timer;
}