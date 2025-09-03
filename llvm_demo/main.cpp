// third_party/llvm/main.cc
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include <iostream>

int main() {
    mlir::MLIRContext context;
    mlir::OpBuilder builder(&context);

    std::cout << "MLIR demo works!" << std::endl;
    return 0;
}
