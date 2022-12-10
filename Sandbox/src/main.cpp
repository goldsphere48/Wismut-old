#include <Wismut.h>
#include <glfw/include/GLFW/glfw3.h>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "ImGui/imgui.h"
#include "Wismut/Events/KeyEvent.h"
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
			-0.5f,  0.5f,  0.5f, 0, 1,
			-0.5f, -0.5f,  0.5f, 0, 0,
			 0.5f,  0.5f,  0.5f, 1, 1,
			 0.5f, -0.5f,  0.5f, 1, 0,
			-0.5f,  0.5f, -0.5f, 0, 1,
			-0.5f, -0.5f, -0.5f, 0, 1,
			 0.5f,  0.5f, -0.5f, 1, 1,
			 0.5f, -0.5f, -0.5f, 0, 0,
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
			{ Wi::ShaderDataType::Float2, "u_TexCoords" },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader = Wi::Shader::Create("assets/test.glsl");
		m_TextureShader = Wi::Shader::Create("assets/texture.glsl");
		m_Texture = Wi::Texture2D::Create("assets/wow.png");

		m_Texture->Bind();
		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_TextCoords", 0);

		m_CameraOrth = std::make_shared<Wi::OrthographicCameraController>(1600.0f / 900.0f);
		m_CameraPers = std::make_shared<Wi::PerspectiveCameraController>(1600.0f / 900.0f, 0.1f, 100.0f);
	}

	void OnEvent(Wi::Event& event) override
	{
		if (m_IsPerspectiveCamera)
			m_CameraPers->OnEvent(event);
		else
			m_CameraOrth->OnEvent(event);

		Wi::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Wi::KeyPressedEvent>(WI_BIND_EVENT_FN(MyLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Wi::KeyPressedEvent& event)
	{
		if (event.GetKey() == Wi::Key::Tab)
		{
			m_IsPerspectiveCamera = !m_IsPerspectiveCamera;
			return true;
		}

		return false;
	}

	void OnUpdate(Wi::Timestep ts) override
	{
		glm::mat4 trans = glm::identity<glm::mat4>();
		trans = glm::translate(trans, glm::vec3(0, 0, -1.0f));

		if (m_IsPerspectiveCamera) 
		{
			m_CameraPers->OnUpdate(ts);
			Wi::Renderer::BeginScene(m_CameraPers->GetCamera());
		}
		else
		{
			m_CameraOrth->OnUpdate(ts);
			Wi::Renderer::BeginScene(m_CameraOrth->GetCamera());
		}
		Wi::Renderer::Submit(m_VertexArray, m_TextureShader, trans);
		Wi::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Camera");
		ImGui::Text("Camera Position");
		glm::vec3 pos = m_CameraPers->GetCamera().GetPosition();
		ImGui::Text("X: %f, Y: %f, Z: %f", pos.x, pos.y, pos.z);
		ImGui::Text("Camera Rotation");
		glm::vec3 rot = glm::eulerAngles(m_CameraPers->GetCamera().GetOrientation());
		ImGui::Text("X: %f, Y: %f, Z: %f", rot.x, rot.y, rot.z);
		ImGui::End();
	}

private:
	std::shared_ptr<Wi::VertexArray> m_VertexArray;
	std::shared_ptr<Wi::Shader> m_Shader;
	std::shared_ptr<Wi::Shader> m_TextureShader;
	std::shared_ptr<Wi::OrthographicCameraController> m_CameraOrth;
	std::shared_ptr<Wi::PerspectiveCameraController> m_CameraPers;
	std::shared_ptr<Wi::Texture2D> m_Texture;
	glm::mat4 m_Transformation;
	float m_Time;
	float m_ScaleX;
	float m_ScaleY;
	float m_ScaleZ;
	float m_Pitch = 0;
	float m_Yaw = 0;
	bool m_IsPerspectiveCamera = true;
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
