load(":example_info.bzl", "ExampleInfo", "make_exampleinfo")

def _my_rule_impl(ctx):
    info = make_exampleinfo(
        ["aaa"],
        ["bbb"],
    )

    return [
        DefaultInfo(),
        info,
    ]

my_rule = rule(
    implementation = _my_rule_impl,
)

def _my_rule_impl2(ctx):
    # 正常创建 ExampleInfo 实例
    lib = ExampleInfo(
        src_files = ["foo.c", "bar.c"],  # 合法：非空
        includes = ["/project/include"],  # 自定义头文件路径
    )
    print("LibraryInfo:")

#    info = ExampleInfo()

my_rule2 = rule(
    implementation = _my_rule_impl2,
)
