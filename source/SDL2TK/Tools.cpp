#include "Tools.hpp"
#include <fstream>
#include <sstream>

namespace SDL2TK
{
    std::string FileToString(const char* path)
    {
        std::string result;

        if (path && *path)
        {
            std::ifstream stream(path, std::ifstream::binary);

            if (stream)
            {
                std::ostringstream oss;
                oss << stream.rdbuf();
                stream.close();
                result = oss.str();
            }
        }

        return result;
    }

    std::vector<char> GetFileContent(const char* path)
    {
        std::vector<char> result;

        if (path && *path)
        {
            std::ifstream stream(path, std::ifstream::binary);

            if (stream)
            {
                stream.seekg(0, std::ios::end);
                result.resize(stream.tellg());
                stream.seekg(0, std::ios::beg);
                stream.read(result.data(), result.size());
                stream.close();
            }
        }

        return result;
    }
}
