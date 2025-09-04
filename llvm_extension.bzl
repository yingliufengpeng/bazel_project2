# extension.bzl
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@bazel_tools//tools/build_defs/repo:local.bzl", "local_repository")

def _my_extension_impl(mctx):
    debug = "debug/"
    if "win" in mctx.os.name:
        path = "D:/repo/llvm_repo/llvmorg-17.0.3"

    else:
        path = "/home/peng/src_repo/llvm_src/llvmorg-17.0.3"

    print("fsfsfsf fsfs     {} {}".format(mctx.os.name, path))

    local_repository(name = "llvm-project", path = path)

llvm = module_extension(implementation = _my_extension_impl)
