#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
  兼容 Windows/Linux 的宏化循环式虚拟机
  模拟逻辑：10 + 20 - 34
*/

#define SQR(x) ((x) * (x))


enum {
    OP_PUSH_CONST,
    OP_ADD,
    OP_SUB,
    OP_SQAURE,
    OP_PRINT_TOP,
    OP_HALT,
};

#define PUSH_STACK()  stack[sp++] = (arg)
#define STACK_SET_TOP(x) stack[sp - 1] = (x)
#define STACK_TOP() stack[sp - 1]
#define STACK_VALUE(offset) stack[sp + (offset)]
#define STACK_SP_ADD() sp += 1
#define STACK_SP_SUB() sp -= 1
#define NEXT_OP_CODE()  opcode = bytecode[pc++]
#define NEXT_ARG() (arg = bytecode[pc++])
#define DISPATCH_EXIT() goto end  /* switch-case 内用 break 跳到下次循环 */

#if defined(_WIN32)

    #define TARGET(op) case op

    #define DISPATCH() \
        NEXT_OP_CODE(); \
        break;  /* switch-case 内用 break 跳到下次循环 */
    #define DEFATULT default

#else

#define TARGET(op) op
#define DISPATCH() \
    NEXT_OP_CODE(); \
    goto *opcode_targets[opcode];  /* switch-case 内用 compute_gotos 跳到下次地址 */
#define DEFATULT default_end


#endif



int main( ) {
#if defined(_WIN32)
#else
    static void *opcode_targets[] = {
        &&TARGET(OP_PUSH_CONST),
        &&TARGET(OP_ADD),
        &&TARGET(OP_SUB),
        &&TARGET(OP_SQAURE),
        &&TARGET(OP_PRINT_TOP),
        &&TARGET(OP_HALT),
    };
#endif

    int bytecode[] = {
        OP_PUSH_CONST, 11,
        OP_PUSH_CONST, 20,
        OP_ADD,
        OP_PUSH_CONST, 30,
        OP_SUB,
        OP_PUSH_CONST, 3,
        OP_ADD,
        OP_SQAURE,
        OP_PRINT_TOP,
        OP_HALT
    };

    int stack[128];
    int sp = 0;
    int pc = 0;
    int opcode, arg;


    goto start_frame;
#if defined(_WIN32)

    for (;;) {
        switch (opcode) {
#else
    {
#endif

        TARGET(OP_PUSH_CONST): {
            NEXT_ARG();
            PUSH_STACK();
            DISPATCH()
        }

        TARGET(OP_ADD): {
            int r1 = STACK_VALUE(-2) + STACK_VALUE(-1);
            STACK_SP_SUB();

            STACK_SET_TOP(r1);
            DISPATCH();
        }

        TARGET(OP_SUB): {
            int r1 = STACK_VALUE(-2)  - STACK_VALUE(-1);
            STACK_SP_SUB();
            STACK_SET_TOP(r1);
            DISPATCH();
        }

        TARGET(OP_SQAURE): {
            int r1 = STACK_TOP();
            int r2 = SQR(r1);
            STACK_SET_TOP(r2);
            DISPATCH();
        }
        TARGET(OP_PRINT_TOP): {
            printf("TOP Value is %d\n", STACK_TOP());
            // STACK_SP_SUB();
            DISPATCH()
        }

        TARGET(OP_HALT): {
            printf("Halt the programm!!\n");
            DISPATCH_EXIT();
        }

        DEFATULT: {
            printf("Halt ERROR running here!!\n");
            DISPATCH_EXIT();
        }

        start_frame: {
            DISPATCH()
        }

#if defined(_WIN32)
    }
}
#else
    }
#endif

    end:
    return 0;
}
