project "Wismut"
	language "C++"
	cppdialect "C++20"
	kind "StaticLib"
	staticruntime "on"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "wipch.h"
	pchsource "src/wipch.cpp"

	files
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**.cpp",
		"vendor/stb_image/**.h",
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.stb_image}",
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
    {
        "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		"_CRT_SECURE_NO_WARNINGS"
    }

	filter "system:windows"
		systemversion "latest"
		defines 
		{ 
			"WI_PLATFORM_WIN",
			"GLFW_INCLUDE_NONE" 
		}

	filter "configurations:Debug"
		symbols "on"
		defines { "WI_DEBUG" }
		runtime "Debug"

	filter "configurations:Release"
		optimize "on"
		defines { "WI_RELEASE" }
		runtime "Release"
		