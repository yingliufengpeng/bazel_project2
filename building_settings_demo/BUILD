load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

# example/BUILD
load(":build_settings.bzl", "allow_multiple_flag", "flavor")
load(":defs.bzl", "fruit", "harvest", "tool", "toolbox")
load(":rules.bzl", "drink_rule")

string_flag(
    name = "myflag",
    build_setting_default = "a",
    values = [
        "a",
        "b",
        "c",
    ],
)

flavor(
    name = "f1",
    build_setting_default = "APPLE",
)

allow_multiple_flag(
    name = "f2",
    build_setting_default = "APPLE2",
)

drink_rule(
    name = "my_drink",
    flavor = ":f1",
)

# Define a label_flag (or setting) using the built-in bazel rules.
# Its default value is the default target this flag should point to.
label_flag(
    name = "tool",
    build_setting_default = ":hammer",
)

# A target that depends on the label flag.
toolbox(name = "my-toolbox")

# Some targets that are potential values of the label flag.
tool(name = "hammer")

tool(name = "screwdriver")

# -------------------------   season  build test ----------------
string_flag(
    name = "season",
    build_setting_default = "spring",
)

harvest(
    name = "harvest",
    fruit = select({
        ":summer": ":cherries",
        ":fall": ":pumpkins",
        "//conditions:default": ":apples",
    }),
)

config_setting(
    name = "summer",
    flag_values = {
        ":season": "summer",
    },
)

config_setting(
    name = "fall",
    flag_values = {
        ":season": "fal l",
    },
)

fruit(name = "cherries")

fruit(name = "apples")

fruit(name = "pumpkins")
