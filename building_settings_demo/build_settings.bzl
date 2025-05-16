# example/buildsettings/build_settings.bzl
FlavorProvider = provider(fields = ["type"])

def _impl(ctx):
    v = ctx.build_setting_value
    print("------- ", v)
    return FlavorProvider(type = ctx.build_setting_value)

flavor = rule(
    implementation = _impl,
    build_setting = config.string(flag = True),  # 构建的配置项,
)

allow_multiple_flag = rule(
    implementation = _impl,
    build_setting = config.string(flag = True, allow_multiple = True),  # 构建的配置项
)
