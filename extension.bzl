# extension.bzl
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@bazel_tools//tools/build_defs/repo:local.bzl", "new_local_repository")

def _my_extension_impl(mctx):
    if "win" in mctx.os.name:
        path = "D:/apps/vcpkg/installed/x64-windows"
    else:
        path = "/home/peng/apps/vcpkg/installed/x64-linux"

    print("fsfsfsf fsfs     {} {}".format(mctx.os.name, path))

    build_file = mctx.file("MODULE.bazel", """""")

    build_file_content = """
cc_library(
   name = "vcpkg",
   srcs = glob(["bin/**/*.dll" ]),  # windows 下是 .lib，Linux 下可以是 .a 或 .so
   hdrs = glob(["include/**/*.h"]),
   includes = ["include"],
#   data = glob(["bin/**/*.dll"]),
   linkopts = select({
                     "@platforms//os:windows": [
                     "/LIBPATH:XXXXX",


                     ],  # Windows 下
                     "@platforms//os:linux": [
                     "-LXXXXX",

                     ],          # Linux 下
                  }),
   visibility = ["//visibility:public"],
)
       """.replace("XXXXX", "{}/lib".format(path)).replace("YYYYY", path)

    new_local_repository(name = "vcpkg", build_file_content = build_file_content, path = path)

vcpkg_repo = module_extension(implementation = _my_extension_impl)
