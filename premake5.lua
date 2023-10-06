cppdialect "C++20"
language "C++"
staticruntime "off"

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"
    defines { "DEBUG" }

filter "configurations:Release"
    runtime "Release"
    optimize "speed"
    symbols "off"
    defines { "RELEASE" }

workspace "StarHuddle"
    architecture "x86_64"
    configurations { "Debug","Release" }
    startproject "StarHuddle"

    project "StarHuddle"
        kind "WindowedApp"
        location ( "bin/starhuddle" )
        targetdir( "build/starhuddle/%{cfg.buildcfg}" )
        
        files {
            "src/**.h",
            "src/**.cpp",
            -- RayLib
            "dependencies/raylib/include/**.h",
        }

        libdirs {
            -- RayLib
            "dependencies/raylib/lib",
        }

        links {
            -- RayLib
            "raylib",
            "winmm",
            "kernel32",
            "opengl32",
            "gdi32",
        }

        includedirs {
            -- RayLib
            "dependencies/raylib/include",
        }
