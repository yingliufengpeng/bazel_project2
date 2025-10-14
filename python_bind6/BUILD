# In a BUILD file, e.g. my_project/BUILD
load("@nanobind_bazel//:build_defs.bzl", "nanobind_extension")

#filegroup(
#    name = "_basic",
#    srcs = [
#        "basic.pyi",
#        "lib/demo_type.cc",
#        "lib/demo_type.h",
#    ],
#)

cc_library(
    name = "_basic_lib",
    srcs = [
        "lib/MyCoroutine.cpp",
        "lib/MyCoroutine.h",
        "lib/THPVariableMeta.cpp",
        "lib/THPVariableMeta.h",
        "lib/demo_type.cc",
        "lib/demo_type.h",
    ],
    copts = select({
        "@platforms//os:windows": ["/std:c++20"],  # MSVC
        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
        "//conditions:default": [],
    }),
    deps = [
        "@rules_python//python/cc:current_py_cc_headers",
        "@rules_python//python/cc:current_py_cc_libs",
    ],
)

cc_library(
    name = "tools_lib",
    srcs = ["tools.cpp"],
    hdrs = ["tools.h"],
    deps = [
        ":_basic_lib",
        "@nanobind_bazel//:nanobind",  # ✅ 关键：添加 nanobind 依赖
    ],
)

nanobind_extension(
    name = "basic",
    srcs = [
        "nanobind_python.cpp",
    ],
    copts = select({
        "@platforms//os:windows": ["/std:c++20"],  # MSVC
        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
        "//conditions:default": [],
    }),
    deps = [
        ":tools_lib",
        "@fmt",
    ],
)

filegroup(
    name = "basic_ext",
    srcs = [":basic"] + glob(["basic/*.pyi"]),  # 原来生成的 .pyd 目标
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
    deps = [
        ":basic_lib",
        "@pip_deps2//anyio",
    ],
)

py_test(
    name = "python_basic_test2",
    srcs = ["python_basic_test2.py"],
    deps = [
        ":basic_lib",
        "@pip_deps2//anyio",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    data = [
        ":basic_lib",
    ],
    deps = [
        ":tools_lib",
        "@rules_python//python/cc:current_py_cc_headers",
        "@rules_python//python/cc:current_py_cc_libs",
    ],
)
