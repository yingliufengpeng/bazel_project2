# In a BUILD file, e.g. my_project/BUILD
load("@nanobind_bazel//:build_defs.bzl", "nanobind_extension")

filegroup(
    name = "_basic",
    srcs = [
        "basic.pyi",
        "lib/demo_type.cc",
        "lib/demo_type.h",
    ],
)

nanobind_extension(
    name = "basic",
    srcs = [
        "nanobind_python.cpp",
        ":_basic",
    ],
    copts = select({
        "@platforms//os:windows": ["/std:c++20"],  # MSVC
        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
        "//conditions:default": [],
    }),
    deps = [
        "@fmt",
    ],
)

filegroup(
    name = "basic_ext",
    srcs = [":basic"],  # 原来生成的 .pyd 目标
    visibility = ["//visibility:public"],
)

py_library(
    name = "basic_lib",
    srcs = [
        "basic_tools.py",
    ],
    data = [
        ":basic_ext",
    ],
    imports = ["."],
)

py_test(
    name = "python_basic_test",
    srcs = ["python_basic_test.py"],
    deps = [":basic_lib"],
)
