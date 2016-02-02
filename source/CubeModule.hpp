#ifndef CUBEMODULE_HPP
#define CUBEMODULE_HPP

#include "SDL2TK/Module.hpp"
#include "SDL2TK/Matrix4x4.hpp"
#include "SDL2TK/OpenGL/ShaderProgram.hpp"
#include "SDL2TK/Surface.hpp"

class CubeModule : public SDL2TK::Module
{
    public:
        CubeModule();
        virtual ~CubeModule();

        virtual void OnOpen();
        virtual void OnClose();
        virtual void OnLoop();
        virtual void OnPulse();
        virtual void OnSecond(int framesPerSecond);

        virtual void OnKeyDown(const SDL_Keysym& keysym);
        virtual void OnKeyUp(const SDL_Keysym& keysym);
        virtual void OnResize(int width, int height);

        virtual void OnControllerAxis(
            const SDL_ControllerAxisEvent& event);
        virtual void OnControllerButtonDown(
            const SDL_ControllerButtonEvent& event);
        virtual void OnControllerButtonUp(
            const SDL_ControllerButtonEvent& event);

    protected:
    private:
        int _pulseCount = 0;
        GLenum _caps[16];
        int _capCount = 0;

        SDL2TK::ShaderProgram _simpleProgram;
        GLint _positionAttribute;
        GLint _colorAttribute;

        SDL2TK::Matrix4x4F _viewMatrix;
        SDL2TK::RotationF _rotation;

        void LoadSimpleShaders();
        void Push(GLenum cap);
};

#endif
