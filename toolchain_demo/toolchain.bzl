
PyToolchainInfo = provider(fields = ["interpreter", "version"])

def _py_toolchain_impl(ctx):
    return [
        platform_common.ToolchainInfo(
                info = PyToolchainInfo(
                    interpreter = ctx.attr.interpreter,
                    version = ctx.attr.version,
                )
            )
    ]
#    return [PyToolchainInfo(interpreter_path = ctx.attr.interpreter_path)]

py_toolchain_impl = rule(
    implementation = _py_toolchain_impl,
    attrs = {
        "interpreter": attr.string(),
        "version": attr.string(),
    },
)
