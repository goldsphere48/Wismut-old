#include "wipch.h"
#include "Wismut/Utils/Time.h"

#include <GLFW/glfw3.h>

namespace Wi
{
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}
