load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

#load("//zip_archive:rule.bzl", "zip_archive")
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//cpp_demo:link_rule.bzl", "link_cpp")
load("//cpp_demo:rule.bzl", "compile_cpp")

def appliction(name):
    compile_cpp(
        name = "{}".format(name),
        srcs = [
            "src/Animal.cpp",
            "src/main.cpp",
        ],
        hsrcs = ["src/Animal.h"],
    )

def link(name, deps):
    link_cpp(
        name = "{}".format(name),
        out = "main",
        objs = deps,
    )

def nativate_app(name):
    compile_name = "{}.compile".format(name)
    cc_binary(
        name = compile_name,
        srcs = [
            "src/Animal.cpp",
            "src/Animal.h",
            "src/main.cpp",
        ],
        deps = [],
    )
    pkg_tar(
        name = "{}".format(name),
        srcs = [
            compile_name,
            "READMD.md",
        ],
    )
