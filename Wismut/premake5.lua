project "Wismut"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "wipch.h"
	pchsource "src/wipch.cpp"

	files
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}",
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
        "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
    }

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines 
		{ 
			"WI_PLATFORM_WIN",
			"GLFW_INCLUDE_NONE" 
		}
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Sandbox/"
		}

	filter "configurations:Debug"
		symbols "on"
		defines 
		{ 
			"WI_DEBUG",
			"IMGUI_IMPL_OPENGL_DEBUG"
		}
		runtime "Debug"

	filter "configurations:Release"
		optimize "on"
		defines { "WI_RELEASE" }
		runtime "Release"
		