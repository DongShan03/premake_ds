workspace "DataStructure"
    configurations { "Debug", "Release" }
    platforms { "Win64" }
    language "C++"
    location "build"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"

function add_project(name, kind_value)
    project(name)
        kind(kind_value)
        targetdir "build/%{cfg.buildcfg}"
        files { name .. "/headers/**.*", name .. "/**.*" }
end

local projects = {"Vector", "Stack", "List", "Queue", "Bitmap", "BinaryTree", "BST", 
            "AVL", "Splay", "RBTree", "HashTable", "Heap", "BTree"}

local kind_value = "ConsoleApp"

-- 循环调用 add_project 函数
for _, proj in ipairs(projects) do
    add_project(proj, kind_value)
end

project("Main")
    kind(kind_value)
    targetdir "build/%{cfg.buildcfg}"
    files { "main.cpp" }
