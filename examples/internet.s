// mmio map
// ffff - our client's local ip
// fffe - our client's destination ip (who he wants to send data to)
// fffd - the byte he wants to send
// fffc - send pin read (if the send pin is high, he wants to send this packet.)
// fffb - send pin write (once we are done sending the packet, turn the pin to low)
// fff9 - receiving ip , if we receive a packet, we want to tell our client who sent it.
// fff8 - receive read, once we received, we turned receive to high. now if receive pin is low, our client received the packet.
// fff7 - receive write, turn pin to high if we received a packet.
// fff6 - receive ibus, this is the bus containing the internet traffic.
// fff5 - write ibus, set a value on the ibus. note if other devices are writing there will be a conflict. make sure the ibus is not used first.
// ibus format
// bit 15 is bus in use
// bit 14 is packet received (if we sent a packet and the receipent received it, this is high.) we will also set it to high if needed
// bit 11-13 source ip, who is sending the packet.
// bit 8-10  dest ip, who is it being sent to.
// bit 0-7 data (a byte)

// MMIO map
#define LIP             0xffff  // local IP of our client
#define DIP             0xfffe  // destination IP (who client wants to send data to)
#define SEND_BYTE       0xfffd  // the byte the client wants to send
#define SEND_READ       0xfffc  // send pin read (high = wants to send)
#define SEND_WRITE      0xfffb  // send pin write (set low once done sending)

#define RECV_RIP        0xfffa
#define RECV_BYTE       0xfff9
#define RECV_READ       0xfff8
#define RECV_WRITE      0xfff7

#define RECV_IBUS       0xfff6  // bus containing incoming internet traffic
#define WRITE_IBUS      0xfff5  // write a value on the ibus

#expansion allowed

start:
    li x1, 0
    li x2, 0
    li x3, 0
    li x4, 0
    li x5, 0
    li x6, 0
    li x7, 0
check_ibus_busy:
    lihs x2, RECV_IBUS
    lw x3, x2
    lihs x2, 0x8000
    and x3, x3, x2
    beq x3, x0, ibus_not_busy
ibus_busy:
    // If the ibus is busy, check if there is a packet for us.
    lihs x2, RECV_IBUS
    lw x3, x2
    li x2, 256
    div x3, x3, x2
    li x2, 0x7
    and x3, x3, x2
    lihs x2, LIP
    lw x4, x2
    xor x3, x3, x4
    beq x3, x0, lip_equals_dip
    j check_ibus_busy
lip_equals_dip:
    lihs x2, RECV_IBUS
    lw x3, x2
    lw x6, x2
    lw x7, x2
    li x2, 0xff
    and x3, x3, x2
    lihs x2, RECV_BYTE
    sw x3, x2
    li x2, 2048
    div x6, x6, x2
    lihs x2, RECV_RIP
    sw x6, x2
    lihs x2, RECV_WRITE
    li x3, 1
    sw x3, x2
    lihs x2, RECV_READ
wait_client_ack:
    lw x3, x2
    beq x3, x0, ack
    j wait_client_ack
ack:
    lihs x2, WRITE_IBUS
    li x3, 16384
    sw x3, x2

    lihs x2, RECV_IBUS
    lihs x3, 32768
check_sender_ack:
    // our received signal is on the ibus, if the ibus use goes off, we can continue.
    lw x4, x2
    and x5, x4, x3
    beq x5, x0, done_receiving
    j check_sender_ack
done_receiving:
    lihs x2, WRITE_IBUS
    sw x0, x2
    nop
    j check_ibus_busy
ibus_not_busy:
    lihs x2, SEND_READ
    lw x3, x2
    beq x3, x0, check_ibus_busy
client_send_packet:
    // x7 is the packet
    lihs x2, SEND_BYTE
    lw x7, x2
    lihs x2, DIP
    lw x6, x2
    li x3, 256
    mul x6, x6, x3
    or x7, x7, x6
    lihs x2, LIP
    lw x6, x2
    li x3, 2048
    mul x6, x6, x3
    or x7, x7, x6
    lihs x3, 32768
    or x7, x7, x3
    lihs x2, WRITE_IBUS
    sw x7, x2
    lihs x2, RECV_IBUS
    li x3, 16384
check_received:
    lw x7, x2
    and x7, x7, x3
    beq x7, x0, check_received
received:
    lihs x2, WRITE_IBUS
    sw x0, x2
    lihs x2, SEND_WRITE
    sw x0, x2
    nop
    j check_ibus_busy

