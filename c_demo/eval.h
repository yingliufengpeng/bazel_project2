//
// Created by peng on 11/7/25.
//

#ifndef BAZEL_PROJECT2_EVAL_H
#define BAZEL_PROJECT2_EVAL_H


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

    #define TARGET(op) case op :

    #define DISPATCH() \
        NEXT_OP_CODE(); \
        break;  /* switch-case 内用 break 跳到下次循环 */

    #define DEFATULT default :

#else
    #define TARGET_IMPL(op) op

    #define TARGET(op) TARGET_IMPL(op) :

    #define DISPATCH() \
        NEXT_OP_CODE(); \
        goto *opcode_targets[opcode];  /* switch-case 内用 compute_gotos 跳到下次地址 */

    #define DEFATULT default_end :

    #define OPERATOR_TARGETS  {         \
        &&TARGET_IMPL(OP_PUSH_CONST),   \
        &&TARGET_IMPL(OP_ADD),          \
        &&TARGET_IMPL(OP_SUB),          \
        &&TARGET_IMPL(OP_SQAURE),       \
        &&TARGET_IMPL(OP_PRINT_TOP),    \
        &&TARGET_IMPL(OP_HALT),         \
    }

#endif


#endif //BAZEL_PROJECT2_EVAL_H