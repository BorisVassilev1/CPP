#define GLFW_INCLUDE_GLU
#ifdef _WIN32
	#define GLFW_DLL	 // -> windows
#elif __linux__
//
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

#define GL_CONTEXT_VERSION_MAJOR 3
#define GL_CONTEXT_VERSION_MINOR 0

GLFWwindow  *window	 = NULL;
GLFWmonitor *monitor = NULL;

int window_width  = 800;
int window_height = 600;

static void window_hints() {
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_CONTEXT_VERSION_MINOR);
}

static void set_perspective(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = window_width / (float)window_height;
	glOrtho(-aspect, aspect, -1, 1, 0.0, 1000);
	glMatrixMode(GL_MODELVIEW);
}

static void set_window_callbacks() {
	glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
		std::cerr << "closing window!";
	});
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		window_width  = width;
		window_height = height;
		set_perspective(width, height);
	});
}

void GLAPIENTRY debug_message_callback_gl(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	std::cerr << "----------<GL DEBUG MESSAGE>----------\n\tSource: ";
	switch (source) {
		case GL_DEBUG_SOURCE_API: std::cerr << "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cerr << "Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			std::cerr << "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			std::cerr << "Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			std::cerr << "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			std::cerr << "Other";
			break;
	}
	std::cerr << "\n\tType: ";

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			std::cerr << "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			std::cerr << "Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			std::cerr << "Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			std::cerr << "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			std::cerr << "Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			std::cerr << "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			std::cerr << "Push Group";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			std::cerr << "Pop Group";
			break;
		case GL_DEBUG_TYPE_OTHER:
			std::cerr << "Other";
			break;
	}
	std::cerr << "\n\tSeverity: ";

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			std::cerr << "high";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cerr << "medium";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			std::cerr << "low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			std::cerr << "notification";
			break;
	}
	std::cerr << "\n\tMessage: " << message << std::endl;
}

void error_callback_glfw(int code, const char *err_msg) {
	std::cerr << "GLFW Error " << code << " : \n\t" << err_msg << std::endl;
}

void init_debug() {
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debug_message_callback_gl, 0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	} else {
		std::cerr << "GL debug context failed to initialize" << std::endl;
	}
}

int main(int argc, char *argv[]) {
	glfwSetErrorCallback(error_callback_glfw);

	if (!glfwInit()) {
		std::cerr << "glfwInit failed.";
		exit(1);
	}

	monitor = glfwGetPrimaryMonitor();
	window_hints();

	window = glfwCreateWindow(window_width, window_height, "test window", NULL, NULL);
	if (!window) {
		std::cerr << "glfwCreateWindow failed." << std::endl;
		glfwTerminate();
		exit(1);
	}

	set_window_callbacks();

	// GLFW settings
	glfwMakeContextCurrent(window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cerr << "glewInit failed." << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(1);
	}

	init_debug();

	glfwSwapInterval(1);

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	set_perspective(window_width, window_height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float r = 0;

	while (!glfwWindowShouldClose(window)) {
		// process pending events
		glfwPollEvents();

		glClearColor(0, 0, 0, 0);	  // black
		glClear(GL_COLOR_BUFFER_BIT);

		glColor4f(1, 1, 1, 1.0);

		glPushMatrix();
		{
			glRotatef(r, 0, 0, 1);
			glBegin(GL_TRIANGLES);
			{
				glColor3f(1, 0, 0);
				glVertex2f(0.5, -0.5);

				glColor3f(0, 1, 0);
				glVertex2f(0, 0.5);

				glColor3f(0, 0, 1);
				glVertex2f(-0.5, -0.5);
			}
			glEnd();
		}
		glPopMatrix();

		r += 1;

		glfwSwapBuffers(window);
	}

	// clean up and exit
	glfwTerminate();
	std::cerr << std::endl;
	return 0;
}
