# extension.bzl
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@bazel_tools//tools/build_defs/repo:local.bzl", "new_local_repository")

def _my_extension_impl(mctx):
    debug = "debug/"
    if "win" in mctx.os.name:
        path = "D:/apps/vcpkg/installed/x64-windows"
        lib = "dll"
        comm = ""
    else:
        path = "/home/peng/apps/vcpkg/installed/x64-linux"
        lib = ""
        comm = "#"
        debug = ""

    print("fsfsfsf fsfs     {} {}".format(mctx.os.name, path))

    build_file = mctx.file("MODULE.bazel", """""")

    build_file_content = """
cc_library(
   name = "vcpkg",
COMM  srcs = glob(["DEBUG_PREbin/**/*.LIB_DLL" ]),  # windows 下是 .lib，Linux 下可以是 .a 或 .so
   hdrs = glob(["include/**/*.h"]),
   includes = ["include"],
#   data = glob(["bin/**/*.dll"]),
   linkopts = select({
                        # Windows 下
                     "@platforms//os:windows": [
                     "/LIBPATH:LIPATH_IMPL",


                     ],  # Linux 下
                     "@platforms//os:linux": [
                     "-LLIPATH_IMPL",

                     ],
                  }),
   visibility = ["//visibility:public"],
)
       """.replace("LIPATH_IMPL", "{}/DEBUG_PRElib".format(path)) \
        .replace("LIB_DLL", lib) \
        .replace("COMM", comm).replace("DEBUG_PRE", debug)

    new_local_repository(name = "vcpkg", build_file_content = build_file_content, path = path)

vcpkg_repo = module_extension(implementation = _my_extension_impl)
