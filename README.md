
# sometime you need to install following requirements for GLIB-x-x-x not founed.
conda install  libstdcxx-ng -c conda-forge


# use gdb debug python/c++ code 

gdb --args  python bazel-bin/python_bind3/python_basic_test

# in console we need to ` run  ` in order to get debug symoal
set breakpoint pending on
b python_bind3/pybind_python.cpp:140


