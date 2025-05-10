load("//cpp_demo:application.bzl", "appliction", "link", "nativate_app")
load("//cpp_demo:link_rule.bzl", "link_cpp")
load("//cpp_demo:rule.bzl", "compile_cpp")
load("//zip_archive:rule.bzl", "zip_archive")

package(
    #    default_visibility = ["//cpp_demo_test:__pkg__"],
    default_visibility = ["//cpp_demo_test:mytest_group"],
    #    default_visibility = ["//visibility:public"],
)

link(
    "link2",
    [":c2"],
)

compile_cpp(
    name = "c1",
    srcs = [
        "src/Animal.cpp",
        "src/main.cpp",
    ],
    hsrcs = ["src/Animal.h"],
)

link_cpp(
    name = "link1",
    out = "main1",
    objs = [":c1"],
)

zip_archive(
    name = "zip_cpp1",
    files = [
        "READMD.md",
        ":link1",
    ],
    output = "cpp.zip",
)

nativate_app("e2")

cc_binary(
    name = "e1",
    srcs = [
        "src/Animal.cpp",
        "src/Animal.h",
        "src/main.cpp",
    ],
    visibility = [
        #        "//cpp_demo_test:__pkg__",  # 对 cpp_demo_test 包可见
        # 或者更开放的可见性：
        #        "//visibility:public",  # 对所有包可见
    ],
    deps = [],
)

cc_library(
    name = "lib1",
    srcs = [
        "src/Animal.cpp",
        "src/Animal.h",
        "src/main.cpp",
    ],
    visibility = [
        #        "//cpp_demo_test:__pkg__",  # 对 cpp_demo_test 包可见
        # 或者更开放的可见性：
        "//visibility:public",  # 对所有包可见
    ],
    deps = [],
)

zip_archive(
    name = "zip_cpp2",
    files = [
        "READMD.md",
        ":e1",
    ],
    output = "cpp2.zip",
)
