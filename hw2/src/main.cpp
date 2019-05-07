#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imconfig.h"
#include <iostream>

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


	//初始化颜色
	ImVec4 top_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImVec4 left_color = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	ImVec4 right_color = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);


	Shader shader("vertexShader.vs", "fragmentShader.fs");

	//创建并绑定ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();

	// 初始化展示选项
	unsigned int VAO, VBO, EBO;
	bool draw_no_color_trangle = true;
	bool draw_render_trangle = false;
	bool draw_line = false;
	bool draw_another_trangle = false;
	bool draw_point = false;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//设置顶点位置
		float vertices[] = {
			// 位置              // 颜色
			// 三角形
			0.5f, -0.5f, 0.0f,  right_color.x, right_color.y, right_color.z,   // 右下
		   -0.5f, -0.5f, 0.0f,  left_color.x, left_color.y, left_color.z,   // 左下
			0.0f,  0.5f, 0.0f,  top_color.x, top_color.y, top_color.z,    // 顶部
			0.7f,  0.2f, 0.0f,  top_color.x, top_color.y, top_color.z,
		   // 线段
			-0.7f, -0.7f, 0.0f,  1.0f, 0.0f, 0.0f, 
			0.7f, -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,
		   // 点
		   0.0f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.1f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.2f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.3f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.4f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.5f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   0.1f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   0.2f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   0.3f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   0.4f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		   0.5f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		// 创建VAO、VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		// 设置缓冲
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// 链接属性
		// 位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 颜色属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	    //glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool ImGui = true;
		ImGui::Begin("Edit color", &ImGui, ImGuiWindowFlags_MenuBar);

		ImGui::ColorEdit3("top color", (float*)&top_color);
		ImGui::ColorEdit3("left color", (float*)&left_color);
		ImGui::ColorEdit3("right color", (float*)&right_color);
		ImGui::Checkbox("no color trangle", &draw_no_color_trangle);
		ImGui::Checkbox("render trangle", &draw_render_trangle);
		ImGui::Checkbox("line", &draw_line);
		ImGui::Checkbox("another triangle", &draw_another_trangle);
		ImGui::Checkbox("point", &draw_point);

		ImGui::End();

		int view_width, view_height;
		glfwGetFramebufferSize(window, &view_width, &view_height);
		glViewport(0, 0, view_width, view_height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 激活对象
		shader.use();
		// 更新颜色
		// float timeValue = glfwGetTime();
		// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// int vertexColorLocation = glGetUniformLocation(shader.getID(), "ourColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		// 绘制三角形
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// 单色三角形
		if (draw_no_color_trangle) {
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (draw_render_trangle) {
			glEnableVertexAttribArray(1);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		} 
		if (draw_line) {
			glEnableVertexAttribArray(1);
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 4, 2);
		}
		if (draw_another_trangle) {
			glEnableVertexAttribArray(1);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		if (draw_point) {
			glEnableVertexAttribArray(1);
			glBindVertexArray(VAO);
			glDrawArrays(GL_POINTS, 6, 11);
		}

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