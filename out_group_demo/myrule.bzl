def _my_rule_impl(ctx):
    # 默认输出文件
    default_out = ctx.actions.declare_file(ctx.label.name + ".txt")
    ctx.actions.write(
        output = default_out,
        content = "Hello, World!",
    )

    # 预声明输出文件（通过 extra_out 属性）
    extra_out = ctx.outputs.extra_out
    print("extra_out is {}".format(extra_out))
    if extra_out:
        print("extra_out file is running...", extra_out.path)
        ctx.actions.write(
            output = extra_out,
            content = "Extra output",
        )

    # 调试输出文件（用于输出组）
    debug_out = ctx.actions.declare_file(ctx.label.name + ".debug")
    ctx.actions.write(
        output = debug_out,
        content = "Debug info",
    )

    # 返回提供者
    return [
        DefaultInfo(files = depset([default_out, extra_out])),  # 默认输出
        OutputGroupInfo(
            debug_files = depset([debug_out]),  # 调试文件组
            all_files = depset([default_out, extra_out, debug_out]),  # 所有文件组
        ),
    ]

my_rule = rule(
    implementation = _my_rule_impl,
    attrs = {
        "extra_out": attr.output(mandatory = False),  # 预声明输出属性
    },
)
