// Window.cpp
#include "affichage.h"
using namespace std;

// Constructeur : crée la fenêtre et initialise OpenGL
Window::Window(int width, int height, const char* title) 
{
	//glfw ne s'initialise pas ?
	if (!glfwInit()) 
	{
		cerr << "Erreur : impossible d'initialiser GLFW\n";
		window = nullptr;
		return;
	}
	
	//infos sur la version à utiliser
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//création et vérification de la création de la fenêtre
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) 
	{
		cerr << "Erreur : impossible de créer la fenêtre GLFW\n";
		glfwTerminate();
		return;
	}
	
	//on modifie sur la fenêtre qui vient d
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		cerr << "Erreur : impossible d'initialiser GLAD\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		window = nullptr;
		return;
	}

	// Callback pour redimensionnement
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h)
	{
		glViewport(0, 0, w, h);
	});
}

// Destructeur qui nettoie GLFW automatiquement
Window::~Window() 
{
	if (window) 
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
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

