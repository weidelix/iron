////// DEPENDENCIES //////
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
////// STANDARD LIBRARY //////
#include <iostream>
#include <string>
#include <math.h>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shaders.h"
#include "Texture2D.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/string_cast.hpp"

//glm::vec3 cameraPos(0.0f, 0.0f, 7.0f);
//// Camera direction
//glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
//glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTarget);
//// Camera right
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDir));
//// Camera up
//glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);

bool cursorLocked = false;
bool fpsView = false;
bool firstMouse_right = true;
bool firstMouse_left = true;
float lastX_right = 200, lastY_right = 200;
float lastX_left = 200, lastY_left = 200;
float pitch = 0, yaw = -90;

float deltaTime = 0.0f;

float rotation_Sensitivity = 60.0f;
float pan_Sensitivity = 4.0f;
float zoom_Sensitivity = 150.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int width = 800, height = 480;
Shaders* shad = nullptr;
Shaders* lightShad = nullptr;
glm::mat4* proj = nullptr;

void RotateAndPanCamera(GLFWwindow* window, double xpos, double ypos)
{
	if (ImGui::GetIO().WantCaptureMouse == false)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			if (firstMouse_right)
			{
				lastX_right = xpos;
				lastY_right = ypos;
				firstMouse_right = false;
			}

			float xoffset = xpos - lastX_right;
			float yoffset = lastY_right - ypos; // reversed since y-coordinates range from bottom to top
			lastX_right = xpos;
			lastY_right = ypos;

			xoffset *= rotation_Sensitivity * deltaTime;
			yoffset *= rotation_Sensitivity * deltaTime;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(direction);
		}

		else firstMouse_right = true;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{

			if (firstMouse_left)
			{
				lastX_left = xpos;
				lastY_left = ypos;
				firstMouse_left = false;
			}

			float xoffset = xpos - lastX_left;
			float yoffset = lastY_left - ypos; // reversed since y-coordinates range from bottom to top
			lastX_left = xpos;
			lastY_left = ypos;

			const float cameraSpeed = pan_Sensitivity * deltaTime;

			if (xoffset > 0.0)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed * xoffset);
			if (xoffset < 0.0)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed * -xoffset);

			if (yoffset < 0.0)
				cameraPos -= glm::normalize(glm::cross(cameraFront, glm::cross(cameraFront, cameraUp))) * (cameraSpeed * -yoffset);
			if (yoffset > 0.0)
				cameraPos += glm::normalize(glm::cross(cameraFront, glm::cross(cameraFront, cameraUp))) * (cameraSpeed * yoffset);
		}

		else firstMouse_left = true;
	}
}
void ZoomCamera(GLFWwindow* window, double xoffset, double yoffset)
{
	if (ImGui::GetIO().WantCaptureMouse == false)
	{
		const float cameraSpeed = zoom_Sensitivity * deltaTime;

		if (yoffset > 0) cameraPos += cameraSpeed * cameraFront;
		else if (yoffset < 0) cameraPos -= cameraSpeed * cameraFront;
	}
}

void OnWindowResize(GLFWwindow*, int width, int height)
{
	*proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);
	shad->SetMat4x4("projection", *proj);
	lightShad->SetMat4x4("projection", *proj);
}

void OnKeyPress(GLFWwindow* window, float deltaTime)
{
	if (fpsView)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {}

	}
}

glm::mat4 LookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	glm::vec3 z = glm::normalize(position - target);
	glm::vec3 x = glm::normalize(glm::cross(z, glm::normalize(up)));
	glm::vec3 y = glm::cross(z, x);

	glm::mat4 translation(1.0f);
	translation[3][0] = -position.x;
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;

	glm::mat4 view(1.0f);
	view[0][0] = x.x;
	view[1][0] = x.y;
	view[2][0] = x.z;

	view[0][1] = y.x;
	view[1][1] = y.y;
	view[2][1] = y.z;

	view[0][2] = z.x;
	view[1][2] = z.y;
	view[2][2] = z.z;

	return view * translation;
}

