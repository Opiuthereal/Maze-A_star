#include "cam.h"

Cam::Cam(const glm::vec3& startPos, bool free)
    : position(startPos),
      viewIndex(0),
      freeMode(free),
      orientation(glm::identity<glm::quat>()),
      front(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f),
      right(1.0f, 0.0f, 0.0f),
      worldUp(0.0f, 1.0f, 0.0f)
{
    updateVectorsFromQuat();
}

void Cam::updateVectorsFromQuat() {
    front = glm::normalize(orientation * glm::vec3(0, 0, -1));
    right = glm::normalize(orientation * glm::vec3(1, 0, 0));
    up    = glm::normalize(orientation * glm::vec3(0, 1, 0));
}

// ------------------ NON-FREE ------------------

void Cam::turnLeft() {
    if (!freeMode) viewIndex = (viewIndex + 3) % 4;
}

void Cam::turnRight() {
    if (!freeMode) viewIndex = (viewIndex + 1) % 4;
}

// Permet de définir la direction de la cam non-free
void Cam::setDirection(const glm::vec3& dir) {
    if (!freeMode) {
        glm::vec3 forward = glm::normalize(dir);
        // Trouver l'axe de rotation autour de Y pour correspondre aux 4 directions
        float angle = atan2(forward.x, -forward.z); // angle Y en rad
        if (angle < 0) angle += 2.0f * 3.14159265f;
        viewIndex = int((angle + 3.14159265f/4.0f) / (3.14159265f/2.0f)) % 4;
    }
}

// ------------------ FREE ------------------

void Cam::processMouseMovement(float xoffset, float yoffset) {
    if (!freeMode) return;
    float sensitivity = 0.00002f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    glm::quat yawQuat   = glm::angleAxis(-xoffset, worldUp);
    glm::quat pitchQuat = glm::angleAxis(-yoffset, right);

    orientation = glm::normalize(yawQuat * pitchQuat * orientation);
    updateVectorsFromQuat();
}

void Cam::processKeyboard(char direction, float deltaTime) {
    if (!freeMode) return;
    float velocity = 5.0f * deltaTime;

    if (direction == 'W') position += front * velocity;
    if (direction == 'S') position -= front * velocity;
    if (direction == 'A') position -= right * velocity;
    if (direction == 'D') position += right * velocity;
}

// ------------------ VIEW ------------------

glm::mat4 Cam::getViewMatrix() const {
    if (freeMode) {
        return glm::lookAt(position, position + front, up);
    } else {
        static const glm::vec3 directions[4] = {
            {0,0,-1}, {1,0,0}, {0,0,1}, {-1,0,0}
        };
        glm::vec3 forward = directions[viewIndex];
        return glm::lookAt(position, position + forward, worldUp);
    }
}

void Cam::setPosition(const glm::vec3& pos) { position = pos; }
glm::vec3 Cam::getPosition() const { return position; }
bool Cam::isFree() const { return freeMode; }

