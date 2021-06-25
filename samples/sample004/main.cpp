/*
 * Shader debugging
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

void printShaderLog(GLuint);
void printProgramLog(GLuint);
bool checkOpenGLError();

int main()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Sample 004", nullptr, nullptr);
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
    GLint vCompiled;
    GLint fCompiled;
    GLint linked;

    // introduce some errors to the source code
    const char *vShaderSource =
            "#version 410\n"
            "void main() idk what im typing\n"
            "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char *fShaderSource =
            "#version 410\n"
            "out vec4 color;\n"
            "void main()\n"
            "{ if (gl_FragCoord.error < 200) color = vec4(1.0, 0.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0); }";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vShaderSource, nullptr);
    glShaderSource(fShader, 1, &fShaderSource, nullptr);

    // catch errors while compiling shaders
    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vCompiled);
    if (vCompiled != 1)
    {
        std::cout << "vertex compilation failed" << std::endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fCompiled);
    if (fCompiled != 1)
    {
        std::cout << "fragment compilation failed" << std::endl;
        printShaderLog(fShader);
    }

    GLuint program = glCreateProgram();

    // catch errors while linking shaders
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    checkOpenGLError();
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != 1)
    {
        std::cout << "linking failed" << std::endl;
        printProgramLog(program);
    }

    return program;
}

void init()
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(NUM_VAO, vao);
    glBindVertexArray(vao[0]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);
    glPointSize(300.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

void printShaderLog(GLuint shader)
{
    int len = 0, chWritten = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        char log[len];
        glGetShaderInfoLog(shader, len, &chWritten, log);
        std::cout << "Shader Info Log: " << log << std::endl;
    }
}

void printProgramLog(GLuint program)
{
    int len = 0, chWritten = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        char log[len];
        glGetProgramInfoLog(program, len, &chWritten, log);
        std::cout << "Program Info Log: " << log << std::endl;
    }
}

bool checkOpenGLError()
{
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}
