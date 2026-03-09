#include "examples/io.s"

kbrdy:
    li.hs x2, KB_ASCII
    lw x3, x2
    beq x3, x0, kbrdy

    li x4, 97

check:
    beq x3, x4, upper
    li x5, 122
    beq x4, x5, output
    addi x4, x4, 1
    j check

upper:
    li x5, 223
    and x3, x3, x5

output:
    li.hs x2, TTY_CHAR
    sw x3, x2
    j kbrdy