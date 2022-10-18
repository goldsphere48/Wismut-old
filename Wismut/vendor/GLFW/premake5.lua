project "GLFW"
	language "C"
	kind "StaticLib"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/glfw3.h",
		"include/glfw3native.h",
		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/mappings.h",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines 
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
		files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_joystick.h",
			"src/win32_monitor.c",
			"src/win32_platform.h",
			"src/win32_thread.c",
			"src/win32_time.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"