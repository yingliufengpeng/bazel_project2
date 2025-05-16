load(":build_settings.bzl", "FlavorProvider")

def _rule_impl(ctx):
    if ctx.attr.flavor[FlavorProvider].type == "ORANGE":
        print("drink_rule running ...")
    else:
        print("drink_rule kkkk running ...")

drink_rule = rule(
    implementation = _rule_impl,
    attrs = {
        "flavor": attr.label(),
    },
)
