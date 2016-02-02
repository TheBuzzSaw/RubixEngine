#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>

namespace SDL2TK
{
    class ShaderProgram
    {
        public:
            static ShaderProgram FromFiles(
                const char* vertexShaderFile,
                const char* fragmentShaderFile);

            ShaderProgram();
            ShaderProgram(
                const char* vertexShaderSource,
                const char* fragmentShaderSource);
            ShaderProgram(ShaderProgram&& other);
            ShaderProgram(const ShaderProgram&) = delete;
            ~ShaderProgram();

            ShaderProgram& operator=(ShaderProgram&& other);
            ShaderProgram& operator=(const ShaderProgram&) = delete;

            inline void Use()
            {
                glUseProgram(_program);
            }

            inline GLint GetUniformLocation(const GLchar* name)
            {
                return glGetUniformLocation(_program, name);
            }

            inline GLint GetAttributeLocation(const GLchar* name)
            {
                return glGetAttribLocation(_program, name);
            }

        protected:
        private:
            GLuint _program;
    };
}

#endif
