def query(switches):
    print("?", switches)
    return int(input())

N = int(input())

for i in range(30):
    num_screams = query("0" * N)

A = 0
B = 0

print("!", A, B)
