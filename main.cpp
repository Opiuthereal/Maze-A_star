#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <filesystem>

#include "face.h"
#include "shader.h"
#include "renderable.h"
#include "window.h"
#include "cam.h"
#include "maze.h"
#include "renderMaze.h"

using namespace std;

int main() {
    // --- Init GLFW ---
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    int windowWidth = mode->width;
    int windowHeight = mode->height;

    Window window(windowWidth, windowHeight, "Cube 3D", primaryMonitor);
    if (!window.isOpen()) return -1;
    GLFWwindow* glfwWindow = window.getGLFWwindow();

    // --- Init GLAD ---
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // --- Chargement maze ---
    filesystem::path exeDir = filesystem::current_path();
    Maze maze((exeDir / "source.mz").string());

    // --- Caméras ---
    Cam playerCam(glm::vec3(0.0f, 0.0f, 0.0f), false); // caméra joueur (non-free)
    playerCam.setPosition(glm::vec3(1.0f, 5.0f, 1.0f));
    playerCam.setDirection(glm::vec3(0.0f, 0.0f, 0.0f));
    
    Cam debugCam(glm::vec3(0.0f, 10.0f, 10.0f), true); // caméra libre quaternion
    Cam* activeCam = &playerCam;

    glfwSetInputMode(
        glfwWindow,
        GLFW_CURSOR,
        activeCam->isFree() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
    );

    // --- Shader ---
    Shader shader(
        (exeDir / "vertex.glsl").string(),
        (exeDir / "fragment.glsl").string()
    );

    // --- Rendu maze ---
    RenderMaze renderMaze(maze, 1.0f);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        float(windowWidth) / float(windowHeight),
        0.1f,
        100.0f
    );

    glEnable(GL_DEPTH_TEST);

    float lastFrame = 0.0f;

    // --- États touches ---
    bool escLast = false;
    bool cLast   = false;
    bool qLast   = false;
    bool dLast   = false;

    // ================= MAIN LOOP =================
    while (window.isOpen()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- ESC : libérer / capturer souris ---
        bool escNow = glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
        if (escNow && !escLast && activeCam->isFree()) {
            int mode = glfwGetInputMode(glfwWindow, GLFW_CURSOR);
            glfwSetInputMode(
                glfwWindow,
                GLFW_CURSOR,
                mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
            );
        }
        escLast = escNow;

        // --- C : switch caméra ---
        bool cNow = glfwGetKey(glfwWindow, GLFW_KEY_C) == GLFW_PRESS;
        if (cNow && !cLast) {
            activeCam = (activeCam == &playerCam) ? &debugCam : &playerCam;
            glfwSetInputMode(
                glfwWindow,
                GLFW_CURSOR,
                activeCam->isFree() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
            );
        }
        cLast = cNow;

        // --- Contrôles ---
        if (activeCam->isFree()) {
            // déplacement
            if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS) activeCam->processKeyboard('W', deltaTime);
            if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS) activeCam->processKeyboard('S', deltaTime);
            if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS) activeCam->processKeyboard('A', deltaTime);
            if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS) activeCam->processKeyboard('D', deltaTime);

            // souris
            double xpos, ypos;
            glfwGetCursorPos(glfwWindow, &xpos, &ypos);
            float xoffset = float(xpos) - windowWidth / 2.0f;
            float yoffset = windowHeight / 2.0f - float(ypos);

            activeCam->processMouseMovement(xoffset, yoffset);
            glfwSetCursorPos(glfwWindow, windowWidth / 2.0, windowHeight / 2.0);
        }
        else {
            // caméra non-free : rotation par Q/D
            bool qNow = glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS;
            bool dNow = glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS;

            if (qNow && !qLast) activeCam->turnLeft();
            if (dNow && !dLast) activeCam->turnRight();

            qLast = qNow;
            dLast = dNow;
        }

        // --- Rendu ---
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", activeCam->getViewMatrix());
        shader.setMat4("model", glm::mat4(1.0f));

        renderMaze.draw(shader);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}

