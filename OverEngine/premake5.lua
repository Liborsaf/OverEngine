project "OverEngine"
	if (DynamicLink) then
		kind "SharedLib"
	else
		kind "StaticLib"
	end

	language "C++"
	cppdialect "C++17"

	targetname "OverEngine"
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pcheader.h"
	pchsource "src/pcheader.cpp"

	files
	{
		-- Source Files
		"src/*.h",
		"src/*.cpp",
		"src/OverEngine/**.h",
		"src/OverEngine/**.cpp",

		-- stb_image
		"vendor/stb_image/stb_image.h",
		"vendor/stb_image/stb_image.cpp",

		-- stb_rectpack
		"vendor/stb_rectpack/stb_rectpack.h",
		"vendor/stb_rectpack/stb_rectpack.cpp",

		-- tinyfiledialogs
		"vendor/tinyfiledialogs/tinyfiledialogs.h",
		"vendor/tinyfiledialogs/tinyfiledialogsBuild.cpp",

		-- Resources
		"res/**.h",

		-- RendererAPI Files
		"src/Platform/OpenGL/**.h",
		"src/Platform/OpenGL/**.cpp",
	 }

	includedirs
	{
		"src",
		"res",
		"vendor",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.GLFW}",
		"../%{IncludeDir.Glad}",
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.glm}",
		"../%{IncludeDir.lua}",
		"../%{IncludeDir.stb_image}",
		"../%{IncludeDir.stb_rectpack}",
		"../%{IncludeDir.entt}",
		"../%{IncludeDir.Box2D}",
		"../%{IncludeDir.json}",
	}

	if (DynamicLink) then
		links (LinkLibs)
	end

	if (IncludeTinyFileDialogs) then
		includedirs "../%{IncludeDir.TFD}"
		if (DynamicLink) then
			links "TinyFileDialogs"
		end
	end

	defines
	{
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS"
	}

	if (DynamicLink) then
		defines
		{
			"OE_PROJECT_BUILD_SHARED",
			"OE_BUILD_SHARED",
		}
	else
		defines "OE_BUILD_STATIC"
	end

	filter "system:windows"
		systemversion "latest"
		staticruntime (StaticRuntime)

		if (DynamicLink) then
			postbuildcommands ("{COPY} %{cfg.buildtarget.relpath} .../bin/" .. outputdir .. "/Sandbox")
			if (IncludeEditor) then
				postbuildcommands ("{COPY} %{cfg.buildtarget.relpath} .../bin/" .. outputdir .. "/OverEditor")
			end
		end

		files
		{
			-- Platform Files
			"src/Platform/Windows/**.h",
			"src/Platform/Windows/**.cpp"
	 	}

	filter "system:linux"
		pic "on"
		systemversion "latest"
		staticruntime "on"

		files
		{
			-- Platform Files
			"src/Platform/Linux/**.h",
			"src/Platform/Linux/**.cpp"
	 	}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:DebugOptimized"
		defines "OE_DEBUG"
		runtime "Debug"
		symbols "on"
		optimize "on"

	filter "configurations:Release"
		defines "OE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OE_DIST"
		runtime "Release"
		optimize "on"
