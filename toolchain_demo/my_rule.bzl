load(":toolchain.bzl", "PyToolchainInfo")


def _my_py_binary_impl(ctx):
    py_toolchain = ctx.toolchains["//toolchain_demo:py_toolchain_type"]
    interpreter = py_toolchain.info.interpreter

    sh = ctx.actions.declare_file(ctx.label.name + ".sh")

    ctx.actions.write(
        output=sh,
        content="{} {}\n".format(interpreter, ctx.files.srcs[0].path),
        is_executable=True,
    )

    return [DefaultInfo(
        executable=sh,
        files=depset(ctx.files.srcs),
        runfiles=ctx.runfiles(files=ctx.files.srcs)
    )]


my_py_binary = rule(
    implementation = _my_py_binary_impl,
    attrs = {
        "srcs": attr.label_list(allow_files = [".py"]),
    },
    toolchains = ["//toolchain_demo:py_toolchain_type"],
    executable = True,
)
