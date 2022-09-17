#define GLFW_INCLUDE_NONE

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "stdlib.h"

#include "tech_things.hpp"

const char *vertex_data = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\n\0";

const char *fragment_data = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

namespace tech68
{
    int init()
    {
        // Setting error callback...
        glfwSetErrorCallback(&glfw_error);

        // GLFW Initializing...
        glfwInit();
    }

    tech68_window make_app(int width, int height, std::string title)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow* app;
        const char* atitle = &title[0];
        app = glfwCreateWindow(width, height, atitle, NULL, NULL);
        glfwMakeContextCurrent(app);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);

        return app;
    }

    tech68_shaders get_shaders()
    {
        tech68_shaders shader;

        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertex_shader, 1, &vertex_data, NULL);
        glCompileShader(vertex_shader);

        glShaderSource(fragment_shader, 1, &fragment_data, NULL);
        glCompileShader(fragment_shader);

        unsigned int shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);

        glLinkProgram(shader_program);

        glUseProgram(shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        shader = shader_program;

        return shader;
    }

    tech68_shape triangle()
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        unsigned int vbo, vao;
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vao);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        tech68_shape vert;
        vert = vao;

        return vert;
    }

    tech68_shape rectangle()
    {
        float vertices[] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };  

        unsigned int vbo, vao, ebo;
        glGenBuffers(1, &ebo);
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(0);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        tech68_shape vert;
        vert = vao;

        return vert;
    }

    void draw_triangle(tech68_shape shape, tech68_shaders shader)
    {
        glUseProgram(shader);
        glBindVertexArray(shape);
        //if (shape.verticies_count > 3)
        //{
        //    glDrawElements(GL_TRIANGLES, shape.indieces_count, GL_UNSIGNED_INT, 0);
        //}
        glBindVertexArray(0);
    }

    void draw_rect(tech68_shape shape, tech68_shaders shader)
    {
        glUseProgram(shader);
        glBindVertexArray(shape);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    int is_open(tech68_window app)
    {
        return glfwWindowShouldClose(app);
    }

    void app_event(tech68_window app)
    {
        glfwSwapBuffers(app);
        glfwPollEvents();
    }

    int end_app(tech68_window app)
    {
        glfwDestroyWindow(app);
        glfwTerminate();
        return 0;
    }

    void screen_clear(float r, float g, float b, float a = 1.0f)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void resize_world(tech68_window app)
    {
        glfwSetFramebufferSizeCallback(app, _framebuffer_size_callback);
    }

    void close_on_key(tech68_window app)
    {
        if(glfwGetKey(app, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app, true);
    }
}