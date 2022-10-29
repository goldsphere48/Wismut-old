#include <Wismut.h>

class MyLayer : public Wi::Layer
{
	void OnAttach() override
	{
		WI_INFO("Layer attached");
	}

	void OnDetach() override
	{
		WI_INFO("Layer attached");
	}
};

class MyApplication : public Wi::Application
{
public:
	MyApplication()
	{
		PushLayer(new MyLayer);
		PushOverlay(new Wi::ImGuiLayer);
	}
};

Wi::Application* Wi::CreateApplication()
{
	return new MyApplication();
}
