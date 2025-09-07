

#include <iostream>
#include "include/PengDialect.h"

#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"

#include "llvm_demo/peng_dialect/PengDialect.cpp.inc"

namespace mlir {
    namespace Peng {

        void PengDialect::initialize() {
            std::cout << "PengDialect is initializing ...";
        }


    }
}