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
		"src/**.h"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDirs.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines { "WI_PLATFORM_WIN" }
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Sandbox/"
		}

	filter "configurations:Debug"
		symbols "on"
		defines { "WI_DEBUG" }
		runtime "Debug"

	filter "configurations:Release"
		optimize "on"
		defines { "WI_RELEASE" }
		runtime "Release"
		