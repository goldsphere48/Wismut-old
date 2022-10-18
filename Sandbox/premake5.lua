project "Sandbox"
	language "C++"
	cppdialect "C++17"
	kind "ConsoleApp"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.h"
	}

	links
	{
		"Wismut"
	}

	includedirs
	{
		"%{wks.location}/Wismut/src",
		"%{wks.location}/Wismut/vendor/spdlog/include"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		defines { "WI_PLATFORM_WIN" }

	filter "configurations:Debug"
		symbols "on"
		defines { "WI_DEBUG" }
		runtime "Debug"

	filter "configurations:Release"
		optimize "on"
		defines { "WI_RELEASE" }
		runtime "Release"
		