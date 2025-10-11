load("@rules_python//python:py_runtime.bzl", "py_runtime")
load("@rules_python//python/cc:py_cc_toolchain.bzl", "py_cc_toolchain")

# 可选：声明 py_cc_toolchain 目标，如果你希望自定义
# But rules_python 自己会创建一个 py_cc_toolchain，使你能访问 headers / libs via toolchain

cc_binary(
    name = "embed_py",
    srcs = ["main.cc"],
    #    copts = select({
    #        "@platforms//os:windows": [
    #            "-IC:/Users/peng/.conda/envs/py13/include",
    #        ],
    #        "@platforms//os:linux": ["-I/usr/include/python3.13"],
    #    }),
    #    linkopts = select({
    #        "@platforms//os:windows": [
    #            "/LIBPATH:C:/Users/peng/.conda/envs/py13/libs",
    #            "python313.lib",
    #        ],
    #        "@platforms//os:linux": ["-lpython3.13"],
    #    }),
    deps = [
        "@rules_python//python/cc:current_py_cc_headers",
        "@rules_python//python/cc:current_py_cc_libs",
    ],
)
