module {
  func.func @add(%a: i32, %b: i32) -> i32 {
    %0 = arith.addi %a, %b : i32
    return %0 : i32
  }

  func.func @sum_loop(%n: index) -> i32 {
    %c0 = arith.constant 0 : i32
    %z  = arith.constant 0 : index
    %res = scf.for %i = %z to %n step %z + 1 {
      %i32 = arith.index_cast %i : index to i32
      %c0p = arith.addi %c0, %i32 : i32
      scf.yield %c0p : i32
    }
    return %res : i32
  }
}
