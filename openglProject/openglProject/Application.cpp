// Application.cpp is the file
// that holds the class to setup
// and initialise the application.

// Include headers
#include "Application.h"

namespace applicationFramework
{
	// Set constants
	const double Application::FRAME_TIME = 1.0 /
		Application::FPS * 1000.0; // Milliseconds

	Application *Application::instance = NULL;

	// Class constructor
	Application::Application() 
	{
		elapsedTimeInSeconds = 0;
		frameTimeElapsed = 0;
		title = "OpenGL Demo";
		eyeVector = Vector<float>(0.0, 0.0, -10.0); // move the eye position back
		position = 0.0f;
		direction = 1.0 / FRAME_TIME;
	}

	// Class Destructor
	Application::~Application() 
	{
	}

	void Application::startApplication(int argc, char *argv[])
	{
		setInstance();	// Sets the instance to self, used in the callback wrapper functions

		// Initialize GLUT
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutCreateWindow(title.c_str());

		// Function callbacks with wrapper functions
		glutReshapeFunc(reshapeWrapper);
		glutMouseFunc(mouseButtonPressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		glutDisplayFunc(displayWrapper);
		glutKeyboardFunc(keyboardDownWrapper);
		glutKeyboardUpFunc(keyboardUpWrapper);
		glutSpecialFunc(specialKeyboardDownWrapper);
		glutSpecialUpFunc(specialKeyboardUpWrapper);

		init();						// Initialize
		glutIdleFunc(runWrapper); 	// The program run loop
		glutMainLoop();				// Start the main GLUT thread
	}

	void Application::load() 
	{
		// Subclass and override this method
	}

	void Application::render(float dTime) 
	{
		// Subclass and override this method
		static int frame = 0;
		std::cout << "GlutFramework Display: Frame: " << frame << ", dt(sec): " << dTime << ", Position: " << position << std::endl;
		++frame;

		// DEMO: Create a teapot and move it back and forth on the x-axis
		glTranslatef(position, 0.0f, 0.0f);
		glutSolidTeapot(2.5);
		if (position > 4 && direction > 0) {
			direction = -1.0 / FRAME_TIME;
		}
		else if (position < -4 && direction < 0) {
			direction = 1.0 / FRAME_TIME;
		}
		position += direction;
	}

	void Application::reshape(int width, int height) 
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}

	void Application::mouseButtonPress(int button, int state, int x, int y) 
	{
		printf("MouseButtonPress: x: %d y: %d\n", x, y);
	}

	void Application::mouseMove(int x, int y) 
	{
		printf("MouseMove: x: %d y: %d\n", x, y);
	}

	void Application::keyboardDown(unsigned char key, int x, int y)
	{
		// Subclass and override this method
		printf("KeyboardDown: %c = %d\n", key, (int)key);
		if (key == 27) { //27 =- ESC key
			exit(0);
		}

		keyStates.keyDown((int)key);
	}

	void Application::keyboardUp(unsigned char key, int x, int y)
	{
		// Subclass and override this method
		printf("KeyboardUp: %c \n", key);
		keyStates.keyUp((int)key);
	}

	void Application::specialKeyboardDown(int key, int x, int y)
	{
		// Subclass and override this method
		printf("SpecialKeyboardDown: %d\n", key);
	}

	void Application::specialKeyboardUp(int key, int x, int y)
	{
		// Subclass and override this method	
		printf("SpecialKeyboardUp: %d \n", key);
	}

	// ******************************
	// ** Graphics helper routines **
	// ******************************

	// Initialize the projection/view matricies.
	void Application::setDisplayMatricies() 
	{
		/* Setup the projection and model view matricies */
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float aspectRatio = width / height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, aspectRatio, 1, 500.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
			centerVector.x, centerVector.y, centerVector.z,
			upVector.x, upVector.y, upVector.z);
	}

	void Application::setupLights() 
	{
		GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
		GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
		GLfloat ambient_light[] = { 0.8, 0.8, 0.8, 1.0 };

		glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	}

	void Application::setLookAt(float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ, float upX, float upY, float upZ) 
	{
		eyeVector = Vector<float>(eyeX, eyeY, eyeZ);
		centerVector = Vector<float>(centerX, centerY, centerZ);
		upVector = Vector<float>(upX, upY, upZ);
	}

	Vector<float> Application::getEyeVector() const 
	{
		return eyeVector;
	}

	Vector<float> Application::getCenterVector() const 
	{
		return centerVector;
	}

	Vector<float> Application::getUpVector() const 
	{
		return upVector;
	}

	void Application::setTitle(std::string theTitle) 
	{
		title = theTitle;
	}

	// **************************
	// ** GLUT Setup functions **
	// **************************
	void Application::init() 
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		load();
	}

	void Application::setInstance() 
	{
		std::cout << "GlutFramework::setInstance()" << std::endl;
		instance = this;
	}

	void Application::run() 
	{
		if (frameRateTimer.isStopped()) {	// The initial frame has the timer stopped, start it once
			frameRateTimer.start();
		}

		frameRateTimer.stop();			// stop the timer and calculate time since last frame
		double milliseconds = frameRateTimer.getElapsedMilliseconds();
		frameTimeElapsed += milliseconds;

		if (frameTimeElapsed >= FRAME_TIME) {	// If the time exceeds a certain "frame rate" then show the next frame
			glutPostRedisplay();
			frameTimeElapsed -= FRAME_TIME;		// remove a "frame" and start counting up again
		}
		frameRateTimer.start();			// start the timer
	}

	void Application::renderApplication() 
	{
		if (displayTimer.isStopped()) {			// Start the timer on the initial frame
			displayTimer.start();
		}

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear once

		displayTimer.stop();		// Stop the timer and get the elapsed time in seconds
		elapsedTimeInSeconds = displayTimer.getElapsedSeconds(); // seconds

		setupLights();
		setDisplayMatricies();

		render(elapsedTimeInSeconds);

		glutSwapBuffers();
		displayTimer.start();		// reset the timer to calculate the time for the next frame
	}

	// ******************************************************************
	// ** Static functions which are passed to Glut function callbacks **
	// ******************************************************************

	void Application::displayWrapper() 
	{
		instance->renderApplication();
	}

	void Application::reshapeWrapper(int width, int height) 
	{
		instance->reshape(width, height);
	}

	void Application::runWrapper() 
	{
		instance->run();
	}

	void Application::mouseButtonPressWrapper(int button, int state, int x, int y) 
	{
		instance->mouseButtonPress(button, state, x, y);
	}

	void Application::mouseMoveWrapper(int x, int y) 
	{
		instance->mouseMove(x, y);
	}

	void Application::keyboardDownWrapper(unsigned char key, int x, int y) 
	{
		instance->keyboardDown(key, x, y);
	}

	void Application::keyboardUpWrapper(unsigned char key, int x, int y) 
	{
		instance->keyboardUp(key, x, y);
	}

	void Application::specialKeyboardDownWrapper(int key, int x, int y) 
	{
		instance->specialKeyboardDown(key, x, y);
	}

	void Application::specialKeyboardUpWrapper(int key, int x, int y) 
	{
		instance->specialKeyboardUp(key, x, y);
	}
}
