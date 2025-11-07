#include <stdio.h>
#include <stdlib.h>

/*
  一个更接近 CPython 的循环式虚拟机（computed goto + 块作用域）

  模拟逻辑：
    10 + 20
*/

enum {
    OP_PUSH_CONST,
    OP_ADD,
    OP_PRINT_TOP,
    OP_HALT
};

#define TARGET(op) TARGET_##op
#define DISPATCH_GOTO() goto *opcode_targets[opcode]
#define NEXTOPCODE() (opcode = bytecode[pc++])
#define NEXTARG() (arg = bytecode[pc++])
#define DISPATCH() goto dispatch_loop

int main(void) {
    int bytecode[] = {
        OP_PUSH_CONST, 10,
        OP_PUSH_CONST, 20,
        OP_ADD,
        OP_PRINT_TOP,
        OP_HALT
    };

    int stack[128];
    int sp = 0;
    int pc = 0;
    int opcode, arg;

    static void *opcode_targets[] = {
        &&TARGET(OP_PUSH_CONST),
        &&TARGET(OP_ADD),
        &&TARGET(OP_PRINT_TOP),
        &&TARGET(OP_HALT),
    };

    for (;;) {
        dispatch_loop:
                NEXTOPCODE();
        DISPATCH_GOTO();

        TARGET(OP_PUSH_CONST): {
            NEXTARG();
            stack[sp++] = arg;
            DISPATCH();
        }

        TARGET(OP_ADD): {
            if (sp < 2) {
                fprintf(stderr, "stack underflow on ADD\n");
                exit(1);
            }
            int b = stack[--sp];
            int a = stack[--sp];
            stack[sp++] = a + b;
            DISPATCH();
        }

        TARGET(OP_PRINT_TOP): {
            if (sp < 1) {
                fprintf(stderr, "stack underflow on PRINT_TOP\n");
                exit(1);
            }
            printf("Result: %d\n", stack[--sp]);
            DISPATCH();
        }

        TARGET(OP_HALT): {
            printf("Program halted.\n");
            break;
        }
    }

    return 0;
}
