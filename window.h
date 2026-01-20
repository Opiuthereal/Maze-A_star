#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
    GLFWwindow* window;

public:
    // Le dernier paramètre permet de passer un monitor pour le plein écran (NULL = fenêtré)
    Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr);
    ~Window();

    bool isOpen() const;
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getGLFWwindow() const;
};

