load("@rules_python//python:defs.bzl", "py_test")
load("//toolchain_demo:my_rule.bzl", "my_py_binary")

py_library(
    name = "basic_lib",
    srcs = ["basic.py"],
    data = [
    ],
    imports = ["."],
)

py_test(
    name = "python_basic_test",
    srcs = ["python_basic_test.py"],
    deps = [":basic_lib"],
)



my_py_binary(
    name = "hello",
    srcs = ["hello.py"],
)
