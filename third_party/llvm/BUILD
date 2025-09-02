load(":LLVM_MLIR_LIBS.bzl", "LIBS")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = ["/MDd"],  # Debug CRT
    linkopts = select({
        "@platforms//os:linux": [
            "-lgdal",
        ],
        "@platforms//os:windows": LIBS + [
            "ws2_32.lib",
            "msvcrtd.lib",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "@vcpkg",
    ],
)
