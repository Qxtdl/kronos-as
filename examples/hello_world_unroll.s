start:
    li.hs x2, 0xFFFF
    li.hs x3, 0xFFFE
    li.hs x4, 0xFFFD
    li.hs x5, 0
    li.hs x6, 0
print:
    li x5, 72
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 101
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 108
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 108
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 111
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 44
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 32
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 87
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 111
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 114
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 108
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 100
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    li x5, 33
    addi x6, x6, 1
    sw x6, x3
    sw x5, x2
    sw x0, x4
    j print
