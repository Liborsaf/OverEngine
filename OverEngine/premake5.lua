project "OverEngine"
	kind "StaticLib"

	language "C++"
	cppdialect "C++17"

	targetname "OverEngine"
	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pcheader.h"
	pchsource "src/pcheader.cpp"

	prebuildcommands
	{
		[[python ../utils/wren_to_c_string.py src/Wren/entity.wren.inc src/Wren/entity.wren
		python ../utils/wren_to_c_string.py src/Wren/input.wren.inc src/Wren/input.wren
		python ../utils/wren_to_c_string.py src/Wren/keycodes.wren.inc src/Wren/keycodes.wren
		python ../utils/wren_to_c_string.py src/Wren/lib.wren.inc src/Wren/lib.wren
		python ../utils/wren_to_c_string.py src/Wren/math.wren.inc src/Wren/math.wren
		python ../utils/wren_to_c_string.py src/Wren/script.wren.inc src/Wren/script.wren]]
	}

	files
	{
		-- Source Files
		"src/*.h",
		"src/*.cpp",
		"src/OverEngine/**.h",
		"src/OverEngine/**.cpp",

		-- stb
		"vendor/stb/stb_image.h",
		"vendor/stb/stb_image.cpp",

		"vendor/stb/stb_sprintf.h",
		"vendor/stb/stb_sprintf.cpp",

		-- tinyfiledialogs
		"vendor/tinyfiledialogs/tinyfiledialogs.h",
		"vendor/tinyfiledialogs/tinyfiledialogsBuild.cpp",

		-- Wrenpp
		"vendor/wrenpp/Wren++.h",
		"vendor/wrenpp/Wren++.cpp",

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
		"%{includeDir.spdlog}",
		"%{includeDir.GLFW}",
		"%{includeDir.glad}",
		"%{includeDir.imgui}",
		"%{includeDir.glm}",
		"%{includeDir.stb}",
		"%{includeDir.entt}",
		"%{includeDir.box2d}",
		"%{includeDir.json}",
		"%{includeDir.fmt}",
		"%{includeDir.yaml_cpp}",
		"%{includeDir.wren}",
	}

	defines
	{
		"GLFW_INCLUDE_NONE",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime (staticRuntime)

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
