#include "llvm/IR/Module.h"
#include "mlir/IR/MLIRContext.h"
#include <iostream>

int main() {
    mlir::MLIRContext context;

    std::cout << "MLIR Module created!" << std::endl;
    return 0;
}
