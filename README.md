
# 或者单独设置外部依赖缓存
build --repository_cache=E:/bazel_local_repo
build --disk_cache=E:/bazel_local/disk
# 设置输出根目录
startup --output_base=E:/bazel_local_repo/bazel_out


# 切记, 尽量是用bazelisk  而非使用 bazel ,原因在于前者可以管理多个bazel版本,可以运行不同的项目中.


# 该文档记录自己学习bazel中,自己所遇到的一些问题,并记录下来,以便于自己和其他的学习者可以快速的进入到这个领域.

# sometimes you need to install following requirements for GLIB-x-x-x not founed.
conda install  libstdcxx-ng -c conda-forge

# update python package cmd 
bazelisk  run :requirements.update

# use gdb debug python/c++ code 

gdb --args  python bazel-bin/python_bind3/python_basic_test

# in console we need to ` run  ` in order to get debug symbol
set breakpoint pending on
b python_bind3/pybind_python.cpp:140

# 使用模块扩展
python = use_extension("@rules_python//python:extensions.bzl", "python")
python.toolchain(python_version = "3.9")
python.toolchain(python_version = "3.10")
use_repo(
    python,
    py39 = "python_3_9",  # 重命名 python_3_9 为 py39
    py310 = "python_3_10",  # 重命名 python_3_10 为 py310
)


Note!!!
        sources_hash = rule(
            _sources_hash_impl,
                attrs = {
                    "go_library": attr.label(
                    aspects = [_get_all_sources],
                    providers = [GoSource],
                ),
                "_hasher": attr.label(
                    cfg = "exec",
                    default = Label("//manifest/hasher"),
                    executable = True,
                ),
        },
        )

    `providers` is guaranteed to ensure  go_library 's label which belongs to some 
        rule must have GoSource in that return values.

 

# 有时候,更新requirements 需要手动执行以下的命令
bazel-bin/requirements.update.exe '--src=_main/pyproject.toml' _main/requirements_lock_3_12.txt //:requirements '--resolver=backtracking' --allow-unsafe --generate-hashes

# 这条命令的目的是刷新库中的相关的BUILD文件建立
bazelisk.exe query @pip_deps2//...  




 

