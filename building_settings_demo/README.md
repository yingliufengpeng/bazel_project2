


//使用案例

bazel build building_settings_demo:f1 --//building_settings_demo:f1=432


bazel build building_settings_demo:f2 --//building_settings_demo:f2=432 --//building_settings_demo:f2=434

bazel build building_settings_demo:myflag  --//building_settings_demo:myflag='b'


bazel build building_settings_demo:my_drink --//building_settings_demo:f1=432

bazel build building_settings_demo:my-toolbox --//building_settings_demo:tool=//building_settings_demo:screwdriver 

bazel build building_settings_demo:harvest
bazel build building_settings_demo:harvest --//building_settings_demo:season=summer