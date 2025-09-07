//
// Created by peng on 9/7/25.
//

#ifndef BAZEL_PROJECT2_PENGTYPES_TD_H
#define BAZEL_PROJECT2_PENGTYPES_TD_H
include "PengDialect.td"
include "mlir/IR/AttrTypeBase.td"

class Peng_Type<string name, string typeMnemonic> : TypeDef<PengDialect, name> {
  let mnemonic = typeMnemonic;
  let typeName = dialect.name# "." #typeMnemonic;
}

//def Noisy_I32 : Noisy_Type<"PengI32", "i32"> {
//  let summary = "A type for approximate 32-bit integers.";
//}

def PengTensor : Peng_Type<"PTensor", "p_tensor"> {
  let summary = "PengTensor for PengDialect.";
  let description = "A Peng tensor type with shape, element type and device id.";

  let parameters = (ins
    ArrayRefParameter<"int64_t">:$shape,
    "Type":$elementType,
    "int64_t":$device_id
  );

//    let builders = [
//      TypeBuilder<(ins
//        "::mlir::ArrayRef<int64_t>":$shape,
//        "::mlir::Type":$elementType
//      ), [{
//        return $_self.get($_ctx, $shape, $elementType, 0);
//      }]>
//    ];
  let genStorageClass = 1;
//  let hasCustomAssemblyFormat = 0;

  let assemblyFormat = "`<`$shape`,`$elementType`,`$device_id`>`";

  let genVerifyDecl = 0;
}



























#endif //BAZEL_PROJECT2_PENGTYPES_TD_H