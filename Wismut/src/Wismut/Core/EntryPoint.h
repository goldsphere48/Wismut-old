#include <Wismut/Core/Application.h>
#include <Wismut/Core/Log.h>

int main()
{
	Wi::Log::Initialize();
	WI_CORE_INFO("Initialize application");
	Wi::Application* app = Wi::CreateApplication();
	app->Run();
	delete app;
}
