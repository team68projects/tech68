#include "GLFW/glfw3.h"
#include "iostream"

#define tech68_shaders unsigned int

#define tech68_shape int

//typedef struct tech68_error
//{
//    int error_code;
//    std::string error_message;
//    std::string text_error_code;
//} tech68_erro

#define tech68_window GLFWwindow*

void _framebuffer_size_callback(GLFWwindow* app, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void glfw_error(int id, const char* description)
{
    std::cout << description << std::endl;
}