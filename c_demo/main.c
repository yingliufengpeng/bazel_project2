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
};

#define PUSH_STACK()  stack[sp++] = (arg)
#define STACK_SET_TOP(x) stack[sp - 1] = (x)
#define STACK_TOP() stack[sp - 1]
#define STACK_VALUE(offset) stack[sp - offset]
#define STACK_SP_ADD() sp += 1
#define STACK_SP_SUB() sp -= 1
#define NEXTOPCODE() (opcode = bytecode[pc++])
#define NEXTARG() (arg = bytecode[pc++])
#define DISPATCH_EXIT() goto end  /* switch-case 内用 break 跳到下次循环 */

#if defined(_WIN32)

    #define TARGET(op) case op

    #define DISPATCH() break  /* switch-case 内用 break 跳到下次循环 */
    #define DEFATULT default

#else


#define TARGET(op) op
#define DISPATCH() \
    NEXTOPCODE(); \
    goto *opcode_targets[opcode];  /* switch-case 内用 break 跳到下次循环 */
#define DEFATULT default_end



#endif



int main( ) {

#if defined(_WIN32)
#else
    static void *opcode_targets[] = {
        &&TARGET(OP_PUSH_CONST),
        &&TARGET(OP_ADD),
        &&TARGET(OP_PRINT_TOP),
        &&TARGET(OP_HALT),
    };
#endif

    int bytecode[] = {
        OP_PUSH_CONST, 10,
        OP_PUSH_CONST, 20,
        OP_ADD,
        OP_PUSH_CONST, 34,
        OP_PRINT_TOP,
        OP_HALT
    };

    int stack[128];
    int sp = 0;
    int pc = 0;
    int opcode, arg;


    goto start_frame;
#if defined(_WIN32)

    for (;; ) {
#else
    {
#endif

        TARGET(OP_PUSH_CONST): {
            NEXTARG();
            PUSH_STACK();

            DISPATCH()

        }

        TARGET(OP_ADD): {

            int r1 = STACK_VALUE(2) + STACK_VALUE(1);
            STACK_SET_TOP(r1);
            STACK_SP_SUB();
            DISPATCH();
        }

        TARGET(OP_PRINT_TOP): {

            printf("%d\n", STACK_TOP());
            STACK_SP_SUB();
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
#else
    }
#endif



    end:
    return 0;
}
