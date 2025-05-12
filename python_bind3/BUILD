load("@pip_deps2//:requirements.bzl", "all_data_requirements", "all_requirements", "all_whl_requirements", "requirement")
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


# 定义 config_setting 用于平台检测
config_setting(
    name = "is_windows",
    constraint_values = [
        "@platforms//os:windows",
    ],
)

config_setting(
    name = "is_linux",
    constraint_values = [
        "@platforms//os:linux",
    ],
)

config_setting(
    name = "is_macos",
    constraint_values = [
        "@platforms//os:macos",
    ],
)

pybind_extension(
    name = "basic",
    srcs = [
        "pybind_numpy.cpp",
        "pybind_numpy.h",
        "pybind_python.cpp",
        #        ":_basic",
    ],
    copts = select({
            ":is_windows": [

                "/O",                       # Windows MSVC 优化
            ],
            ":is_linux": [
                "-O0",                       # Linux GCC/Clang 优化

            ],
            ":is_macos": [
                "-O0",                       # macOS Clang 优化

            ],
            "//conditions:default": [],
        }),

#    copts = [
#        "-g",
#        #        "--strip=never",
#        "-O0",
#    ],  # 确保调试符号，禁用优化
)

py_library(
    name = "basic_lib",
    srcs = ["tools.py"],
    data = [
        ":basic",
    ],
    imports = ["."],
    deps = [
        "@pip_deps2//numpy",
        #        requirement("pandas"),
    ],
)

py_test(
    name = "python_basic_test",
    srcs = ["python_basic_test.py"],
    deps = [":basic_lib"],
)

#
#py_wheel(
#    name = "my_package_wheel",
#    abi = "py3",
#    distribution = "basic",  # 包名
#    platform = select({
#        "@platforms//os:linux": "linux_x86_64",
#        "@platforms//os:windows": "win_amd64",
#        "//conditions:default": "any",
#    }),
#    python_tag = "py3",  # Python 版本
#    requires = ["requests==2.28.1"],  # 声明运行时依赖
#    version = "0.1.0",  # 版本号
#    deps = [
#        ":basic",
#        ":basic_lib",
#    ],  # 引用 py_library
#)
