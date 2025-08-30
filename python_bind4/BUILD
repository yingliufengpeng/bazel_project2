# In a BUILD file, e.g. my_project/BUILD
load("@nanobind_bazel//:build_defs.bzl", "nanobind_extension")

#load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library", "pybind_library_test")
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

nanobind_extension(
    name = "basic",
    srcs = [
        #        "basic.cpp",
        #        "basic.h",
        "nanobind_python.cpp",
        ":_basic",
    ],
    deps = [
        "@fmt",
    ],
    #    copts = ["-std=c++20"],  # 这里指定了 C++17 标准
)

filegroup(
    name = "basic_ext",
    srcs = [":basic"],  # 原来生成的 .pyd 目标
    visibility = ["//visibility:public"],
)

py_library(
    name = "basic_lib",
    srcs = [
        #        "basic.pyi",
        "basic_tools.py",
    ],
    data = [
        ":basic_ext",
        #        ":_basic.pyd",
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

cc_binary(
    name = "hello_world",
    srcs = ["hello_absl.cc"],
    deps = [
        "@abseil-cpp//absl/strings:str_format",
    ],
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
    #    abi = "py3",
    distribution = "python_bind",  # 包名
    platform = select({
        "@platforms//os:linux": "linux_x86_64",
        "@platforms//os:windows": "win_amd64",
        "//conditions:default": "any",
    }),
    python_tag = "py3",  # Python 版本
    requires = ["requests>=2.31.0"],  # 声明运行时依赖
    version = "0.1.0",  # 版本号
    deps = [
        ":basic_ext",
        ":basic_lib",
    ],  # 引用 py_library
)
