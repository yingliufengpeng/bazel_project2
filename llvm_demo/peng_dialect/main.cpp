//
// Created by peng on 7/9/2025.
//


#include "mlir/IR/Types.h"

#include "mlir/IR/DialectRegistry.h"

#include "mlir/IR/MLIRContext.h"

#include "include/PengDialect.h"
#include "include/PengTypes.h"
#include "include/PengEnums.h"
int main() {
    mlir::DialectRegistry DialectRegistry;
    mlir::MLIRContext context(DialectRegistry);
    auto diaglect = context.getOrLoadDialect<mlir::peng::PengDialect>();

    auto f32 = mlir::Float32Type::get(&context);
    llvm::outs() << f32;
    llvm::outs() << "\n";
    auto peng_tensor = mlir::peng::PTensorType::get(&context, {3, 4}, mlir::Float64Type::get(&context), 3);
    llvm::outs() << "peng_tensor" << "\t";
    peng_tensor.dump();
    llvm::outs() << "\n";

    auto m = mlir::peng::stringifyBinaryOp(mlir::peng::BinaryOp::Add);

    llvm::outs() << "m" << "\t" << m << "\n";



    return 0;
}






















