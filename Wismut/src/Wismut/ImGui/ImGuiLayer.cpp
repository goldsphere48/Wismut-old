#include "wipch.h"
#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "glad/glad.h"
#include "Wismut/Core/Application.h"
#include "Wismut/Platform/GLFW/imgui_impl_glfw.h"
#include "Wismut/Platform/OpenGL/ImGuiOpenGLRenderer.h"

Wi::ImGuiLayer::ImGuiLayer()
	: Layer("ImGui"), m_Time(0)
{
}

Wi::ImGuiLayer::~ImGuiLayer()
= default;

void Wi::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Wi::ImGuiLayer::OnDetach()
{
	
}

void Wi::ImGuiLayer::OnUpdate()
{
	float time = static_cast<float>(glfwGetTime());
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
	m_Time = time;

	Application& app = Application::Get();
	int w = app.GetWindow().GetWidth();
	int h = app.GetWindow().GetHeight();
	io.DisplaySize = ImVec2(w, h);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Wi::ImGuiLayer::OnEvent(const Event& event)
{
	
}
