#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    vector<long long> K(Q);
    
    for (int i = 0; i < Q; ++i) {
        cin >> K[i];
    }

    vector<bool> sol(Q, false);

    for (int i = 0; i < Q; ++i) {
        cout << (sol[i] ? "YES" : "NO") << endl;
    }

    return 0;
}
