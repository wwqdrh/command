set_languages("c++17")

add_rules("mode.debug", "mode.release")

add_requires("gtest", "vcpkg::nlohmann-json", "vcpkg::cli11")

target("c")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include")
    add_packages("vcpkg::nlohmann-json", "vcpkg::cli11")

target("test_jsonstore")
    set_kind("binary")
    add_files("tests/jsonstore_test.cpp", "src/jsonstore.cpp")
    add_includedirs("include")
    add_packages("vcpkg::nlohmann-json")
    add_packages("gtest")
