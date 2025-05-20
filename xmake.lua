add_rules("mode.debug", "mode.release")
set_languages("c++20")


package("juce")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "lib/JUCE"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
    on_test(function (package)
        assert(package:has_cfuncs("add", {includes = "foo.h"}))
    end)
package_end()

add_requires("juce")

target("juce_test")
    set_kind("binary")
    add_files("Source/*.cpp", "Source/*.ixx")
    add_packages("foo")
