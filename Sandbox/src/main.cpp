#include <Wismut.h>

#include "glm/gtc/quaternion.hpp"
#include "ImGui/imgui.h"
#include "Wismut/Events/KeyEvent.h"
#include "Wismut/Renderer/PerspectiveCameraController.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Renderer/VertexArray.h"

class MyLayer : public Wi::Layer
{
public:
	MyLayer()
		: Wi::Layer("Layer"), m_Time(0), m_ScaleX(1), m_ScaleY(1), m_ScaleZ(1)
	{
		m_CameraOrth = std::make_shared<Wi::OrthographicCameraController>(1600.0f / 900.0f);
		m_CameraPers = std::make_shared<Wi::PerspectiveCameraController>(1600.0f / 900.0f, 0.1f, 100.0f);
	}

	void OnEvent(Wi::Event& event) override
	{
		m_CameraOrth->OnEvent(event);
	}

	void OnUpdate(Wi::Timestep ts) override
	{
		m_CameraPers->OnUpdate(ts);
		Wi::Renderer::BeginScene(m_CameraPers->GetCamera());
		Wi::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Camera");
		ImGui::Text("Camera Position");
		glm::vec3 pos = m_CameraOrth->GetCamera().GetPosition();
		ImGui::Text("X: %f, Y: %f, Z: %f", pos.x, pos.y, pos.z);
		ImGui::Text("Camera Rotation");
		glm::vec3 rot = glm::eulerAngles(m_CameraOrth->GetCamera().GetOrientation());
		ImGui::Text("X: %f, Y: %f, Z: %f", rot.x, rot.y, rot.z);
		ImGui::End();
	}

private:
	std::shared_ptr<Wi::VertexArray> m_VertexArray;
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
