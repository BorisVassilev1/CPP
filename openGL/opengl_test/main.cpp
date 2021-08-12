#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

GLFWwindow* window = NULL;
GLFWmonitor* monitor = NULL;

int main(int argc, char *argv[])
{

    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    window = glfwCreateWindow(800, 600, "test window",NULL, NULL);
    if(!window)
        throw std::runtime_error("glfwOpenWindow failed.");

    // GLFW settings
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        // process pending events
        glfwPollEvents();
        glClearColor(0, 0, 0, 1); // black
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
