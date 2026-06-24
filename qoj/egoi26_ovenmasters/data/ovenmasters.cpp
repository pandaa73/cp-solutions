#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> b(M);
    for (int i = 0; i < M; ++i) {
        int T;
        cin >> T;
        b[i].resize(T);
        for (int j = 0; j < T; ++j) {
            cin >> b[i][j];
        }
    }

    vector<int> a(N);

    bool possible = false;

    if (!possible) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < N; ++i) {
            cout << a[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}
