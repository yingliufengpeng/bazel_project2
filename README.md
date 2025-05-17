
# sometimes you need to install following requirements for GLIB-x-x-x not founed.
conda install  libstdcxx-ng -c conda-forge


# use gdb debug python/c++ code 

gdb --args  python bazel-bin/python_bind3/python_basic_test

# in console we need to ` run  ` in order to get debug symoal
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

