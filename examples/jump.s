#define hexvalone 0xfe
#define hexvaltwo 0xef

.ramorg 0xa
data::
.word hexvalone hexvaltwo

start: 
    lihs x1, 0xFFFF
jump:
    lil x1, data
    j start