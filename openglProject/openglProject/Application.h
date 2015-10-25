#pragma once
// Application.h is the framework
// which holds all the OpenGL
// application initialization.

// Header guards
#ifndef APPLICATION_H_
#define APPLICATION_H_

// Include headers
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>

// **Note:** Include GLUT after the standard c++ libraries to prevent linker errors
#ifdef WIN32
	#include <windows.h>
	#include <GL/glut.h>
#else
	#include <GL/glut.h>
#endif

// Utility classes
#include "Keyboard.h"
#include "PerformanceTimer.h"
#include "Vector.h"

namespace applicationFramework
{
	class Application
	{
		private:
			double frameTimeElapsed;

		protected:
			Keyboard keyStates;
			PerformanceTimer frameRateTimer;
			PerformanceTimer displayTimer;

			std::string title;
			double elapsedTimeInSeconds;
			static Application *instance;

			Vector<float> eyeVector;
			Vector<float> centerVector;
			Vector<float> upVector;

			float position;
			float direction;

		public:
			// Constants
			const static int FPS = 60;		// Frames per second
			const static int WINDOW_WIDTH = 640;
			const static int WINDOW_HEIGHT = 480;
			const static int WINDOW_X_POSITION = 100;
			const static int WINDOW_Y_POSITION = 100;

			const static double FRAME_TIME;		// Frame time is in milliseconds calculated
												// using FPS.

		public:
			// class constructor/destructor
			Application();
			virtual ~Application();

			// startApplication will initialize the application and start
			// the GLUT run loop. It must be called after the GLUTFramework
			// class is created to start the application.
			void startApplication(int argc, char *argv[]);

			// ****************************
			// ** Subclass and Implement ** 
			// ****************************

			/** Any loading logic can be down in this method when the application starts. */
			virtual void load();

			// The render function is called at a specified frames-per-second (FPS). 
			// Any animation drawing code can be run in the render function.
			// @param dTime - the change in time (seconds)
			virtual void render(float dTime);

			// Called when the window dimensions change.
			// @param width - the width of the window in pixels
			// @param height - the height of the window in pixels
			virtual void reshape(int width, int height);

			// called when the mouse buttons are pressed
			// @param button - the mouse button
			// @param state - the state of the buttons
			// @param x - the x coordinate
			// @param y - the y coordinate
			virtual void mouseButtonPress(int button, int state, int x, int y);

			// Called when the mouse moves on the screen 
			// @param x - the x coordinate
			// @param y - the y coordinate
			virtual void mouseMove(int x, int y);

			// The keyboard function is called when a standard key is
			// pressed down.
			// @param key - the key press
			// @param x - the x coordinate
			// @param y = the y coordinate
			virtual void keyboardDown(unsigned char key, int x, int y);

			// The keyboard function is called when a standard key is
			// pressed down.
			// @param key - the key press
			// @param x - the x coordinate
			// @param y = the y coordinate
			virtual void keyboardUp(unsigned char key, int x, int y);

			/** The keyboard function is called when a special key is pressed down.
			(F1 keys, Home, Insert, Delete, Page Up/Down, End, arrow keys)
			http://www.opengl.org/resources/libraries/glut/spec3/node54.html
			@param key - the key press
			@param x - the x coordinate of the mouse
			@param y - the y coordinate of the mouse
			*/
			virtual void specialKeyboardDown(int key, int x, int y);

			/** The keyboard function is called when a special key is "unpressed.
			(F1 keys, Home, Insert, Delete, Page Up/Down, End, arrow keys)
			@param key - the key press
			@param x - the x coordinate of the mouse
			@param y - the y coordinate of the mouse
			*/
			virtual void specialKeyboardUp(int key, int x, int y);

			/** Sets the initial matrices that are used to setup OpenGL. */
			void setDisplayMatricies();

			/** Sets up basic lighting */
			void setupLights();

			/** A helper function that allows the camera position and orientation to be changed.
			@param eyeX, eyeY, eyeZ - the vector describing the "eye" or camera position
			@param centerX, centerY, centerZ - the vector describing the "object" that the eye is looking at
			@param upX, upY, upZ - the vector describing orientation. Normally (0,1,0)
			*/
			void setLookAt(float eyeX, float eyeY, float eyeZ,
				float centerX, float centerY, float centerZ,
				float upX, float upY, float upZ);

			/** The position of the "eye" or camera in 3D space
			@return a 3D vector
			*/
			Vector<float> getEyeVector() const;

			/** The position that the "eye" or camera is looking at in 3D space
			@return a 3D vector
			*/
			Vector<float> getCenterVector() const;

			/** The up vector, used to determine orientation. Normally set to (0,1,0)
			@return a 3D vector
			*/
			Vector<float> getUpVector() const;

			/** Sets the title of the window to a specific string. Invoke before startFramework()
			@param title - the name of the window
			*/
			void setTitle(std::string theTitle);

			/** Initializes GLUT and registers the callback functions. */
			void init();

			/** The instance will be set when the framework is started, this step is necessary
			* to initialize the static instance that is used for the object oriented wrapper calls
			*/
			void setInstance();

			/** The run method is called by GLUT and contains the logic to set the framerate of the application. */
			void run();

			/** The renderApplication() function sets up initial GLUT state and calculates the
			change in time between each frame. It calls the display(float) function which can
			be sub classed.
			*/
			void renderApplication();

			// ** Static functions which are passed to GLUT function callbacks **
			// http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.1
			static void displayWrapper();
			static void reshapeWrapper(int width, int height);
			static void runWrapper();
			static void mouseButtonPressWrapper(int button, int state, int x, int y);
			static void mouseMoveWrapper(int x, int y);
			static void keyboardDownWrapper(unsigned char key, int x, int y);
			static void keyboardUpWrapper(unsigned char key, int x, int y);
			static void specialKeyboardDownWrapper(int key, int x, int y);
			static void specialKeyboardUpWrapper(int key, int x, int y);
	};
}

#endif