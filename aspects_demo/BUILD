load(":file_count.bzl", "file_count_rule")

cc_library(
    name = "lib",
    srcs = [
        "lib.cpp",
        "lib.h",
    ],
)

cc_binary(
    name = "app",
    srcs = [
        "main.cpp",
    ],
    deps = [":lib"],
)

file_count_rule(
    name = "file_count",
    extension = "cpp",
    deps = [":app"],
)
