#include<iostream>
#include "window.h"
using namespace std;

// Constructeur : crée la fenêtre et initialise OpenGL
Window::Window(int width, int height, const char* title, GLFWmonitor* monitor) 
{
    if (!glfwInit()) 
    {
        std::cerr << "Erreur : impossible d'initialiser GLFW\n";
        window = nullptr;
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Création de la fenêtre (plein écran si monitor != nullptr)
    window = glfwCreateWindow(width, height, title, monitor, nullptr);
    if (!window) 
    {
        std::cerr << "Erreur : impossible de créer la fenêtre GLFW\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Erreur : impossible d'initialiser GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
        return;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h)
    {
        glViewport(0, 0, w, h);
    });
}

// Vérifie si la fenêtre est ouverte
bool Window::isOpen() const 
{
    return window && !glfwWindowShouldClose(window);
}

// Swap les buffers pour afficher le rendu
void Window::swapBuffers() 
{
    if (window)
        glfwSwapBuffers(window);
}

// Récupère les événements
void Window::pollEvents() 
{
    glfwPollEvents();
}

// Accès direct à la fenêtre GLFW
GLFWwindow* Window::getGLFWwindow() const 
{
    return window;
}

// Destructeur qui nettoie GLFW automatiquement
Window::~Window() 
{
    if (window) 
    {
        glfwDestroyWindow(window);
        window = nullptr; // sécurité
    }
}

