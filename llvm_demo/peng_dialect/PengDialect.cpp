

#include <iostream>
#include "include/PengDialect.h"

#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"

#include "llvm_demo/peng_dialect/PengDialect.cpp.inc"

namespace mlir {
    namespace Peng {

        void PengDialect::initialize() {
            std::cout << "PengDialect is initializing ..." << std::endl;
            llvm::outs() << "PengDialect  --> "  << getDialectNamespace();
        }


        void PengDialect::sayHello() {
            std::cout << "AAA" << std::endl;

        }

        void PengDialect::sayHello2() {
            std::cout << "AAA" << std::endl;

        }

        void PengDialect::sayHello3() {
            std::cout << "BBB" << std::endl;

        }


    }
}