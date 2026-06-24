#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> W(N);
    for (int i = 0; i < N; ++i) {
        cin >> W[i];
    }

    vector<int> P(Q);
    vector<int> Z(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> P[i] >> Z[i];
    }

    vector<long long> ans(Q+1, 0);

    for (int i = 0; i <= Q; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
