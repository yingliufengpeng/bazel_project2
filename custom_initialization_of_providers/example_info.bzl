def _exampleinfo_init_banned(*args, **kwargs):
    fail("Do not call ExampleInfo(). Use make_exampleinfo() instead.")

ExampleInfo, _new_exampleinfo = provider(
    fields = [
        "files_to_link",
        "headers",
    ],
    init = _exampleinfo_init_banned,
)

def make_exampleinfo(files_to_link, headers):
    return _new_exampleinfo(files_to_link = files_to_link, headers = headers)
