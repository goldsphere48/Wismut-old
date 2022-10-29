project "glad"
    language "C"
    kind "StaticLib"

    targetdir("bin/" .. outputdir .. "%{prj.name}")
    objdir("obj/" .. outputdir .. "%{prj.name}")

    files 
    {
        "include/glad/**.h",
        "include/KHR/**.h",
        "src/**.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"