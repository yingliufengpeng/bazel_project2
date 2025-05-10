def _impl(ctx):
    outputs = []
    src_fs = ctx.files.srcs
    h_fs = ctx.files.hsrcs
    for f in src_fs:
        print("path is {}".format(f.path))
        fn = f.path.split("/")[-1][:-4]
        out = ctx.actions.declare_file(
            "{}.o".format(fn),  # xx.cpp -> xx.o
        )
        print("compiled out {} ----> {}".format(f, out))
        print("headers is {}".format(ctx.files.hsrcs))

        inputs = [f]
        inputs.extend(ctx.files.hsrcs)
        args = ctx.actions.args()
        args.add(f)
        args.add("-o")
        args.add(out)
        args.add("-c")
        print("xxxxxxxxxxxxx {}".format(args))
        ctx.actions.run(
            executable = "/usr/bin/g++",
            arguments = [args],
            inputs = inputs,
            outputs = [out],
        )

        outputs.append(out)

    return DefaultInfo(
        files = depset(outputs),
    )

compile_cpp = rule(
    implementation = _impl,
    attrs = {
        "srcs": attr.label_list(
            allow_files = True,
            doc = "src files",
        ),
        "hsrcs": attr.label_list(
            allow_files = True,
            doc = "hsrc files",
        ),
    },
)
