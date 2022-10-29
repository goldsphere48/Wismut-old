workspace "Wismut"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "vendor/glfw/include"
IncludeDirs["glad"] = "vendor/glad/include"

include "Wismut/vendor/glfw"
include "Wismut/vendor/glad"
include "Wismut"
include "Sandbox"