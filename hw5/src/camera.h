#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imconfig.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Camera {
public:
	Camera(glm::vec3 cameraPos, glm::vec3 objPos, glm::vec3 cameraUp) {
		this->cameraPos = cameraPos;
		this->cameraFront = objPos - cameraPos;
		this->cameraUp = cameraUp;
	}

	void moveForward(float const moveSpeed) {
		//std::cout << "forward: " << (cameraFront * moveSpeed).x << ' ' <<(cameraFront * moveSpeed).y << ' ' << (cameraFront * moveSpeed).z  <<endl;
		cameraPos += cameraFront * moveSpeed;
	}
	void moveBack(float const moveSpeed) {
		//std::cout << "back: " << (cameraFront * moveSpeed).x << ' ' << (cameraFront * moveSpeed).y << ' ' << (cameraFront * moveSpeed).z << endl;
		cameraPos -= cameraFront * moveSpeed;

	}
	void moveRight(float const moveSpeed) {
		//std::cout << "right: " << (cameraRight * moveSpeed).x << ' ' << (cameraRight * moveSpeed).y << ' ' << (glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * moveSpeed).z << endl;
		cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * moveSpeed;

	}
	void moveLeft(float const moveSpeed) {
		//std::cout << "left: " << (cameraRight * moveSpeed).x << ' ' << (cameraRight * moveSpeed).y << ' ' << (glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * moveSpeed).z << endl;
		cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * moveSpeed;

	}
	void rotate(GLfloat const pitch, GLfloat const yaw) {
		glm::vec3 front = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
		cameraFront = glm::normalize(front);
	}

	glm::vec3 getCameraPos() {
		return cameraPos;
	}

	glm::vec3 getCameraFront() {
		return cameraFront;
	}

	glm::vec3 getCameraUp() {
		return cameraUp;
	}

private:
	
	GLfloat pfov, pratio, pnear, pfar;
	glm::vec3 cameraPos, cameraFront, cameraUp;

};