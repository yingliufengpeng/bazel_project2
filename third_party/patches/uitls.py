from pathlib import Path
import shutil
import argparse

# 1. 创建解析器
parser = argparse.ArgumentParser(description="这是一个示例程序")

# 2. 添加参数
parser.add_argument(
    "--src",      # 参数名称，调用时用 --name
    type=str,      # 类型
    help = 'src dir'
)

parser.add_argument(
    "--to",
    type=str,
    help = 'dest dir'
)

# 3. 解析参数
args = parser.parse_args()

# 4. 使用参数
print(f" copying ... {args.src} ---> {args.to}")



def copy_to_dest(src, dest):
    src = Path(rf'{src}')
    dst = Path(rf'{dest}')

    #breakpoint()
    for pattern in ['*.origin', '*.bzl']:
        print(f'pattern is {pattern}')
        for f in src.rglob(pattern):
            path = f.relative_to(src)
            print(f'copying  {f} to {dest/path}')
            dest_f = dst / path
            dest_f.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(f, dst / path)





if __file__ == '__main__':
    copy_to_dest(args.src, args.to)








