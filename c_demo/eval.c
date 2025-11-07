//
// Created by peng on 2025/11/7.
//

#include "eval.h"



int EVAL_Value(int bytecode[]) {


#if defined(_WIN32)
#else
        static void *opcode_targets[] = OPERATOR_TARGETS;
#endif


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

            TARGET(OP_PUSH_CONST) {
                NEXT_ARG();
                PUSH_STACK();
                DISPATCH()
            }

            TARGET(OP_ADD) {
                int r1 = STACK_VALUE(-2) + STACK_VALUE(-1);
                STACK_SP_SUB();

                STACK_SET_TOP(r1);
                DISPATCH();
            }

            TARGET(OP_SUB) {
                int r1 = STACK_VALUE(-2)  - STACK_VALUE(-1);
                STACK_SP_SUB();
                STACK_SET_TOP(r1);
                DISPATCH();
            }

            TARGET(OP_SQAURE) {
                int r1 = STACK_TOP();
                int r2 = SQR(r1);
                STACK_SET_TOP(r2);
                DISPATCH();
            }
            TARGET(OP_PRINT_TOP) {
                printf("TOP Value is %d\n", STACK_TOP());
                // STACK_SP_SUB();
                DISPATCH()
            }

            TARGET(OP_HALT) {
                printf("Halt the programm!!\n");
                DISPATCH_EXIT();
            }

            DEFATULT {
                printf("Halt ERROR running here!!\n");
                DISPATCH_ERROR();
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

error:
    return -1;
end:
    return 0;



}