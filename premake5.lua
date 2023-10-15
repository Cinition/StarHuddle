cppdialect "C++20"
language "C++"
staticruntime "off"


defines {
    "_CRT_SECURE_NO_WARNINGS"
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


    project "ZStd"
        kind "StaticLib"
        location ( "build" )
        targetdir( "lib" )

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
            "dependencies/zstd/lib/common/",
        }


    project "StarHuddle"
        kind "WindowedApp"
        location ( "build" )
        targetdir( "bin" )

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
            "ZStd",
        }

        includedirs {
            "src/",
            -- nlohmann_json
            "dependencies/json/single_include/nlohmann",
            -- RayLib
            "dependencies/raylib/src",
            "dependencies/zstd/lib",
        }