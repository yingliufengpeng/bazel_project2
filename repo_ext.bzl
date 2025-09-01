# File: hello.bzl

def _hello_repo_impl(ctx):
    # Create files for the xxxxxx_hello_world repository
    ctx.file("BUILD.bazel", """
cc_library(
    name = "foo",
    hdrs = ["foo.h"],
    srcs = ["foo.cc"],
    visibility = ["//visibility:public"],
)
""")
    ctx.file("foo.h", "int foo();")
    ctx.file("hello.txt", "Hello, World")
    ctx.file("foo.cc", "int foo() { return 42; }")

hello_repo = repository_rule(
    implementation = _hello_repo_impl,
)

def _ext_impl(mctx):
    for module in mctx.modules:
        for door_obj in module.tags.door:
            pass

        for table_obj in module.tags.table:
            pass

        for add_hello_obj in module.tags.add_hello:
            greeting = add_hello_obj.greeting
            print("name {} version {} tag {} is_root {}".format(module.name, module.version, greeting, module.is_root))

    # Note: We don't create files here anymore since they're handled by the repository rule
    return None

hello_ext = module_extension(
    implementation = _ext_impl,
    tag_classes = {
        "door": tag_class(attrs = {}),
        "table": tag_class(attrs = {}),
        "add_hello": tag_class(
            attrs = {"greeting": attr.string(default = "Hello")},
        ),
    },
)
