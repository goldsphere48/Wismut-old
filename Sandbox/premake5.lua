project "Sandbox"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	staticruntime "on"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.h",
	}

	links
	{
		"Wismut"
	}

	includedirs
	{
		"%{wks.location}/Wismut/src",
		"%{wks.location}/Wismut/vendor/spdlog/include",
		"%{wks.location}/Wismut/vendor",
		"%{wks.location}/Wismut/%{IncludeDirs.glm}"
	}

	filter "system:windows"
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
		