#include "eval.h"

int main( ) {

    int bytecode[] = {
        OP_PUSH_CONST, 11,
        OP_PUSH_CONST, 20,
        OP_ADD,
        OP_PUSH_CONST, 30,
        OP_SUB,
        OP_PUSH_CONST, 3,
        OP_ADD,
        OP_PRINT_TOP,
        OP_PUSH_CONST, 41,
        OP_PUSH_CONST, 2,
        OP_FULL_CALL, 3, OP_ADD,
        OP_SQAURE,
        OP_PRINT_TOP,
        OP_HALT,
    };

    int res = EVAL_Value(bytecode);
    printf("running result is %d\n", res);

    return 0;
}





