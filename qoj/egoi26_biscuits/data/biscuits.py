N, Q = map(int, input().split())

W = list(map(int, input().split()))

P = [0] * Q
Z = [0] * Q
for i in range(Q):
    P[i], Z[i] = map(int, input().split())

ans = [0] * (Q + 1)

for i in range(Q+1):
    print(ans[i])
