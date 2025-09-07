#ifndef Peng_Dialect

#define Peng_Dialect


include "mlir/IR/DialectBase.td"

def PengDialect : Dialect {

    let name = "Peng";

    let summary = "";

    let description = "";

    let cppNamespace = "::mlir::Peng";


}



#endif //Peng_Dialect
