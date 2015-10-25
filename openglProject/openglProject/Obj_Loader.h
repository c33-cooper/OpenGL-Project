#pragma once
// Obj_Loader.h is the file that 
// allows the user to load an obj
// model into their scene.

// Header guards
#ifndef OBJ_LOADER_H_
#define OBJ_LOADER_H_

// Include headers
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/GL.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define KEY_ESCAPE 27

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
// namespace declaration
using namespace std;

class Obj_Loader
{
	public:
		// Class Constructor/destructor
		Obj_Loader();
		~Obj_Loader();

		// Model Loader functions
		float* calculateNormal(float* coord1, float* coord2, float* coord3);
		int load(char *filename);	// Loads the model
		void render();					// Draws the model on the screen
		void release();				// Release the model

		float* normals;							// Stores the normals
		float* Faces_Triangles;					// Stores the triangles
		float* vertexBuffer;					// Stores the points which make the object
		long TotalConnectedPoints;				// Stores the total number of connected vertices
		long TotalConnectedTriangles;			// Stores the total number of connected triangles

};

#endif // !OBJ_LOADER_H_
