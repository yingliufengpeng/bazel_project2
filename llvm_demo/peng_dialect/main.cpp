//
// Created by peng on 7/9/2025.
//

#include "include/PengDialect.h"

#include "mlir/IR/DialectRegistry.h"

#include "mlir/IR/MLIRContext.h"


int main() {
    mlir::DialectRegistry DialectRegistry;
    mlir::MLIRContext context(DialectRegistry);
    auto diaglect = context.getOrLoadDialect<mlir::Peng::PengDialect>();
    diaglect->sayHello();
    return 0;
}