load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

filegroup(
    name = "basic",
    srcs = [
        "basic.cpp",
        "basic.h",
    ],
)

pybind_extension(
    name = "pybind_basic",
    srcs = [
        "pybind_python.cpp",
        ":basic",
    ],
)

py_library(
    name = "basic_lib",
    data = [":pybind_basic"],
    imports = ["."],
)

py_test(
    name = "python_basic_test",
    srcs = ["python_basic_test.py"],
    deps = [":basic_lib"],
)

cc_library(
    name = "basic_cc_library",
    srcs = [":basic"],
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
