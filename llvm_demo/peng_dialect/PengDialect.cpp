

#include <iostream>


#include "include/PengDialect.h"


#define GET_TYPEDEF_CLASSES
#include "llvm_demo/peng_dialect/PengDialect.cpp.inc"




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

            registerTypes();

        }







    }
}