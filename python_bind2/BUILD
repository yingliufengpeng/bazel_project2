load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library", "pybind_library_test")
load("@rules_python//python:defs.bzl", "py_test")
load("@rules_python//python:packaging.bzl", "py_package", "py_wheel")

filegroup(
    name = "_basic",
    srcs = [
        "basic.pyi",
        #        "tools.py",
    ],
)

pybind_extension(
    name = "basic",
    srcs = [
        "pybind_python.cpp",
        #        ":_basic",
    ],
)

py_library(
    name = "basic_lib",
    srcs = ["tools.py"],
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

# 打包所有依赖
py_package(
    name = "basic_pkg",
#    packages = ["src"],
    deps = [":basic_lib"],
)

# 生成 Python wheel
py_wheel(
    name = "wheel",
    author = "YingLiuFengPeng",
    distribution = "basic",
    license = "Apache 2.0",
    python_requires = ">=3.9.0",
    python_tag = "py3",
    version = "0.0.1",
    #    abi = "cp39",
    #    platform = select({
    #        "@bazel_tools//src/conditions:windows": "win_amd64",
    #        "//conditions:default": "any",
    #    }),
    deps = [":basic_pkg"],
)
