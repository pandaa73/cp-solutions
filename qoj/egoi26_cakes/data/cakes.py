N, Q = map(int, input().split())

a = list(map(int, input().split()))

K = [0] * Q
for i in range(Q):
    K[i] = int(input())

sol = [False] * Q

for i in range(Q):
    print("YES" if sol[i] else "NO")
