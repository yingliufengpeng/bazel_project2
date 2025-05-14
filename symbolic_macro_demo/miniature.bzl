# Implementation function
def _miniature_impl(name, visibility, src, size, **kwargs):
    print(" ----> miniature  visibility is {} ".format(visibility))

    #    o_cmd = kwargs["cmd"]
    #    print("xxxxxxx o_cmd is {}".format(o_cmd))
    cmd = kwargs.pop("cmd", None) or "convert $< -resize " + size + " $@"

    print("xxxxxxx cmd is {}".format(cmd))
    native.genrule(
        name = name,
        visibility = visibility,
        srcs = [src],
        outs = [name + "_small_" + src.name],
        cmd = cmd,
        **kwargs
    )

# Macro declaration
miniature = macro(
    doc = """Create a miniature of the src image.

    The generated file name will be prefixed with `name + "_small_"`.
    """,
    implementation = _miniature_impl,
    # Inherit most of genrule's attributes (such as tags and testonly)
    inherit_attrs = native.genrule,
    attrs = {
        "src": attr.label(
            doc = "Image file",
            allow_single_file = True,
            # Non-configurable because our genrule's output filename is
            # suffixed with src's name. (We want to suffix the output file with
            # srcs's name because some tools that operate on image files expect
            # the files to have the right file extension.)
            configurable = False,
        ),
        "size": attr.string(
            doc = "Output size in WxH format",
            default = "100x100",
        ),
        # Do not allow callers of miniature() to set srcs, cmd, or outs -
        # _miniature_impl overrides their values when calling native.genrule()
        "srcs": None,
        "cmd": attr.string(doc = "convert func"),
        "outs": None,
    },
)
