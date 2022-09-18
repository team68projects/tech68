#define GLFW_INCLUDE_NONE

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "stdlib.h"

#include "tech_things.hpp"
#include "shader.hpp"

class tech68
{
    public:
        tech68()
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


        void draw(tech68_shape shape, tech68_shaders shader)
        {
            shader.init_program();
            glBindVertexArray(shape.vao);

            if (shape.count != 0)
            {
                glDrawElements(GL_TRIANGLES, shape.count, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }
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

        void screen_clear(tech68_shaders shader, float r, float g, float b, float a = 1.0f)
        {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
            shader.init_program();
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


        tech68_shaders get_shaders()
        {
            tech68_shaders shader("res/vertex.glsl", "res/fragment.glsl");

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

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            tech68_shape shape;
            shape.vao = vao;
            shape.count = 0;

            return shape;
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

            tech68_shape shape;
            shape.vao = vao;
            shape.count = (sizeof(indices)/ sizeof(*indices));

            return shape;
        }
};