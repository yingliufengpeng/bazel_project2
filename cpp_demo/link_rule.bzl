def _impl(ctx):
    obj_fs = ctx.files.objs
    out = ctx.outputs.out

    args = ctx.actions.args()

    args.add_all(obj_fs)

    args.add("-o")
    args.add(out)

    args.add("-B")
    args.add("/usr/bin")

    ctx.actions.run(
        executable = "/usr/bin/g++",
        arguments = [args],
        inputs = obj_fs,
        outputs = [out],
    )

    return DefaultInfo(
        files = depset([out]),
        executable = out,
    )

link_cpp = rule(
    implementation = _impl,
    attrs = {
        "objs": attr.label_list(
            allow_files = True,
            doc = "src files",
        ),
        "out": attr.output(),
    },
    executable = True,
)
