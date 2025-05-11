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
    copts = [
        "-g",
        #        "--strip=never",
        "-O0",
    ],  # 确保调试符号，禁用优化
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
