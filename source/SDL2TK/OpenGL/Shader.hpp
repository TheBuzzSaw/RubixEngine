#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

namespace SDL2TK
{
    class Shader
    {
        public:
            enum class Type : GLenum
            {
                Vertex = GL_VERTEX_SHADER,
                Geometry = GL_GEOMETRY_SHADER,
                Fragment = GL_FRAGMENT_SHADER
            };

            Shader();
            Shader(Shader&& other);
            ~Shader();

            Shader& operator=(Shader&& other);

            std::string Compile(Type type, const char* source);

        private:
            Shader(const Shader& other) = delete;
            Shader& operator=(const Shader& other) = delete;

            GLuint _shader;

            friend class ProgramBuilder;
    };
}

#endif
