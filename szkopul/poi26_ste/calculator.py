import math

def efficiency(n, base, bit_count):
    block_sz = math.floor(math.log(2 ** bit_count, base))
    blocks = math.ceil(n / block_sz)
    bits = blocks * bit_count
    return bits

N = 2 * 10 ** 5

min = 1 * 10 ** 6
min_base = -1
min_count = -1
for bit_count in range(5, 128):
    e = efficiency(N + 1, 26, bit_count)
    if e < min:
        min = e
        min_base = 26
        min_count = bit_count

    e = efficiency(N, 27, bit_count)
    if e < min:
        min = e
        min_base = 27
        min_count = bit_count

block_sz = math.floor(math.log(2 ** min_count, min_base))
efficiency = (min_base ** block_sz) / (2 ** min_count)

print(f'min_base = {min_base} | min_count = {min_count}')
print(f'min_bits = {min} | sz = {math.ceil(min ** 0.5)}')
print(f'block_sz = {block_sz} | efficiency = {efficiency:.2}')
