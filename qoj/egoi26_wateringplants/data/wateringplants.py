N, D = map(int, input().split())

t = list(map(int, input().split()))

for d in range(D):
    parts = input().split()
    if parts[0] == '!':
        r = int(parts[1])
        x = int(parts[2])
    else:
        r = int(parts[1])
        print(0)
