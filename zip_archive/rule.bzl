def _impl_zip_archive(ctx):
    out_file = ctx.outputs.output
    args = ctx.actions.args()

    args.add(out_file)
    args.add_all(ctx.files.files)

    print("zip files is {} out is {}".format(ctx.files.files, out_file))

    ctx.actions.run(
        executable = "zip",
        arguments = [args],
        inputs = ctx.files.files,
        outputs = [out_file],
    )

    return DefaultInfo(
        files = depset([out_file]),
    )

zip_archive = rule(
    implementation = _impl_zip_archive,
    attrs = {
        "files": attr.label_list(allow_files = True),
        "output": attr.output(mandatory = True),
    },
)
