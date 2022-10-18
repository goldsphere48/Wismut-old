#include <Wismut.h>

class MyApplication : public Wi::Application
{
	
};

Wi::Application* Wi::CreateApplication()
{
	return new MyApplication();
}
