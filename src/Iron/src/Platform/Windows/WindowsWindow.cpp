#include <glad/glad.h>
#include "Platform/Windows/WindowsWindow.hpp"
#include "Log.hpp"

namespace Iron {
	static bool s_glfwIsInitialized = false;

	Window* Window::Create(const WindowProps& prop) {
		return new WindowsWindow(prop);
	}

	WindowsWindow::WindowsWindow(const WindowProps& prop) { Init(prop); }

	WindowsWindow::~WindowsWindow() { Close(); }

	void WindowsWindow::Init(const WindowProps& prop) {
		m_data.Title = prop.Title;
		m_data.Width = prop.Width;
		m_data.Height = prop.Height;

		if (!s_glfwIsInitialized) {
			int glfwState = glfwInit();
			IRON_CORE_ASSERT(glfwState, "Failed to initialize glfw");
			s_glfwIsInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow((int)m_data.Width, (int)m_data.Height,
			m_data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSwapInterval(1);

		int gladState = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IRON_CORE_ASSERT(gladState, "failed to initialize glad");

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glfwSetErrorCallback([](int error, const char* desc) {
			IRON_CORE_ERROR("[GLFW ERROR]({0}): {1}", error, desc);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			glfwDestroyWindow(window);
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			glViewport(0, 0, width, height);
			WindowResizeEvent* e = new WindowResizeEvent(width, height);
			data.Events.push_back(e);
			data.InternalEventCallback(*e);
			data.EventCallback(*e);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent* e = new MouseMoveEvent(xpos, ypos);
			data.Events.push_back(e);
			data.InternalEventCallback(*e);
			data.EventCallback(*e);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mod) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent* e = new MouseButtonPressedEvent(button);
				data.Events.push_back(e);
				data.InternalEventCallback(*e);
				data.EventCallback(*e);
			} break;
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent* e = new MouseButtonReleasedEvent(button);
				data.Events.push_back(e);
				data.InternalEventCallback(*e);
				data.EventCallback(*e);
			} break;
			}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent* e = new MouseScrollEvent(xoffset, yoffset);
			data.Events.push_back(e);
			data.InternalEventCallback(*e);
			data.EventCallback(*e);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					if (mods != 0) {
						KeyCombinationEvent* e = new KeyCombinationEvent(key, mods);
						data.Events.push_back(e);
						data.InternalEventCallback(*e);
						data.EventCallback(*e);
					}

					else {
						KeyPressEvent* e = new KeyPressEvent(key, false);
						data.Events.push_back(e);
						data.InternalEventCallback(*e);
						data.EventCallback(*e);
					}
				} break;

				case GLFW_RELEASE: {
					KeyReleaseEvent* e = new KeyReleaseEvent(key);
					data.Events.push_back(e);
					data.InternalEventCallback(*e);
					data.EventCallback(*e);
				} break;

				case GLFW_REPEAT: {
					if (mods != 0) {
						KeyCombinationEvent* e = new KeyCombinationEvent(key, mods);
						data.Events.push_back(e);
						data.InternalEventCallback(*e);
						data.EventCallback(*e);
					}

					else {
						KeyPressEvent* e = new KeyPressEvent(key, true);
						data.Events.push_back(e);
						data.InternalEventCallback(*e);
						data.EventCallback(*e);
					}
				} break;
			}
		});
	}

	void WindowsWindow::Close() { glfwTerminate(); }

	void WindowsWindow::OnUpdate() {
		for (auto* e : m_data.Events)
			delete e;
		m_data.Events.clear();
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool val) {
		if (val)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = true;
	}
} // namespace Iron
