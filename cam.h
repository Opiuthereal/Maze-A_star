#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Cam {
private:
    glm::vec3 position;
    int viewIndex;     // 0=front, 1=right, 2=back, 3=left
    bool freeMode;

    // --- Free camera (quaternion) ---
    glm::quat orientation;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    void updateVectorsFromQuat();

public:
    Cam(const glm::vec3& startPos, bool free);

    // Cam non-free
    void turnLeft();
    void turnRight();
    void setDirection(const glm::vec3& dir); // <-- nouveau

    // Cam libre
    void processMouseMovement(float xoffset, float yoffset);
    void processKeyboard(char direction, float deltaTime);

    glm::mat4 getViewMatrix() const;

    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;
    bool isFree() const;
};

