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

#define MAKE_TARGET(n) &&OP_##n

#define OP_IMPL_ALL(_)      \
    _(PUSH_CONST),          \
    _(ADD),                 \
    _(SUB),                 \
    _(SQAURE),              \
    _(PRINT_TOP),           \
    _(HALT)


#define MAKE_N(n) OP_##n
enum {
     OP_IMPL_ALL(MAKE_N)
};

#undef MAKE_N

#define PUSH_STACK()  stack[sp++] = (arg)
#define STACK_SET_TOP(x) stack[sp - 1] = (x)
#define STACK_TOP() stack[sp - 1]
#define STACK_VALUE(offset) stack[sp + (offset)]
#define STACK_SP_ADD() sp += 1
#define STACK_SP_SUB() sp -= 1
#define NEXT_OP_CODE()  opcode = bytecode[pc++]
#define NEXT_ARG() (arg = bytecode[pc++])
#define DISPATCH_EXIT() goto end  /* switch-case 内用 break 跳到下次循环 */
#define DISPATCH_ERROR() goto error  /* switch-case 内用 break 跳到下次循环 */



#if defined(_WIN32)

    #define TARGET(op) case op :

    #define DISPATCH() \
        NEXT_OP_CODE(); \
        break;  /* switch-case 内用 break 跳到下次循环 */

    #define DEFATULT default :

#else

    #define TARGET(op)  op :

    #define DISPATCH() \
        NEXT_OP_CODE(); \
        goto *opcode_targets[opcode];  /* switch-case 内用 compute_gotos 跳到下次地址 */

    #define DEFATULT default_end :
    #define OPERATOR_TARGETS   { OP_IMPL_ALL(MAKE_TARGET) }



#endif

int EVAL_Value(int bytecode[]);
#endif //BAZEL_PROJECT2_EVAL_H

