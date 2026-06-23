#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, D;
    cin >> N >> D;

    vector<int> t(N);
    for (int i = 0; i < N; ++i) {
        cin >> t[i];
    }

    for (int d = 0; d < D; ++d) {
        char c;
        cin >> c;
        if (c == '!') {
            int r;
            int x;
            cin >> r >> x;
        } else {
            int r;
            cin >> r;
            cout << 0 << endl;
        }
    }

    return 0;
}
