# extensions.bzl

def _my_extension_impl(ctx):
    # 这个实现可以处理依赖项并生成仓库规则
    print("My extension is executing!")

    # 示例：为每个依赖项创建一个仓库
    for mod in ctx.modules:
        for dep in mod.tags.dep:
            # 这里只是一个示例，实际中你会调用实际的仓库规则
            print("Processing dependency:", dep.name, "version:", dep.version)

my_extension = module_extension(
    implementation = _my_extension_impl,
    tag_classes = {
        "dep": tag_class(attrs = {
            "name": attr.string(mandatory = True),
            "version": attr.string(default = "1.0.0"),
        }),
    },
)
