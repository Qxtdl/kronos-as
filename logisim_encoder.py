import sys

with open(sys.argv[1], "rb") as binf, open(sys.argv[2], "w") as hexf:
    hexf.write("v2.0 raw\n")

    while True:
        bytes4 = binf.read(4)
        if not bytes4:
            break

        value = int.from_bytes(bytes4, byteorder="little")
        hexf.write(f"{value:08X}\n")