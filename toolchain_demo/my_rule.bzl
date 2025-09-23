load(":toolchain.bzl", "PyToolchainInfo")

def _my_py_binary_impl(ctx):
    py_toolchain = ctx.toolchains["//toolchain_demo:py_toolchain_type"]
    interpreter = py_toolchain.info.interpreter
    main = ctx.files.srcs[0]
    print("main   ", main)

    #    py_toolchain = ctx.toolchains["@rules_python//python:toolchain_type"]
    #
    #    #    print("dir(ctx) ", dir(ctx))
    #    #    print("xxxx ", dir(py_toolchain))
    #    #    print("yyyy ", dir(py_toolchain.py3_runtime))
    #    print("jjjj", dir(ctx.fragments.bazel_py))
    #    python = ctx.fragments.bazel_py.python_path  # Python 可执行文件路径
    #    print("zzz", python, type(python))
    #    interpreter = py_toolchain.py3_runtime.interpreter  # 获取 Python 可执行文件
    #    python_exec_path = ctx.runfiles(files = [interpreter])
    #    #    print("2dir(python_exec_path)", dir(python_exec_path))
    #    #    print("2dir(python_exec_path.files)", dir(python_exec_path.files))
    #    #    print("yy", python_exec_path.files.to_list()[0].path)
    #
    #    path = python_exec_path.files.to_list()[0].path
    #    interpreter_path = py_toolchain.py3_runtime.interpreter_path  # 获取 Python 可执行文件

    #    print("dir333", dir(interpreter))
    #    print("root", interpreter.root.path)
    #    print("path", interpreter.path)
    #    print("basename", interpreter.basename)
    #    print("short_path", interpreter.short_path)
    #    print("interpreter_path", interpreter_path)
    #    print("VAR value is", ctx.var)
    is_windows = ctx.var["TARGET_CPU"] == "x64_windows"

    if is_windows:
        sh = ctx.actions.declare_file(ctx.label.name + ".cmd")
        interpreter = '"{}"'.format(interpreter)
    else:
        sh = ctx.actions.declare_file(ctx.label.name + ".sh")

    test_f = "D:\\repo\\clion_repo\\bazel_project2\\python_demo\\hello.py"
    ctx.actions.write(
        output = sh,
                content = "{} {}\n".format(interpreter, ctx.files.srcs[0].short_path),
        is_executable = True,
    )


    return [DefaultInfo(
        executable = sh,
        files = depset(ctx.files.srcs),
        runfiles = ctx.runfiles(files = ctx.files.srcs),
    )]

my_py_binary = rule(
    implementation = _my_py_binary_impl,
    attrs = {
        "srcs": attr.label_list(allow_files = [".py"]),
    },
    fragments = [
        "platform",
        "bazel_py",
    ],  # 引入 platform fragment
    toolchains = [
        "@rules_python//python:toolchain_type",
        "//toolchain_demo:py_toolchain_type",
    ],
    executable = True,
)
