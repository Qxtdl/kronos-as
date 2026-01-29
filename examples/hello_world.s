start:
    li.hs x2, 0xFFFF
    li.hs x3, 0xFFFE
    li.hs x4, 0xFFFD
    li.hs x5, 0
    li.hs x6, 0
print:
    li x5, 72
    jal x1, putc
    li x5, 101
    jal x1, putc
    li x5, 108
    jal x1, putc
    li x5, 108
    jal x1, putc
    li x5, 111
    jal x1, putc
    li x5, 44
    jal x1, putc
    li x5, 32
    jal x1, putc
    li x5, 87
    jal x1, putc
    li x5, 111
    jal x1, putc
    li x5, 114
    jal x1, putc
    li x5, 108
    jal x1, putc
    li x5, 100
    jal x1, putc
    li x5, 33
    jal x1, putc
    j print
putc:
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    jalr x0, x1