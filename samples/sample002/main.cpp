/*
 * Use shaders to draw a point
 */

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define NUM_VAO 1

GLuint renderingProgram;
GLuint vao[NUM_VAO];

void init();
void display();
GLuint createShaderProgram();

int main()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "sample 2", nullptr, nullptr);
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

    glfwSwapInterval(1);

    init();

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

GLuint createShaderProgram()
{
    const char *vShaderSource =
            "#version 410\n"
            "void main()\n"
            "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char *fShaderSource =
            "#version 410\n"
            "out vec4 color;\n"
            "void main()\n"
            "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vShaderSource, nullptr);
    glShaderSource(fShader, 1, &fShaderSource, nullptr);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    return program;
}

void init()
{
    renderingProgram = createShaderProgram();

    // not using those because we hardcoded a single point in the vertex shader, but openGL requires at least one
    // vertex array object be created whenever shaders are being used
    glGenVertexArrays(NUM_VAO, vao);
    glBindVertexArray(vao[0]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // load the shaders into the hardware
    glUseProgram(renderingProgram);

    // Control the size of the point
    glPointSize(30.0f);

    // initiates pipeline processing
    glDrawArrays(GL_POINTS, 0, 1);
}
