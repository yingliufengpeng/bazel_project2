load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library", "pybind_library_test")
load("@rules_python//python:packaging.bzl", "py_package", "py_wheel")

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
        "basic.pyi",
    ],
)

pybind_extension(
    name = "basic",
    srcs = [
        #        "basic.cpp",
        #        "basic.h",
        "pybind_python.cpp",
        ":_basic",
    ],
)

py_library(
    name = "basic_lib",
    srcs = [
        #        "basic.pyi",
        "basic_tools.py",
    ],
    data = [
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

#py_package(
#    name = "my_package",
#    #    distribution = "basic",  # 包名
#    packages = [],
#    #    python_tag = "py3",  # Python 版本
#    #    requires = ["requests==2.28.1"],  # 声明运行时依赖
#    #    version = "0.1.0",  # 版本号
#    deps = [":basic_lib"],  # 引用 py_library
#)
#platform = "linux_x86_64",
py_wheel(
    name = "my_package_wheel",
    abi = "py3",
    distribution = "basic",  # 包名
    platform = select({
        "@platforms//os:linux": "linux_x86_64",
        "@platforms//os:windows": "win_amd64",
        "//conditions:default": "any",
    }),
    python_tag = "py3",  # Python 版本
    requires = ["requests==2.28.1"],  # 声明运行时依赖
    version = "0.1.0",  # 版本号
    deps = [
        ":basic",
        ":basic_lib",
    ],  # 引用 py_library
)
