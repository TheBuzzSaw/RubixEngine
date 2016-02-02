#include "SDL2TK/Window.hpp"
#include "TestModule.hpp"
#include "Rectangle.hpp"
#include <SDL_image.h>
#include <vector>
using namespace std;

void MyCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *msg,
    const void *data)
{
    if (id != 131218) // http://stackoverflow.com/a/13201020
        cerr << "OpenGL debug -- " << id << " -- " << msg << endl;
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    {
        /* Open the first available controller. */
        SDL_GameController *controller = NULL;
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            if (SDL_IsGameController(i))
            {
                controller = SDL_GameControllerOpen(i);
                if (controller)
                {
                    break;
                }
                else
                {
                    fprintf(
                        stderr,
                        "Could not open gamecontroller %i: %s\n",
                        i,
                        SDL_GetError());
                }
            }
        }

        SDL2TK::WindowSettings settings;
        settings.Title("CityCube");
        settings.Width(1024);
        settings.Height(768);

        SDL2TK::Window window(move(settings));
        SDL_GL_SetSwapInterval(1);

        glDebugMessageCallback(MyCallback, nullptr);

        GLint v;
        glGetIntegerv(GL_CONTEXT_FLAGS, &v);
        if (v & GL_CONTEXT_FLAG_DEBUG_BIT)
            cerr << "DEBUG MODE\n";

        TestModule module;
        window.Run(module);
    }

    IMG_Quit();
    SDL_Quit();
    return 0;
}