void CherryTheme() {
	// cherry colors, 3 intensities
	#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
	#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
	#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
	// backgrounds (@todo: complete with BG_MED, BG_LOW)
	#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
	// text
	#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = TEXT(0.78f);
	style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	//style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
	style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
	style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);

	style.Colors[ImGuiCol_Tab] = MED(0.76f);
	style.Colors[ImGuiCol_TabHovered] = MED(0.86f);
	style.Colors[ImGuiCol_TabActive] = HI(1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = LOW(0.60f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = MED(0.60f);

	style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
	style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
	style.Colors[ImGuiCol_Header] = MED(0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
	style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
	//.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
	//style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
	//style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
	style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
	// [...]
	style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

	style.WindowPadding = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.FramePadding = ImVec2(5, 2);
	style.FrameRounding = 3.0f;
	style.ItemSpacing = ImVec2(7, 1);
	style.ItemInnerSpacing = ImVec2(1, 1);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 2.0f;

	style.WindowTitleAlign.x = 0.50f;

	style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
	style.FrameBorderSize = 0.0f;
	style.WindowBorderSize = 1.0f;
}


int main()
{
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, "Iron Engine", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);
		glfwSetCursorPosCallback(window, RotateAndPanCamera);
		glfwSetScrollCallback(window, ZoomCamera);
		glfwSetWindowSizeCallback(window, OnWindowResize);

		if (glewInit() != GLEW_OK) std::cout << "Something went wrong!" << std::endl;

		glEnable(GL_DEPTH_TEST);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("res/fonts/JetBrainsMono-Regular.ttf", 15);
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true); // Windows without contexts must not be passed to
		ImGui_ImplOpenGL3_Init("#version 330");
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		float light[] =
		{
			-0.5f,  0.5f, -2.5f,
			-0.5f, -0.5f, -2.5f,
			 0.5f, -0.5f, -2.5f,
			 0.5f,  0.5f, -2.5f,

			-0.5f,  0.5f,  -1.5f,
			-0.5f, -0.5f,  -1.5f,
			 0.5f, -0.5f,  -1.5f,
			 0.5f,  0.5f,  -1.5f,
		};

		unsigned int lightIndices[] =
		{
			0, 1, 2,  2, 3, 0,
			3, 2, 6,  6, 7, 3,
			7, 6, 4,  4, 5, 6,
			4, 5, 1,  1, 0, 4,
			0, 3, 7,  7, 4, 0,
			1, 2, 6,  6, 5, 1
		};

		float v1[] =
		{
			//   Position				 Color					Text-Coord		Normal
				-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, -1.0f, //0
				-0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, -1.0f, //1
				 0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, -1.0f, //2
				 0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, -1.0f, //2
				 0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, -1.0f, //3
				-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, -1.0f, //0

				 0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //3
				 0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //2
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //6
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //6
				 0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //7
				 0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	1.0f, 0.0f, 0.0f, //3

				 0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, 1.0f, //7
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, 1.0f, //6
				-0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, 1.0f, //4
				-0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, 1.0f, //4
				-0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 0.0f, 1.0f, //5
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 0.0f, 1.0f, //6

				-0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //4
				-0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //5
				-0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //1
				-0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //1
				-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //0
				-0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,    -1.0f, 0.0f, 0.0f, //4

				-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 1.0f, 0.0f, //0
				 0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 1.0f, 0.0f, //3
				 0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 1.0f, 0.0f, //7
				 0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, 1.0f, 0.0f, //7
				-0.5f,  0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 1.0f, 0.0f, //4
				-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, 1.0f, 0.0f, //0

				-0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, -1.0f, 0.0f, //1
				 0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, -1.0f, 0.0f, //2
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, -1.0f, 0.0f, //6
				 0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 1.0f,   	0.0f, -1.0f, 0.0f, //6
				-0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, -1.0f, 0.0f, //5
				-0.5f, -0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,	 	0.0f, 0.0f,   	0.0f, -1.0f, 0.0f, //1
		};

		unsigned int indices[] =
		{
			0, 1, 2,  2, 3, 0,
			3, 2, 6,  6, 7, 3,
			7, 6, 4,  4, 5, 6,
			4, 5, 1,  1, 0, 4,
			0, 3, 7,  7, 4, 0,
			1, 2, 6,  6, 5, 1
		};

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);
		glm::mat4 view(1.0f);
		proj = &projection;
		const float radius = 15.0f;

		glm::vec3 lightPos(1.0f, -1.0f, -1.0f);
		glm::vec3 objectPos(0.0f, 0.0f, 0.0f);

		VertexArray lightVAO = VertexArray();
		lightVAO.VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);

		VertexArray::VertexAttribBinding(0, 0);
		VertexArray::EnableVertexAttribArray(0);

		VertexBuffer lightVBO = VertexBuffer(light, 24 * sizeof(float));
		IndexBuffer lightIBO = IndexBuffer(indices, 36);

		Shaders lightShader = Shaders(ShaderSource::ParseShaderSource("res/shaders/lighting.shader"));
		lightShad = &lightShader;
		lightShader.SetMat4x4("projection", projection);
		lightVBO.BindVertex(0, 0, 3 * sizeof(float));
		lightVAO.Unbind();

		VertexArray vao = VertexArray();

		// (Attrib_Index)-(Number of components per attribute)-(Type)-(Normalize?)-(Offset of Attribute)
		vao.VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
		vao.VertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		vao.VertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
		vao.VertexAttribFormat(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float));

		VertexArray::VertexAttribBinding(0, 0);
		VertexArray::VertexAttribBinding(1, 0);
		VertexArray::VertexAttribBinding(2, 0);
		VertexArray::VertexAttribBinding(3, 0);

		VertexArray::EnableVertexAttribArray(0);
		VertexArray::EnableVertexAttribArray(1);
		VertexArray::EnableVertexAttribArray(2);
		VertexArray::EnableVertexAttribArray(3);

		VertexBuffer vbo = VertexBuffer(v1, 396 * sizeof(float));
		vbo.BindVertex(0, 0, 11 * sizeof(float));
		IndexBuffer ibo = IndexBuffer(indices, 36);

		Texture2D texture = Texture2D("res/textures/Grass_sample.png", 0);
		texture.UseTexture(0);

		vbo.Unbind();
		Shaders shader = Shaders(ShaderSource::ParseShaderSource("res/shaders/basic.shader"));
		shader.SetInt1("texture0", 0);
		shader.SetInt1("texture1", 1);
		shader.SetInt1("texture2", 2);
		shader.SetInt1("texture3", 3);
		shad = &shader;
		shader.SetMat4x4("projection", projection);
		shader.SetFloat3("lightColor", 1.0f, 1.0f, 1.0f);

		float lastFrame = 0.0f; // Time of last frame

		float pos[3] = { 0.0f, 0.0f, 0.0f };
		float light_pos[3] = { 1.0f, -1.0f, -1.0f };
		float camera_pos[3] = { 0.0f, 0.0f, 3.0f };

		// ImGui Styles
		CherryTheme();
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 2.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		float specStrength = 0.5f;
		int shineIntensity = 32;
		float ambientStrength = 0.1f;
		float brightness = 1.0f;

		shader.SetFloat1("specularStrength", specStrength);
		shader.SetInt1("shineIntensity", shineIntensity);
		shader.SetFloat1("ambientStrength", ambientStrength);
		shader.SetFloat1("brightness", brightness);

		bool showViewPortCameraSettings = false;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Renderer and engine settings 
			{
				if (ImGui::BeginMainMenuBar())
				{
					ImGui::MenuItem("Camera Settings", NULL, &showViewPortCameraSettings);
					ImGui::EndMainMenuBar();
				}

				if (showViewPortCameraSettings)
				{
					ImGui::SetNextWindowSize({200, 350});
					ImGui::Begin("Viewport Camera Settings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
					ImGui::PushItemWidth(-1);
					ImGui::Text("Rotation Sensitivity");
					ImGui::SliderFloat("##hidden Rotation Sensitivity", &rotation_Sensitivity, 1.0f, 150.0f);			
					ImGui::Text("Pan Sensitivity");
					ImGui::SliderFloat("##hidden Pan Sensitivity", &pan_Sensitivity, 1.0f, 150.0f);
					ImGui::Text("Zoom Sensitivity");
					ImGui::SliderFloat("##hidden Zoom Camera Sensitivity", &zoom_Sensitivity, 1.0f, 500.0f);
					ImGui::PopItemWidth();
					ImGui::SameLine(ImGui::GetWindowWidth() - 60);
					ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
					if (ImGui::Button("Close")) showViewPortCameraSettings = false;
					ImGui::End();
				}
			}

			{
				ImGui::SetNextWindowPos(ImVec2(0, 20));
				ImGui::Begin("Properties");

				ImGui::BeginTabBar("tab");
				if (ImGui::BeginTabItem("Test Object"))
				{
					ImGui::Text("Position");
					ImGui::PushItemWidth((ImGui::GetWindowWidth() / 3) - 32);
					ImGui::Text("x:");								  ImGui::SameLine();
					ImGui::DragFloat("##hidden x", &pos[0], 0.05f);   ImGui::SameLine();
					ImGui::Text("y:");								  ImGui::SameLine();
					ImGui::DragFloat("##hidden y", &pos[1], 0.05f);   ImGui::SameLine();
					ImGui::Text("z:");								  ImGui::SameLine();
					ImGui::DragFloat("##hidden z", &pos[2], 0.05f);
					ImGui::PopItemWidth();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Light"))
				{
					ImGui::Text("Position");
					ImGui::PushItemWidth((ImGui::GetWindowWidth() / 3) - 32);
					ImGui::Text("x:");										ImGui::SameLine();
					ImGui::DragFloat("##hidden x", &light_pos[0], 0.05f);   ImGui::SameLine();
					ImGui::Text("y:");										ImGui::SameLine();
					ImGui::DragFloat("##hidden y", &light_pos[1], 0.05f);   ImGui::SameLine();
					ImGui::Text("z:");										ImGui::SameLine();
					ImGui::DragFloat("##hidden z", &light_pos[2], 0.05f);
					ImGui::PopItemWidth();
					ImGui::NewLine();
					ImGui::SliderFloat("Specular", &specStrength, 0.0f, 1.0f);
					ImGui::SliderInt("Shine", &shineIntensity, 2, 256);
					ImGui::SliderFloat("Ambient", &ambientStrength, 0.0f, 1.0f);
					ImGui::SliderFloat("Brightness", &brightness, 0.0f, 50.0f);
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Camera"))
				{
					ImGui::DragFloat3("Position", camera_pos, 0.05f);
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();

				/*ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/
				ImGui::End();

				objectPos.x = pos[0];
				objectPos.y = pos[1];
				objectPos.z = pos[2];

				lightPos.x = light_pos[0];
				lightPos.y = light_pos[1];
				lightPos.z = light_pos[2];

				//cameraPos.x = camera_pos[0];
				//cameraPos.y = camera_pos[1];
				//cameraPos.z = camera_pos[2];

				shader.SetFloat1("specularStrength", specStrength);
				shader.SetInt1("shineIntensity", shineIntensity);
				shader.SetFloat1("ambientStrength", ambientStrength);
				shader.SetFloat1("brightness", brightness);
			}

			OnKeyPress(window, deltaTime);

			shader.SetFloat3("cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);

			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

			{
				glm::mat4 model = glm::mat4(1.0f);
				shader.SetFloat3("lightPos", lightPos.x, lightPos.y, lightPos.z); // Add overloaded function for vec3 param
				model = glm::translate(model, lightPos);
				lightVAO.Bind();
				lightShader.Use();
				lightShader.SetMat4x4("view", view);
				lightShader.SetMat4x4("model", model);
				GlCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
			}

			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, objectPos);
				vao.Bind();
				shader.Use();
				shader.SetMat4x4("view", view);
				shader.SetMat4x4("model", model);
				GlCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			}

			// Rendering
			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
