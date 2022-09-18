#include "glad/glad.h"

#include "iostream"
#include "fstream"
#include "sstream"

class tech68_shaders
{
    public:
        unsigned int ID;

        tech68_shaders(std::string vertex_shader_file, std::string fragment_shader_file);

        void init_program();
        void set_bool(const std::string &name, bool value) const;
        void set_int(const std::string &name, int value) const;
        void set_float(const std::string &name, float value) const;
};

tech68_shaders::tech68_shaders(std::string vertex_shader_file, std::string fragment_shader_file)
{
    std::string vertex_shader_file_content;
    std::string fragment_shader_file_content;

    std::ifstream vertex_shader;
    vertex_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::ifstream fragment_shader;
    fragment_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        std::stringstream vertex_shader_stream, fragment_shader_stream;

        vertex_shader.open(vertex_shader_file);
        vertex_shader_stream << vertex_shader.rdbuf();
        vertex_shader.close();

        fragment_shader.open(fragment_shader_file);
        fragment_shader_stream << fragment_shader.rdbuf();
        fragment_shader.close();

        vertex_shader_file_content = vertex_shader_stream.str();
        fragment_shader_file_content = fragment_shader_stream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Cant read shader file, or it does'nt exist!" << std::endl;
    }

    const char* vertex_code = vertex_shader_file_content.c_str();
    const char* fragment_code = fragment_shader_file_content.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &vertex_code, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(fragment);

    tech68_shaders::ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void tech68_shaders::init_program()
{
    glUseProgram(tech68_shaders::ID);
}

void tech68_shaders::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void tech68_shaders::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void tech68_shaders::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
