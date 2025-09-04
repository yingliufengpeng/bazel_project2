path = select({
    "@platforms//os:windows": "D:/repo/llvm_repo/llvmorg-17.0.3",
    "@platforms//os:linux": "/home/peng/src_repo/llvm_src/llvmorg-17.0.3",
})
