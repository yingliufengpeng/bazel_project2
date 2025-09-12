

#include <iostream>
#include "include/PengTypes.h"
#include "include/PengDialect.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"
#include "mlir/include/mlir/IR/Builders.h"


//
#define GET_TYPEDEF_CLASSES
#include "llvm_demo/peng_dialect/PengTypes.cpp.inc"

namespace mlir::peng {
    void PengDialect::registerTypes() {
        addTypes<
                       #define GET_TYPEDEF_LIST
                       #include "llvm_demo/peng_dialect/PengTypes.cpp.inc"
                   >();

    }

}
