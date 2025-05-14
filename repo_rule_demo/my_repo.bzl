def _my_repo_impl(ctx):
    # 下载文件
    ctx.download(
        url = ctx.attr.url,
        #        sha256 = ctx.attr.sha256,
        output = "archive.tar.gz",
    )

    # 解压文件
    ctx.execute(["tar", "-xzf", "archive.tar.gz"])

    # 生成 BUILD 文件
    ctx.file(
        "BUILD.bazel",
        """
package(default_visibility = ["//visibility:public"])


        """,
    )

my_repo_rule = repository_rule(
    implementation = _my_repo_impl,
    attrs = {
        "url": attr.string(mandatory = True, doc = "URL to download the archive"),
        "sha256": attr.string(doc = "SHA256 checksum of the archive"),
    },
)
