/*
 * Initialize a window, api loader, and clear the color buffer with clear color of red
 */

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>

void display();

int main()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    // 1 on mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // these 2 lines on mac, They force the Mac to use the latest version of OpenGL available on the hardware.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Sample 001", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (gl3wInit())
    {
        std::cerr << "failed to initialize OpenGL" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!gl3wIsSupported(4, 1))
    {
        std::cerr << "OpenGL 4.1 not supported" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void display()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
