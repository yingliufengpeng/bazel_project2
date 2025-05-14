load(":fortune.bzl", "haiku_fortune")
load(":template.bzl", "hello_world")

haiku_fortune(
    name = "fortune1",
    srcs = [
        "A.txt",
        "B.txt",
    ],
)

hello_world(
    name = "g_basic",
    template = "Basic.cc.tpl",
    username = "Yingliufenpeng  Mozlet",
)

cc_binary(
    name = "basic",
    srcs = [":g_basic"],
    deps = [],
)
