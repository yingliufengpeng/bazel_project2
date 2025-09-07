#ifndef Peng_Dialect

#define Peng_Dialect


include "mlir/IR/DialectBase.td"

def PengDialect : Dialect {

    let name = "Peng";

    let summary = "";

    let description = "";

    let cppNamespace = "::mlir::peng";

    let extraClassDeclaration = [{
      static void sayHello();
      static void sayHello2();
      static void sayHello3();
    }];




}



#endif //Peng_Dialect
