#include "TestModule.hpp"
#include "SDL2TK/Tools.hpp"
#include <iostream>
using namespace std;

TestModule::TestModule()
{
    LoadSimpleShaders();
}

TestModule::~TestModule()
{
}

void TestModule::OnOpen()
{
    _simpleProgram.Use();
    glMatrixMode(GL_MODELVIEW);
}

void TestModule::OnClose()
{
    glDisable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

void TestModule::OnLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    constexpr float N = 1.0f;

    const float Data[] =
    {
        -N, -N, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        N, -N, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        N, N, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -N, N, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    _simpleProgram.Use();
    glEnableVertexAttribArray(_positionAttribute);
    glEnableVertexAttribArray(_colorAttribute);

    glLoadMatrixf(_viewMatrix);

    glVertexAttribPointer(
        _positionAttribute,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 7,
        Data);

    glVertexAttribPointer(
        _colorAttribute,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 7,
        Data + 3);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableVertexAttribArray(_colorAttribute);
    glDisableVertexAttribArray(_positionAttribute);
}

void TestModule::OnPulse()
{
    ++_pulseCount;

    _rotation += SDL2TK::RotationF::FromDegrees(3.0f);

    _viewMatrix
        .LoadIdentity()
        .Translate(0.0f, 0.0f, -32.0f)
        .RotateX(SDL2TK::RotationF::FromDegrees(-45.0f))
        .RotateZ(SDL2TK::RotationF::FromDegrees(-45.0f));
}

void TestModule::OnSecond(int framesPerSecond)
{
    return;
    cout
        << framesPerSecond << " frames, "
        << _pulseCount << " pulses"
        << endl;

    _pulseCount = 0;
}

void TestModule::OnKeyDown(const SDL_Keysym& keysym)
{
    Module::OnKeyDown(keysym);
}

void TestModule::OnKeyUp(const SDL_Keysym& keysym)
{
}

void TestModule::OnControllerAxis(const SDL_ControllerAxisEvent& event)
{
}

void TestModule::OnControllerButtonDown(const SDL_ControllerButtonEvent& event)
{
}

void TestModule::OnControllerButtonUp(const SDL_ControllerButtonEvent& event)
{
}

void TestModule::OnResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    SDL2TK::Matrix4x4F matrix;
    matrix.Perspective(
        SDL2TK::RotationF::FromDegrees(30.0f),
        float(width) / float(height),
        1.0f,
        512.0f);
    //matrix.Orthographic(1.0f, float(width) / float(height));

    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void TestModule::LoadSimpleShaders()
{
    _simpleProgram = SDL2TK::ShaderProgram::FromFiles(
        "simple.vertex.shader", "simple.fragment.shader");

    _positionAttribute = _simpleProgram.GetAttributeLocation("position");
    _colorAttribute = _simpleProgram.GetAttributeLocation("color");
}
