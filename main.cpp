#include <GL\glew.h>

#include "Window.h"
#include "Program.h"
#include "StorageTexture.h"
#include "ComputeProgram.h"
#include "Quad.h"

const GLint WIDTH = 1280;
const GLint HEIGHT = 768;

int main()
{
	// Create window
	Window mainWindow = Window(WIDTH, HEIGHT);
	mainWindow.initialise();

	// Quad to draw
	Quad quad = Quad();
	quad.initialise();	

	// Create programs
	Program drawProgram = Program();
	drawProgram.createFromFiles("vertex.glsl", "fragment.glsl");

	ComputeProgram computeProgram = ComputeProgram();
	computeProgram.createFromFile("compute.glsl");
	StorageTexture texOutput = StorageTexture();
	texOutput.initialise(WIDTH, HEIGHT);

	while (!mainWindow.getShouldClose()) {

		// Get + Handle user input events
		glfwPollEvents();

		// Clean window
		mainWindow.clear(0.25f, 0.5f, 0.75f, 1.0f);

		// Compute
		computeProgram.use();
		texOutput.useToCompute();
		glDispatchCompute(ceil(WIDTH/32.0f), ceil(HEIGHT/32.0f), 1);

		// Make sure writing to image has finished before read
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawProgram.use();
		texOutput.useToDraw();

		// Draw
		quad.draw();

		mainWindow.swapBuffers();
	}
}