#define hexvalone 0xfe
#define hexvaltwo 0xef

#macro inc reg
    addi reg, reg, 1
#endmacro

#macro nop2
    nop
    nop
#endmacro

#expansion allowed

.ramorg 0xa
data::
.word hexvalone hexvaltwo

start:
    inc x1 
    nop2
    j start