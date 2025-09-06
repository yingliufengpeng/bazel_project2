#include "llvm_demo/lib/Dialect/Noisy/NoisyDialect.h"

#include "llvm_demo/lib/Dialect/Noisy/NoisyOps.h"
#include "llvm_demo/lib/Dialect/Noisy/NoisyTypes.h"
#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"

#include "llvm_demo/lib/Dialect/Noisy/NoisyDialect.cpp.inc"
#define GET_TYPEDEF_CLASSES
#include "llvm_demo/lib/Dialect/Noisy/NoisyTypes.cpp.inc"
#define GET_OP_CLASSES
#include "llvm_demo/lib/Dialect/Noisy/NoisyOps.cpp.inc"

namespace mlir {
namespace tutorial {
namespace noisy {

void NoisyDialect::initialize() {
  addTypes<
#define GET_TYPEDEF_LIST
#include "llvm_demo/lib/Dialect/Noisy/NoisyTypes.cpp.inc"
      >();
  addOperations<
#define GET_OP_LIST
#include "llvm_demo/lib/Dialect/Noisy/NoisyOps.cpp.inc"
      >();
}

} // namespace noisy
} // namespace tutorial
} // namespace mlir
