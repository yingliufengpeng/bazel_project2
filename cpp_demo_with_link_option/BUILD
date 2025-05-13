# 定义链接脚本文件
filegroup(
    name = "linker_script",
    srcs = ["linker_script.lds"],
)

exports_files(
    [
        "linker_script.lds",
    ],
)

# 定义二进制目标
cc_binary(
    name = "my_binary",
    srcs = ["main.c"],
    additional_linker_inputs = [":linker_script"],  # 确保链接脚本可用
    linkopts = select({
        "@platforms//os:linux": [
            "-T",
            "$(location :linker_script)",
        ],
        "//conditions:default": [],
    }),
    #    linkopts = [
    #        "-T",
    #        "$(location :linker_script)",  # 使用链接脚本
    #    ],
)
