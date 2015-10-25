// Keyboard.cpp is the file that
// holds the implementation for
// the keyboard functionality.

// Include headers
#include "Keyboard.h"

namespace applicationFramework {

	// Class constructor
	Keyboard::Keyboard() 
	{
		for (int i = 0; i < NUMBER_KEYS; i++) {
			keys[i] = UP;
		}
	}

	// Keyboard down function
	void Keyboard::keyDown(int key) 
	{
		keys[key] = DOWN;
	}

	// Keyboard up functionality
	void Keyboard::keyUp(int key) 
	{
		keys[key] = UP;
	}

	// Keyboard down fucntionality
	bool Keyboard::isKeyDown(int key) 
	{
		if (keys[key] == DOWN) {
			return true;
		}
		else {
			return false;
		}
	}
}	// namespace
