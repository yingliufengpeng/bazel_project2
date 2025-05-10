load("//zip_archive:rule.bzl", "zip_archive")

zip_archive(
    name = "zip1",
    files = ["READMD.md"],
    output = "out.zip",
)

genrule(
    name = "zip2",
    srcs = ["READMD.md"],
    outs = ["out2.zip"],
    cmd = "zip $(OUTS)   $(SRCS) ",
)
