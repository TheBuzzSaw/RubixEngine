#include "Shader.hpp"
#include <memory>

namespace SDL2TK
{
    Shader::Shader()
        : _shader(0)
    {
    }

    Shader::Shader(Shader&& other)
        : _shader(other._shader)
    {
        other._shader = 0;
    }

    Shader::~Shader()
    {
        // http://www.opengl.org/sdk/docs/man/xhtml/glDeleteShader.xml
        glDeleteShader(_shader); // Safe to call on 0.
    }

    Shader& Shader::operator=(Shader&& other)
    {
        if (this != &other)
        {
            glDeleteShader(_shader);
            _shader = other._shader;
            other._shader = 0;
        }

        return *this;
    }

    std::string Shader::Compile(Type type, const char* source)
    {
        glDeleteShader(_shader);
        std::string errors;

        // http://www.opengl.org/sdk/docs/man/xhtml/glCreateShader.xml
        _shader = glCreateShader(static_cast<GLenum>(type));

        if (_shader)
        {
            glShaderSource(_shader, 1, &source, nullptr);
            glCompileShader(_shader);

            GLint compiled;
            glGetShaderiv(_shader, GL_COMPILE_STATUS, &compiled);

            if (!compiled)
            {
                GLint length;
                glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

                if (length > 0)
                {
                    errors.resize(length);
                    glGetShaderInfoLog(_shader, length, nullptr, &errors[0]);
                }
                else
                {
                    errors = "failed to compile (OpenGL provided no logs)";
                }

                glDeleteShader(_shader);
                _shader = 0;
            }
        }
        else
        {
            errors = "failed on glCreateShader";
        }

        return errors;
    }
}
