set_languages("c++17")

add_requires("gtest")

add_requires("vcpkg::nlohmann-json")

target("c")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include")
    add_packages("vcpkg::nlohmann-json")

target("test_jsonstore")
    set_kind("binary")
    add_files("tests/jsonstore_test.cpp", "src/jsonstore.cpp")
    add_includedirs("include")
    add_packages("vcpkg::nlohmann-json")
    add_packages("gtest")
