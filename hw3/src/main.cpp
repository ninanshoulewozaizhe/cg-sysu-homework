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
#include "Drawtriangle.h"
#include "DrawCircle.h"


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

	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
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


	//初始化颜色
	ImVec4 top_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImVec4 left_color = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	ImVec4 right_color = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);

	glPointSize(3.0f);

	Shader shader("vertexShader.vs", "fragmentShader.fs");

	//创建并绑定ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();

	// 初始化展示选项
	unsigned int VAO, VBO, EBO;
	bool draw_trangle = true;
	bool fill_trangle = false;
	bool fill_record = false;
	bool draw_record = true;
	//hw3 
	Triangle triangle = Triangle(-200.0f, -200.0f, 200.0f, -200.0f, 0.0f, 200.0f);
	Circle circle = Circle(0, 0, 200);
	float* vertices = triangle.getDrawPoints(fill_trangle);
	int pointsCount = 0;

	float circle_r = 200.0f;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		if (draw_trangle) {
			if (!fill_trangle || fill_record != fill_trangle || !draw_record) {
				vertices = triangle.getDrawPoints(fill_trangle);
				pointsCount = triangle.getPointsCount();
				fill_record = fill_trangle;
			}
		}
		else {
			circle.setR(circle_r);
			vertices = circle.getDrawPoints();
			pointsCount = circle.getPointsCount();
		}
		draw_record = draw_trangle;

		// 创建VAO、VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		// 设置缓冲
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, pointsCount * 6 * sizeof(float), vertices, GL_STREAM_DRAW);

		// 链接属性
		// 位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 颜色属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	    glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool ImGui = true;
		ImGui::Begin("Edit color", &ImGui, ImGuiWindowFlags_MenuBar);
		ImGui::SliderFloat("float", &circle_r, 100.0f, 400.0f);
		ImGui::Checkbox("trangle", &draw_trangle);
		ImGui::Checkbox("fill trangle", &fill_trangle);
		ImGui::End();

		int view_width, view_height;
		glfwGetFramebufferSize(window, &view_width, &view_height);
		glViewport(0, 0, view_width, view_height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 激活对象
		shader.use();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//glEnableVertexAttribArray(1);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, pointsCount);
		
		glfwSwapBuffers(window);
	}

	// 释放内存占用
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// 释放ImGui资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}