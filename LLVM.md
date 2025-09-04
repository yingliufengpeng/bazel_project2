
# llvm搭建 
 注意: 该搭建逻辑是基于llvm源码就行搭建. 并非是基于vcpkg管理的逻辑. 
 
# 第一步
``` bash  
    
 git clone --branch  llvmorg-17.0.3  https://github.com/llvm/llvm-project.git  llvm-17.0.3

 cd llvm-17.0.3 
 
 touch BUILD.bazel
 
 cp 
 
 mkdir build
 
 cd build 
 
 cmake ../llvm  
 
 cp build/include/llvm/Config/config.h  llvm/include/llvm/Config
 cp build/include/llvm/Config/llvm-config.h  llvm/include/llvm/Config
 
 
 
```


第二步
进入到 bazel_proejct2文件夹根目录
假设 llvm_dir = ....

```bash 
  cp ./third_party/patches/llvm-project-17.0.3/MODULE.template    llvm_dir/MODULE.bazel
  cp ./third_party/patches/llvm-project-17.0.3/gast_rename_bazel.py     llvm_dir

   python ./third_party/patches/uitls.py  --src  ./third_party/patches/llvm-project-17.0.3     --to  llvm_dir  
   
   python llvm_dir/gast_rename_bazel.py  
    
```
