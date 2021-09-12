//#define GLFW_DLL // -> windows
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

GLFWwindow* window = NULL;
GLFWmonitor* monitor = NULL;

int window_width = 800;
int window_height = 600;

static void window_hints() {
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
}


static void set_window_callbacks() {
	glfwSetWindowCloseCallback(window, [] (GLFWwindow *window) {
		std::cout << "closing window!";
	});
	glfwSetKeyCallback(window, [] (GLFWwindow *window, int key,int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});
	glfwSetWindowSizeCallback(window, [] (GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		window_width = width;
		window_height = height;
		glLoadIdentity();
		GLdouble aspect = (GLdouble)window_width / window_height;
		glOrtho(-1, 1, -1 / aspect, 1 / aspect, 0.01, 10000);
		glTranslatef(0, 0, -10);
	});
}

int main(int argc, char *argv[])
{

	if(!glfwInit())
		throw std::runtime_error("glfwInit failed");

	monitor = glfwGetPrimaryMonitor();
	window_hints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(window_width, window_height, "test window", NULL, NULL);

	if(!window)
		throw std::runtime_error("glfwOpenWindow failed.");


	set_window_callbacks();


	// GLFW settings
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	std::cout << glGetString(GL_VERSION) << std::endl;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	GLdouble aspect = window_width / window_height;
	glOrtho(-1, 1, -1 / aspect, 1 / aspect, 0.01, 10000);
	glTranslatef(0, 0, -10);	

	while(!glfwWindowShouldClose(window))
	{
		//glRotatef(1, 0, 0, 0.1);
		// process pending events
		glfwPollEvents();
		glClearColor(0, 0, 0, 0); // black
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);

		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.5, -0.5);

		glColor3f(0.0, 1.0, 0.0);
		glVertex2f( 0.5, -0.5);

		glColor3f(0.0, 0.0, 1.0);
		glVertex2f( 0.0,  0.5);

		glEnd();

		glfwSwapBuffers(window);
	}

	// clean up and exit
	glfwTerminate();
	return 0;
}
