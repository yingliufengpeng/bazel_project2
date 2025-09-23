load(":toolchain.bzl", "PyToolchainInfo")

def _my_py_binary_impl2(ctx):
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
        content = "{} rlocation({})\n".format(interpreter, ctx.files.srcs[0].short_path),
        #        content = "{} {}\n".format(interpreter, test_f),
        is_executable = True,
    )

    # 通过 symlink，把 hello.py 铺平到 runfiles 根目录
    runfiles = ctx.runfiles(
        symlinks = {
            "{}".format(main_file.short_path): main_file
            for main_file in ctx.files.srcs
        },
    )

    return [DefaultInfo(
        executable = sh,
        files = depset(ctx.files.srcs),
        #        runfiles = ctx.runfiles(files = ctx.files.srcs),
        runfiles = runfiles,
    )]

def _my_py_binary_impl(ctx):
    py_toolchain = ctx.toolchains["//toolchain_demo:py_toolchain_type"]
    interpreter = py_toolchain.info.interpreter
    #    py_toolchain = ctx.toolchains["@rules_python//python:toolchain_type"]
    #    interpreter = py_toolchain.py3_runtime.interpreter  # 获取 Python 可执行文件

    main = ctx.files.srcs[0]

    # 生成 wrapper 脚本
    wrapper = ctx.actions.declare_file(ctx.attr.name + "_wrapper.py")
    wrapper_content = """
import sys
import os

__fs_map__ = {}

with open('MANIFEST') as m_f:
    lines = m_f.readlines()
    for li in lines:
        l, r = li.split()
        __fs_map__[l] = r

#print('__fs_map__', __fs_map__)

#for i, arg in enumerate(sys.argv):
#    if i == 0:
#        continue
#    print('arg...', arg)
#
#    real_path = __fs_map__['_main/' + arg]
#    print('real_path', real_path)


main_py = __fs_map__['_main/' + sys.argv[1]]

with open(main_py, mode='r') as f:
    code = f.read()

# 执行原脚本
exec(compile(code, main_py, 'exec'))
    """  # 用逻辑路径
    is_windows = ctx.var["TARGET_CPU"] == "x64_windows"

    if is_windows:
        launcher = ctx.actions.declare_file(ctx.label.name + ".cmd")
        interpreter = '"{}"'.format(interpreter)

        content = """{}  ../{}  {}
                      """.format(interpreter, wrapper.basename,
                      " ".join([e.short_path for e in ctx.files.srcs]))
    else:
        launcher = ctx.actions.declare_file(ctx.label.name + ".sh")
        content = """{} {} """.format(interpreter, main.path)

    ctx.actions.write(wrapper, wrapper_content, is_executable = True)

    #    launcher = ctx.actions.declare_file(ctx.attr.name + ".cmd")
    ctx.actions.write(launcher, content, is_executable = True)
    #    print("dddd", """ {} "../{}" %* """.format(interpreter, wrapper.basename))
    #    print("dddd", dir(wrapper))
    #    print("root", wrapper.root.path)
    #    print("basename", wrapper.basename)

    # runfiles 包含源文件和 wrapper
    runfiles = ctx.runfiles(files = [main, wrapper])

    return [DefaultInfo(
        executable = launcher,
        files = depset(ctx.files.srcs),
        runfiles = runfiles,
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
