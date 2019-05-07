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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// 着色器
	Shader shader("vertexShader.vs", "fragmentShader.fs");


	// 立方体顶点坐标
	float vertices[] = {
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,

		-2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		-2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		-2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,

		-2.0f,  2.0f,  2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f,  2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f, -2.0f,  2.0f,  0.0f, 0.0f, 1.0f,
		-2.0f,  2.0f,  2.0f,  0.0f, 0.0f, 1.0f,

		 2.0f,  2.0f,  2.0f,  1.0f, 1.0f, 0.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		 2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		 2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		 2.0f, -2.0f,  2.0f,  1.0f, 1.0f, 0.0f,
		 2.0f,  2.0f,  2.0f,  1.0f, 1.0f, 0.0f,

		-2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		-2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 1.0f,

		-2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		-2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 1.0f
	};


	// ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();

	// 初始化变量
	unsigned int VAO, VBO;
	// part 1
	static int perspective = 1;
	float p_fov = 45.0f;
	float p_near = 0.1f;
	float p_far = 100.0f;
	float o_top = 10.0f;
	float o_left = -10.0f;
	float o_right = 10.0f;
	float o_bottom = -10.0f;
	float o_near = -4.0f;
	float o_far = 100.0f;
	// part 2
	bool camera_rotate = false;
	float camera_x = 8.0f;
	float camera_z = 8.0f;

	// 设置VAO VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// 设置位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 设置颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	float size = 0.0f;
	bool add = true;
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glEnable(GL_DEPTH_TEST);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool ImGui = true;
		ImGui::Begin("choose", &ImGui, ImGuiWindowFlags_MenuBar);

		ImGui::Checkbox("camera_rotate", &camera_rotate);
		
		ImGui::RadioButton("perspective", &perspective, 1); ImGui::SameLine();
		ImGui::RadioButton("orthographic", &perspective, 0);

		if (perspective) {
			ImGui::SliderFloat("p_fov", &p_fov, 0.0f, 200.0f);
			ImGui::SliderFloat("p_near", &p_near, 0.0f, 20.0f);
			ImGui::SliderFloat("p_far", &p_far, 0.0f, 1000.0f);
		} else {
			ImGui::SliderFloat("o_left", &o_left, -20.0f, 20.0f);
			ImGui::SliderFloat("o_right", &o_right, -20.0f, 20.0f);
			ImGui::SliderFloat("o_bottom", &o_bottom, -20.0f, 20.0f);
			ImGui::SliderFloat("o_top", &o_top, -20.0f, 20.0f);
			ImGui::SliderFloat("o_near", &o_near, -4.0f, 4.0f);
			ImGui::SliderFloat("o_far", &o_far, 1.0f, 100.0f);
		}

		ImGui::End();

		int view_width, view_height;
		glfwGetFramebufferSize(window, &view_width, &view_height);
		glViewport(0, 0, view_width, view_height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// 使用着色器
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// part 1
		if (perspective) {
			projection = glm::perspective(glm::radians(p_fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, p_near, p_far);
			// part 2
			if (camera_rotate) {
				camera_x = sin((float)glfwGetTime()) * 8.0f;
				camera_z = cos((float)glfwGetTime()) * 8.0f;
				view = glm::lookAt(glm::vec3(camera_x, 8, camera_z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			}
			else {
				camera_x = 8.0f;
				camera_z = 8.0f;
				view = glm::lookAt(glm::vec3(camera_x, camera_z, 8), glm::vec3(-1.5f, 0.5f, -1.5f), glm::vec3(0, 1, 0));
			}
		} else {
			projection = glm::ortho(o_left, o_right, o_bottom, o_top, o_near, o_far);
			model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.5f));
		}
		
		shader.setMat4("view", view);
		shader.setMat4("model", model);
		shader.setMat4("projection", projection);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// 释放gui资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}