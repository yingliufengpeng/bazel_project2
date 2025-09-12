//
// Created by peng on 9/7/25.
//


// PengEnums.td



include "PengDialect.td"

// 定义一个枚举
include "mlir/IR/EnumAttr.td"

def PengBinaryOp : I32EnumAttr<
    "BinaryOp",
    "peng 二元操作",
    [
      I32EnumAttrCase<"Add", 0, "add">,
      I32EnumAttrCase<"Sub", 1, "sub">,
      I32EnumAttrCase<"Mul", 2, "mul">,
      I32EnumAttrCase<"Div", 3, "div">
    ]
> {
  let cppNamespace = "mlir::peng";
}


def PengBinaryOpAttr : EnumAttr<Peng_Dialect, PengBinaryOp, "BinOp"> {

    let assemblyFormat = "`<` $value `>`";
}


























