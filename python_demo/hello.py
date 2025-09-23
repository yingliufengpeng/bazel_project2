import os

print("Hello from Bazel!")
print("RUNFILES_DIR =", os.environ.get("RUNFILES_DIR"))
print("RUNFILES_MANIFEST_FILE =", os.environ.get("RUNFILES_MANIFEST_FILE"))
