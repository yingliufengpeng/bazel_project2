

#include <iostream>

#include "mlir/include/mlir/IR/Builders.h"
#include "llvm/include/llvm/ADT/TypeSwitch.h"
#include "include/PengDialect.h"
#include "include/PengTypes.h"

#define GET_TYPEDEF_CLASSES
#include "llvm_demo/peng_dialect/PengDialect.cpp.inc"
#include "llvm_demo/peng_dialect/PengTypes.cpp.inc"



namespace mlir {
    namespace peng {



        namespace inner {
            void registerTypesImpl();

            void registerTypes() {
             }
        }

        void PengDialect::initialize() {
            std::cout << "PengDialect is initializing ..." << std::endl;
            llvm::outs() << "PengDialect  --> "  << getDialectNamespace()  ;

            addTypes<
                   #define GET_TYPEDEF_LIST
                   #include "llvm_demo/peng_dialect/PengTypes.cpp.inc"
               >();

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