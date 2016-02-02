#include "ShaderProgram.hpp"
#include "../Tools.hpp"

namespace SDL2TK
{
    GLuint LoadShader(const char* source, GLenum shaderType)
    {
        GLuint result = glCreateShader(shaderType);

        glShaderSource(result, 1, &source, nullptr);
        glCompileShader(result);

        return result;
    }

    ShaderProgram ShaderProgram::FromFiles(
        const char* vertexShaderFile,
        const char* fragmentShaderFile)
    {
        auto vertexShaderSource = FileToString(vertexShaderFile);
        auto fragmentShaderSource = FileToString(fragmentShaderFile);

        return ShaderProgram(
            vertexShaderSource.c_str(),
            fragmentShaderSource.c_str());
    }

    ShaderProgram::ShaderProgram()
        : _program(0)
    {
    }

    ShaderProgram::ShaderProgram(
        const char* vertexShaderSource,
        const char* fragmentShaderSource)
    {
        _program = glCreateProgram();

        GLuint vertexShader =
            LoadShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader =
            LoadShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        glAttachShader(_program, vertexShader);
        glAttachShader(_program, fragmentShader);
        glLinkProgram(_program);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other)
        : _program(other._program)
    {
        other._program = 0;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(_program);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other)
    {
        if (this != &other)
        {
            glDeleteProgram(_program);
            _program = other._program;
            other._program = 0;
        }

        return *this;
    }
}
