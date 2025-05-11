load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library", "pybind_library_test")

filegroup(
    name = "_basic",
    srcs = [
        "Dog.cpp",
        "Dog.h",
        "Pet.cpp",
        "Pet.h",
        "PolymorphhicPet.h",
        "basic.cpp",
        "basic.h",
    ],
)

pybind_extension(
    name = "basic",
    srcs = [
        "pybind_python.cpp",
        ":_basic",
    ],
)

py_library(
    name = "basic_lib",
    srcs = ["basic_tools.py"],
    data = [
        #        "basic_tools.py",
        ":basic",
    ],
    imports = ["."],
)

py_test(
    name = "python_basic_test",
    srcs = ["python_basic_test.py"],
    deps = [":basic_lib"],
)

cc_library(
    name = "basic_cc_library",
    srcs = [":_basic"],
    deps = [],
)

pybind_library(
    name = "pybind_basic_cc_library",
    srcs = [":_basic"],
    deps = [],
)

cc_test(
    name = "basic_test",
    #    main = 'basic_test.cpp',
    srcs = ["basic_test.cpp"],
    deps = [
        ":basic_cc_library",
        "@googletest//:gtest_main",
    ],
)

pybind_library_test(
    name = "pybind_basic_test",
    srcs = ["basic_test.cpp"],
    deps = [
        ":pybind_basic_cc_library",
        "@googletest//:gtest_main",
    ],
)

filegroup(
    name = "_Pet",
    srcs = [
        "Pet.cpp",
        "Pet.h",
    ],
)

cc_library(
    name = "Pet",
    srcs = [":_Pet"],
    deps = [],
)

cc_test(
    name = "PetTest",
    #    main = 'basic_test.cpp',
    srcs = ["PetTest.cpp"],
    deps = [
        ":Pet",
        "@googletest//:gtest_main",
    ],
)
