# NodeJS 服务器

# Python FastAPI 服务器
load("@rules_python//python:defs.bzl", "py_binary")
load("@rules_python//python:pip.bzl", "compile_pip_requirements")
load("//module_load:node_setup.bzl", "setup_nodejs")

# 初始化 NodeJS 和 Python repo
setup_nodejs()

compile_pip_requirements(
    name = "requirements",
    src = "pyproject.toml",
    requirements_txt = "requirements_lock_3_12.txt",
)
