def _my_repo_impl(ctx):
    ctx.file("BUILD.bazel", """
    cc_library(
        name = "foo",
        hdrs = ["foo.h"],
        srcs = ["foo.cc"],
        visibility = ["//visibility:public"],
    )
    """)
    ctx.file("foo.h", "int foo();")
    ctx.file("foo.cc", "int foo() { return 42; }")

my_repo = repository_rule(implementation = _my_repo_impl)

def _ext_impl(mctx):
    # 在 bzlmod 里注册一个外部仓库 @hello_world
    #    print(dir(mctx))  # Prints all attributes and methods of mctx

    #    print("modules is {}  os {} path {}".format(mctx.modules, mctx.os, mctx.path))
    for module in mctx.modules:
        for door_obj in module.tags.door:
            pass

        #            print("door_obj is {} name is {}".format(door_obj, door_obj))

        for table_obj in module.tags.table:
            pass

        #            print("table_obj is {}".format(table_obj))

        for add_hello_obj in module.tags.add_hello:
            greeting = add_hello_obj.greeting
            #            print("add_hello_obj is {} greeting is {}".format(add_hello_obj, add_hello_obj.greeting))

            print("name {} version {} tag {} is_root {}".format(module.name, module.version, greeting, module.is_root))

    mctx.file("BUILD.bazel", """
    cc_library(
        name = "foo",
        hdrs = ["foo.h"],
        srcs = ["foo.cc"],
        visibility = ["//visibility:public"],
    )
    """)
    mctx.file("foo.h", "int foo();")
    mctx.file("foo.cc", "int foo() { return 42; }")

    return None

#    mctx.use_repo_rule(my_repo, name = "xxxxxx_hello_world")

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
