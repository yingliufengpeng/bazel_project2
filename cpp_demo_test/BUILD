load(":new_rule.bzl", "show")

package_group(
    name = "mytest_group",
    packages = ["//cpp_demo_test/my_test"],
)

filegroup(
    name = "file1",
    srcs = glob(["*.cpp"]),
)

cc_test(
    name = "my_test",
    srcs = [":file1"],
    deps = [
        "@googletest//:gtest_main",
        # 其他依赖...
        "//cpp_demo:lib1",
    ],
)

show(4)
