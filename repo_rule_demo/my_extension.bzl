load(":my_repo.bzl", "my_repo_rule")

def _my_extension_impl(ctx):
    for mod in ctx.modules:
        for tag in mod.tags.lib:
            my_repo_rule(
                name = "my_external_lib_{}".format(tag.version.replace(".", "_")),
                url = tag.url,
                sha256 = tag.sha256,
            )

lib_tag = tag_class(
    attrs = {
        "version": attr.string(mandatory = True),
        "url": attr.string(mandatory = True),
        "sha256": attr.string(),
    },
)

my_extension = module_extension(
    implementation = _my_extension_impl,
    tag_classes = {"lib": lib_tag},
)
