load("@rules_python//python:py_runtime.bzl", "py_runtime")
load("@rules_python//python/cc:py_cc_toolchain.bzl", "py_cc_toolchain")

# 可选：声明 py_cc_toolchain 目标，如果你希望自定义
# But rules_python 自己会创建一个 py_cc_toolchain，使你能访问 headers / libs via toolchain

# 构建C扩展的共享库
cc_library(
    name = "peng_demo.so",  # 输出文件名为 my_extension.so
    srcs = [
        "lib/demo_type.cc",
        "lib/demo_type.h",
    ],
    copts = select({
        "@platforms//os:windows": ["/std:c++20"],  # MSVC
        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
        "//conditions:default": [],
    }),
    data = [
        "peng_demo.pyi",
    ],
    deps = [
        "@rules_python//python/cc:current_py_cc_headers",
        "@rules_python//python/cc:current_py_cc_libs",
    ],
)

# 使用 py_library 将 C 扩展包装成 Python 模块
py_library(
    name = "my_module",
    srcs = [],
    # 将编译好的 .so 文件作为数据依赖
    data = [
        ":peng_demo.so",
    ],
    imports = ["."],  # 允许从当前目录导入
    visibility = ["//visibility:public"],
)

# 用于测试的 Python 脚本
py_test(
    name = "my_module_test",
    srcs = ["my_module_test.py"],
    deps = [
        ":my_module",
    ],
)

#cc_library(
#    name = "embed_lib",
#    srcs = glob([
#        "lib/*.cc",
#        "lib/*.h",
#    ]),
#    copts = select({
#        "@platforms//os:windows": ["/std:c++20"],  # MSVC
#        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
#        "//conditions:default": [],
#    }),
#    deps = [
#        "@rules_python//python/cc:current_py_cc_headers",
#        "@rules_python//python/cc:current_py_cc_libs",
#    ],
#)
#
#cc_binary(
#    name = "embed_py",
#    srcs = [
#        "main.cc",
#    ],
#    #    copts = select({
#    #        "@platforms//os:windows": ["/std:c++20"],  # MSVC
#    #        "@platforms//os:linux": ["-std=c++20"],  # GCC/Clang
#    #        "//conditions:default": [],
#    #    }),
#    deps = [
#        ":embed_lib",
#    ],
#)
