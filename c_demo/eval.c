//
// Created by peng on 2025/11/7.
//

#include "eval.h"



static int add(int a, int b) {return a + b;}
static int sub(int a, int b) {return a - b;}
static int mul(int a, int b) {return a * b;}



static op_func_t op_fun_tables[] = {
    [ADD] = add,
    [SUB] = sub,
    [MUL] = mul,
};

int f_call(int arr[], int num, op_func_t acc) {
    int sum = 0;
    for (int i = 0; i < num; i++) {
        sum = acc(sum, arr[i]);
    }

    return sum;

}


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
                STACK_SP_DOWN();

                STACK_SET_TOP(r1);
                DISPATCH();
            }

            TARGET(OP_SUB) {
                int r1 = STACK_VALUE(-2)  - STACK_VALUE(-1);
                STACK_SP_DOWN();
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
                // STACK_SP_DOWN();
                DISPATCH()
            }

            TARGET(OP_FULL_CALL) {
                NEXT_ARG();
                int num = arg;
                NEXT_ARG();
                int f_t = arg;
                int *arr = malloc(num * sizeof(int));

                for (int i = 0; i < num; i++) {
                    arr[i] = STACK_VALUE(-i - 1);
                }

                int r = f_call(arr, num, op_fun_tables[f_t]);

                for (int i = 0; i < num; i++) {
                    STACK_SP_DOWN();
                }

                free(arr);

                STACK_SET_TOP(r);
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