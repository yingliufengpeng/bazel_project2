cc_library(
    name = "my_lib",
    hdrs = ["include/my_header.h"],
    include_prefix = "third_party/my_lib",
    #    strip_include_prefix = "include",
    #    visibility = "//visibility:public",
    visibility = ["//cpp_demo:__pkg__"],  # Allow //cpp_demo package to access this target
)

cc_library(
    name = "my_lib2",
    hdrs = ["include/my_header.h"],
    include_prefix = "third_party/my_lib",
    strip_include_prefix = "include",
    #    visibility = "//visibility:public",
    visibility = ["//cpp_demo:__pkg__"],  # Allow //cpp_demo package to access this target
)
