#pragma once
// PerformanceTimer.h is the file that
// handles performance timing for the
// application.

// Header guards
#ifndef PERFORMANCE_TIMER_H
#define PERFORMANCE_TIMER_H

#ifdef WIN32			
#include <windows.h>	// Windows 
#else						
#include <time.h>	// Mac/Unix
#include <Winsock2.h>
#endif

namespace applicationFramework {

	class PerformanceTimer
	{
	public:
		// Class constructor/destructor
		PerformanceTimer();
		~PerformanceTimer();

		/** Starts the timer */
		void start();

		/** Stops the timer */
		void stop();

		/** Checks to see if the timer is stopped */
		bool isStopped() const;

		/** Returns the elapsed time since the timer was started, or the time interval
		between calls to start() and stop().
		*/
		double getElapsedMicroseconds();
		double getElapsedMilliseconds();
		double getElapsedSeconds();

	private:
		bool _isStopped;

#ifdef WIN32
		LARGE_INTEGER _start;
		LARGE_INTEGER _end;
		LARGE_INTEGER _freq;
#else
		timeval _start;
		timeval _end;
#endif

	};
}	// namespace

#endif

