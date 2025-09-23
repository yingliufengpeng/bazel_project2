load("//toolchain_demo:toolchain.bzl", "py_toolchain_impl")
load("@bazel_tools//tools/build_defs/repo:local.bzl", "local_repository", "new_local_repository")

def _python_repo_impl(ctx):
    ctx.file("BUILD.bazel", ctx.attr.build_file_content)
#    ctx.file("python_tool.py", "#!/usr/bin/env python3\nprint('hello from toolchain')\n")

python_repo = repository_rule(
    implementation = _python_repo_impl,
    attrs = {
        "build_file_content": attr.string(mandatory = True, doc = "build_file_content string."),
     },
)

def _python_toolchain_ext_impl(module_ctx):
    # 声明一个 repo，里面放 toolchain 注册

    build_file_content = """
load("@bazel_project2//toolchain_demo:toolchain.bzl", "py_toolchain_impl")

py_toolchain_impl(
  name = "py_impl",
  interpreter = "python3",
  version = "python3",
)

toolchain(
  name = "py_toolchain",
  toolchain_type = "@bazel_project2//toolchain_demo:py_toolchain_type",
  toolchain = ":py_impl",
)

"""


    python_repo(
        name = 'py_toolchain_repo',
        build_file_content=build_file_content
    )


python_toolchain_ext = module_extension(
    implementation = _python_toolchain_ext_impl,
)
