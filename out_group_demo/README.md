


bazel build out_group_demo:my_rule1   --output_groups=debug_files
bazel build out_group_demo:my_rule1   --output_groups=all_files

add `--output_groups` will change rule's generation output which only
generate files which belongs to one of flags of OutputGroupInfo 