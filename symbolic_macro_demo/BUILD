load(":miniature.bzl", "miniature")

miniature(
    name = "logo_miniature",
    src = "image.png",
    cmd = "cp $<  $@",
)

cc_binary(
    name = "my_app",
    srcs = ["my_app.cpp"],
    data = [":logo_miniature"],
)
