project "ImGui"
    language "C++"
    kind "StaticLib"

    targetdir("bin/" .. outputdir .. "%{prj.name}")
    objdir("obj/" .. outputdir .. "%{prj.name}")

    files
    {
        "imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",
        "imgui_tables.cpp"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
        cppdialect "C++17"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"