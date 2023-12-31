language      "C++"
cppdialect    "C++20"
staticruntime "off"
warnings      "Extra"

defines {
    "_CRT_SECURE_NO_WARNINGS",
    "_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING",
    "WORKING_DIRECTORY=" .. "\"" .. os.getcwd() .. "\""
}

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


    project "Raylib"
        kind "StaticLib"
        location ( "build" )
        targetdir( "lib" )

        warnings "Off"

        files {
            "dependencies/raylib/src/rcore.c",
            "dependencies/raylib/src/utils.c",
            "dependencies/raylib/src/rmodels.c",
            "dependencies/raylib/src/rshapes.c",
            "dependencies/raylib/src/rtext.c",
            "dependencies/raylib/src/rtextures.c",
            "dependencies/raylib/src/rglfw.c",
        }

        defines {
            "GRAPHICS_API_OPENGL_33",
            "PLATFORM_DESKTOP",
        }

        includedirs {
            "dependencies/raylib/src/external/glfw/include",
            "dependencies/raylib/src/external/glfw/deps/mingw",
        }


    project "Zstd"
        kind "StaticLib"
        location ( "build" )
        targetdir( "lib" )

        warnings "Off"

        files {
            "dependencies/zstd/lib/zstd.h",
            "dependencies/zstd/lib/common/*.h",
            "dependencies/zstd/lib/common/*.c",
            "dependencies/zstd/lib/compress/*.h",
            "dependencies/zstd/lib/compress/*.c",
            "dependencies/zstd/lib/decompress/*.h",
            "dependencies/zstd/lib/decompress/*.c",
        }

        includedirs {
            "dependencies/zstd/lib/common",
            "dependencies/zstd/lib/compress",
            "dependencies/zstd/lib/decompress",
        }


    project "StarHuddle"
        kind "WindowedApp"
        location ( "build" )
        targetdir( "bin" )

        flags {
            "FatalWarnings",
        }

        files {
            "src/**.h",
            "src/**.cpp",
        }

        links {
            "Raylib",
            "kernel32",
            "opengl32",
            "gdi32",
            "winmm",
            "Zstd",
        }

        includedirs {
            "src/",
            -- nlohmann_json
            "dependencies/json/single_include/nlohmann",
            -- RayLib
            "dependencies/raylib/src",
            -- Zstd
            "dependencies/zstd/lib",
        }