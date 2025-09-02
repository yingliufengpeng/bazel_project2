load(":LINUX_LLVM_MLIR_LIBS.bzl", "LINUX_LIBS")
load(":WIN_LLVM_MLIR_LIBS.bzl", "WIN_LIBS")

cc_binary(
    name = "main",
    srcs = glob([
        #        "*.cpp",
        "*.cc",
        "toy/*.h",
    ]),
    copts = select({
        "@platforms//os:windows": [
            "/MDd",  # debug mode
        ],
        "//conditions:default": [
            "-fno-rtti",
        ],
    }),
    linkopts = select({
        "@platforms//os:linux": LINUX_LIBS + [
            #            "-lMLIRIR",
            #            "-lMLIRSupport",
            #            "-lMLIRParser",
            #            "-lLLVMOption",
            #            "-lLLVMCore",
            #            "-lLLVMSupport",
            "-lLLVMDemangle",
            "-ltinfo",
            "-ldl",
            "-pthread",
            #            "-fno-rtti",
        ],
        "@platforms//os:windows": WIN_LIBS + [
            "ws2_32.lib",
            "msvcrtd.lib",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "@vcpkg",
    ],
)
