load("@rules_python//python:py_runtime.bzl", "py_runtime")
load("@rules_python//python/cc:py_cc_toolchain.bzl", "py_cc_toolchain")

# 可选：声明 py_cc_toolchain 目标，如果你希望自定义
# But rules_python 自己会创建一个 py_cc_toolchain，使你能访问 headers / libs via toolchain

cc_binary(
    name = "embed_py",
    srcs = ["main.cc"],
    # 引用 rules_python 所配置的 python C API headers 和 libs
    deps = [
        "@rules_python//python/cc:current_py_cc_headers",
        "@rules_python//python/cc:current_py_cc_libs",
    ],
)
