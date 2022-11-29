workspace "Wismut"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "vendor/GLFW/include"
IncludeDirs["glad"] = "vendor/glad/include"
IncludeDirs["ImGui"] = "vendor/ImGui"
IncludeDirs["glm"] = "vendor/glm"
IncludeDirs["stb_image"] = "vendor/stb_image"

include "Wismut/vendor/glfw"
include "Wismut/vendor/glad"
include "Wismut/vendor/ImGui"
include "Wismut"
include "Sandbox"