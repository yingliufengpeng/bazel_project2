
include "mlir/IR/DialectBase.td"

def Peng_Dialect : Dialect {

    let name = "Peng";

    let summary = "";

    let description = "";

    let cppNamespace = "::mlir::peng";

    let extraClassDeclaration = [{

      void registerTypes();
    }];

    let useDefaultTypePrinterParser  = 1;


}


