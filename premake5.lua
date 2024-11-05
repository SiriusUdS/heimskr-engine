workspace "heimskr-engine"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "heimskr-engine"

project "heimskr-engine"
    kind "ConsoleApp"
    language "C++"
    targetdir "out/%{cfg.buildcfg}"

    includedirs {
        "src/gui",
        "src/logging"
    }

    files { "src/**.h", "src/**.cpp" }

    filter "system:windows"
        buildoptions {
            "/utf-8",
            "/wd4005",
            "/wd26498",
            "/wd26800"
        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"