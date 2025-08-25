load("@rules_nodejs//nodejs:repositories.bzl", "nodejs_repositories")

#nodejs_repositories(
#    name = "my_node",
#    node_version = "8.11.1",
#)

def setup_nodejs():
    pass
    # NodeJS 工具链

# 安装 npm/yarn 依赖

#    yarn_install(
#        name = "npm_deps",
#        package_json = "//:package.json",
#        yarn_lock = "//:yarn.lock",
#    )
#    module.use_repo("npm_deps")

#    nodejs_binary(
#        name = "server",
#        data = ["@npm_deps//:node_modules"],
#        entry_point = "index.js",
#    )
