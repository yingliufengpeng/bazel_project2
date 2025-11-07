#include <stdio.h>
#include <stdlib.h>

/*
  兼容 Windows 的宏化循环式虚拟机
  模拟逻辑：10 + 20
*/

enum {
    OP_PUSH_CONST,
    OP_ADD,
    OP_PRINT_TOP,
    OP_HALT,
    OP_END,
};

#if defined(_WIN32)

    #define TARGET(op) case op :
    #define NEXTOPCODE() (opcode = bytecode[pc++])
    #define NEXTARG() (arg = bytecode[pc++])
    #define DISPATCH() break  /* switch-case 内用 break 跳到下次循环 */
    #define DISPATCH_EXIT() goto end  /* switch-case 内用 break 跳到下次循环 */
    #define DEFATULT default :

#else


#define TARGET(op) op :
#define NEXTOPCODE() (opcode = bytecode[pc++])
#define NEXTARG() (arg = bytecode[pc++])
#define DISPATCH() goto opcode_targets[op]  /* switch-case 内用 break 跳到下次循环 */
#define DISPATCH_EXIT goto end
#define DEFATULT default_end :

static void *opcode_targets[] = {
    &&TARGET(OP_PUSH_CONST),
    &&TARGET(OP_ADD),
    &&TARGET(OP_PRINT_TOP),
    &&TARGET(OP_HALT),
    &&TARGET(OP_END),
};

#endif







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

    for (;;) {
        NEXTOPCODE();

        switch (opcode) {

            TARGET(OP_PUSH_CONST) {
                NEXTARG();
                stack[sp++] = arg;
                DISPATCH();
            }

            TARGET(OP_ADD)  {
                if (sp < 2) {
                    fprintf(stderr, "stack underflow on ADD\n");
                    exit(1);
                }
                int b = stack[--sp];
                int a = stack[--sp];
                stack[sp++] = a + b;
                DISPATCH();
            }

            TARGET(OP_PRINT_TOP) {
                if (sp < 1) {
                    fprintf(stderr, "stack underflow on PRINT_TOP\n");
                    exit(1);
                }
                printf("Result: %d\n", stack[--sp]);
                DISPATCH();
            }

            TARGET(OP_HALT) {
                printf("Program halted.\n");
                DISPATCH_EXIT();
            }

            DEFATULT {
                fprintf(stderr, "Unknown opcode: %d\n", opcode);
                DISPATCH_EXIT();
            }
        }
    }


end:

    return 0;
}
