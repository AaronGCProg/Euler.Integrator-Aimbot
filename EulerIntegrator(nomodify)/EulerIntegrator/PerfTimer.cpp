// ----------------------------------------------------
// j1PerfTimer.cpp
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint64 j1PerfTimer::frequency = 0;

// ---------------------------------------------
j1PerfTimer::j1PerfTimer()
{
	// TODO 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
	// they are simple, one line each!
	Start();
}

// ---------------------------------------------
void j1PerfTimer::Start()
{
	//Gets the time the timer is started and the frequency
	started_at = SDL_GetPerformanceCounter();
	frequency = SDL_GetPerformanceFrequency();
}

// ---------------------------------------------
double j1PerfTimer::ReadMs() const
{
	return ((SDL_GetPerformanceCounter() - started_at) * 1000.0f) / (double)frequency;

}

// ---------------------------------------------
uint64 j1PerfTimer::ReadTicks() const
{
	return (SDL_GetPerformanceCounter() - started_at);
}