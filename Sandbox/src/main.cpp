#include <Wismut.h>
#include <glfw/include/GLFW/glfw3.h>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "Wismut/Renderer/PerspectiveCameraController.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/VertexArray.h"

class MyLayer : public Wi::Layer
{
public:
	MyLayer()
		: Wi::Layer("Layer"), m_Time(0), m_ScaleX(1), m_ScaleY(1), m_ScaleZ(1)
	{
		float vertices[] = {
			-0.5f,  0.5f,  0.0f, 1, 0, 0,
			-0.5f, -0.5f,  0.0f, 0, 1, 0,
			 0.5f,  0.5f,  0.0f, 0, 0, 1,
			 0.5f, -0.5f,  0.0f, 1, 0, 1,
			-0.5f,  0.5f, -1.0f, 1, 1, 0,
			-0.5f, -0.5f, -1.0f, 0, 1, 1,
			 0.5f,  0.5f, -1.0f, 1, 1, 1,
			 0.5f, -0.5f, -1.0f, 1, 1, 0,
		};

		uint32_t indices[] = {
			0, 2, 3, 0, 3, 1,
			2, 6, 7, 2, 7, 3,
			6, 4, 5, 6, 5, 7,
			4, 0, 1, 4, 1, 5,
			0, 4, 6, 0, 6, 2,
			1, 5, 7, 1, 7, 3,
		};

		m_VertexArray = Wi::VertexArray::Create();

		auto vertexBuffer = Wi::VertexBuffer::Create(vertices, sizeof(vertices));
		auto indexBuffer = Wi::IndexBuffer::Create(indices, 36);

		auto layout = Wi::BufferLayout
		{
			{ Wi::ShaderDataType::Float3, "u_Position" },
			{ Wi::ShaderDataType::Float3, "u_Color" },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader = Wi::Shader::Create("assets/test.glsl");

		m_Camera = std::make_shared<Wi::OrthographicCamera>(-2.0f, 1.5f, 2.0f, -1.5f);
		m_CameraPers = std::make_shared<Wi::PerspectiveCameraController>(1600 / 900, 0.1f, 100.0f);
	}

	void OnEvent(Wi::Event& event) override
	{
		m_CameraPers->OnEvent(event);
	}

	void OnUpdate() override
	{
		glm::mat4 trans = glm::identity<glm::mat4>();
		trans = glm::rotate(trans, m_Time, glm::vec3(1, 1, 1));
		m_CameraPers->OnUpdate();
		Wi::Renderer::BeginScene(m_CameraPers->GetCamera());
		Wi::Renderer::Submit(m_VertexArray, m_Shader, trans);
		Wi::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Rotate");
		float vMin = -10;
		float vMax = 10;
		ImGui::SliderScalar("Rotation", ImGuiDataType_Float, &m_Time, &vMin, &vMax);
		ImGui::SliderScalar("Scale X", ImGuiDataType_Float, &m_ScaleX, &vMin, &vMax);
		ImGui::SliderScalar("Scale Y", ImGuiDataType_Float, &m_ScaleY, &vMin, &vMax);
		ImGui::SliderScalar("Scale Z", ImGuiDataType_Float, &m_ScaleZ, &vMin, &vMax);
		ImGui::SliderScalar("Pitch", ImGuiDataType_Float, &m_Pitch, &vMin, &vMax);
		ImGui::SliderScalar("Yaw", ImGuiDataType_Float, &m_Yaw, &vMin, &vMax);
		ImGui::End();
	}

private:
	std::shared_ptr<Wi::VertexArray> m_VertexArray;
	std::shared_ptr<Wi::Shader> m_Shader;
	std::shared_ptr<Wi::OrthographicCamera> m_Camera;
	std::shared_ptr<Wi::PerspectiveCameraController> m_CameraPers;
	glm::mat4 m_Transformation;
	float m_Time;
	float m_ScaleX;
	float m_ScaleY;
	float m_ScaleZ;
	float m_Pitch = 0;
	float m_Yaw = 0;
};

class MyApplication : public Wi::Application
{
public:
	MyApplication()
	{
		PushLayer(new MyLayer);
	}
};

Wi::Application* Wi::CreateApplication()
{
	return new MyApplication();
}
