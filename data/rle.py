#==================================================================================================
# RLE encoder
# Takes any binary file and converts to RLE sequenced (ended with length 0)
#--------------------------------------------------------------------------------------------------
# Usage: python rle.py <BIN_FILENAME>
#--------------------------------------------------------------------------------------------------
# Input  :  FF FF FF FF FF FF FF FF FF 0A FF FF FF
# Output : 09 FF 01 0A 03 FF 00
#==================================================================================================
import os
import sys
import math

input = sys.argv[1]

if len(sys.argv) == 1:
    print("Usage:\n $ python3 ./rle.py <BIN_FILENAME>\n\nOutput .rle format.")
    sys.exit()


def compress(data):
    output = []
    i = 1
    total = 0
    char = data[0]
    count = 1

    while i <= len(data):
        if i == len(data):
            output.append(bytes([count]))
            output.append(bytes([char]))
            total += count
            break
        if char == data[i]:
            count += 1
            if count == 255:
                total += count
                output.append(bytes([count]))
                output.append(bytes([char]))
                count = 0
            i += 1
            continue
        else:
            total += count
            output.append(bytes([count]))
            output.append(bytes([char]))
            count = 1
            char = data[i]
            i += 1
            continue

    print(total, "bytes compresed to", len(output))
    return output


def read_file_bytes(file):
    with open(file, 'rb') as f:
        return f.read()


def read_file(input):
    inbytes = read_file_bytes(input)
    output = compress(inbytes)
    f = None
    try:
        f = open(input.split('.')[0] + ".rle", "wb")
        for b in output:
            f.write(b)
        f.write(b'\x00')
    finally:
        f.close()


read_file(input)

print("File written successfully.")
