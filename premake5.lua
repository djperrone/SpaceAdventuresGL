workspace "SpaceAdventuresGL"
	architecture "x64"
	startproject "SpaceAdventuresGL"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "SpaceAdventuresGL/vendor/GLFW/include"
IncludeDir["Glad"] = "SpaceAdventuresGL/vendor/Glad/include"
IncludeDir["ImGui"] = "SpaceAdventuresGL/vendor/imgui"
IncludeDir["stb_image"] = "SpaceAdventuresGL/vendor/stb_image"
IncludeDir["glm"] = "SpaceAdventuresGL/vendor/glm"

include "SpaceAdventuresGL/vendor/GLFW"
include "SpaceAdventuresGL/vendor/Glad"

project "SpaceAdventuresGL"
	location "SpaceAdventuresGL"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	

	pchheader "sapch.h"
	pchsource "SpaceAdventuresGL/src/sapch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"	
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/localimgui/imgui/*.h",
		"%{prj.name}/vendor/localimgui/imgui/*.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",		
		"%{prj.name}/vendor/spdlog/include",				
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",	
		"%{IncludeDir.stb_image}",	
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",		
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{			
			"GLFW_INCLUDE_NONE"		
		}

	filter "configurations:Debug"			
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
