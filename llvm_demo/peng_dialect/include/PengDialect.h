//
// Created by peng on 7/9/2025.
//

#ifndef BAZEL_PROJECT2_PENGDIALECT_H
#define BAZEL_PROJECT2_PENGDIALECT_H
#include "mlir/include/mlir/IR/DialectImplementation.h"
#include <iostream>

#include "llvm_demo/peng_dialect/PengDialect.h.inc"

namespace mlir {
    namespace Peng {

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

#endif //BAZEL_PROJECT2_PENGDIALECT_H
