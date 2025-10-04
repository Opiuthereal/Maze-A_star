#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
    GLFWwindow* window;

public:
    Window(int width, int height, const char* title);
    ~Window(); //destructeur

    bool isOpen() const;
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getGLFWwindow() const;
};
