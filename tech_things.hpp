#include "GLFW/glfw3.h"
#include "iostream"

typedef GLFWwindow* tech68_window;

typedef struct tech68_shape
{
    int vao;
    int count;
} tech68_shape;

void _framebuffer_size_callback(GLFWwindow* app, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void glfw_error(int id, const char* description)
{
    std::cout << description << std::endl;
}