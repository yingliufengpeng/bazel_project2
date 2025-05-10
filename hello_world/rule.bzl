
def _impl(ctx):
    print('target label {}'.format(ctx.label))
    print('content is {}'.format(ctx.attr.text))
    # new_file = ctx.actions.declare_file(ctx.attr.output_file)
    new_file = ctx.outputs.output_file 
    print(new_file)
    print('----')
    # print(type(new_file))

    ctx.actions.write(
        content=ctx.attr.text,
        output=new_file,
    )

    return DefaultInfo(
        files=depset([new_file])
    )


generate_file = rule(
    implementation = _impl,
    attrs = {
        'text': attr.string(mandatory=True),
        # 'output_file': attr.string(mandatory=True)
        'output_file': attr.output(mandatory=True)
    }

)