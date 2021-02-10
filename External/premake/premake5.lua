workspace "Tempest"
    architecture "x64"
    startproject "CustomGame"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
	{
		"MultiProcessorCompile"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Debug"
    location "Tempest/Core/Debug"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" ..outputdir.. "/%{prj.name}")
    objdir("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "../../Tempest/Core/Debug/**.h",
        "../../Tempest/Core/Debug/**.cpp",
    }

    includedirs
    {
        ".",
        "Tempest/",
        "Tempest/Core/",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            
        }

        postbuildcommands
        {

        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "configurations:Dist"
        optimize "On"

project "CustomGame"
    location "Tempest/MyGame"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" ..outputdir.. "/%{prj.name}")
    objdir("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "../../Tempest/MyGame/**.h",
        "../../Tempest/MyGame/**.cpp",
    }

    includedirs
    {
        ".",
        "Tempest/",
        "Tempest/Core/",
    }

    links
    {
        Debug
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            
        }

        postbuildcommands
        {

        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "configurations:Dist"
        optimize "On"