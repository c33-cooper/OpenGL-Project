// PerformanceTimer.cpp is the file that
// holds the implementation for the
// application timer.

// Include headers
#include "PerformanceTimer.h"

namespace applicationFramework {

// Class constructor
PerformanceTimer::PerformanceTimer() 
{

#ifdef WIN32	
		QueryPerformanceFrequency(&_freq);	// Retrieves the frequency of the high-resolution performance counter
		_start.QuadPart = 0;
		_end.QuadPart = 0;
#else
		_start.tv_sec = 0;
		_start.tv_usec = 0;
		_end.tv_sec = 0;
		_end.tv_usec = 0;

#endif

		_isStopped = true;
	}

// Class destructor
PerformanceTimer::~PerformanceTimer() 
{
}

// Start the timer
void PerformanceTimer::start() 
{
#ifdef WIN32
		QueryPerformanceCounter(&_start);	// Retrieves the current value of the high-resolution performance counter
#else
		gettimeofday(&_start, NULL);		// Get the starting time
#endif
		_isStopped = false;
	}

// Stop the timer
void PerformanceTimer::stop() 
{
#ifdef WIN32
		QueryPerformanceCounter(&_end);
#else
		gettimeofday(&_end, NULL);
#endif

		_isStopped = true;
	}

// Check is timer is stopped
bool PerformanceTimer::isStopped() const 
{
		return _isStopped;
}

// return elapsed microseconds
double PerformanceTimer::getElapsedMicroseconds()
{
		double microSecond = 0;

		if (!_isStopped) {
#ifdef WIN32
			QueryPerformanceCounter(&_end);
#else
			gettimeofday(&_end, NULL);
#endif
		}

#ifdef WIN32
		if (_start.QuadPart != 0 && _end.QuadPart != 0) {
			microSecond = (_end.QuadPart - _start.QuadPart) * (1000000.0 / _freq.QuadPart);
		}
#else 
		microSecond = (_end.tv_sec * 1000000.0 + _end.tv_usec) - (_start.tv_sec * 1000000.0 + _start.tv_usec);
#endif

		return microSecond;
	}

// Return elapsed milliseconds
double PerformanceTimer::getElapsedMilliseconds()
{
		return getElapsedMicroseconds() / 1000.0;
}

// Return elapsed seconds
double PerformanceTimer::getElapsedSeconds() 
{
		return getElapsedMicroseconds() / 1000000.0;
}

}
