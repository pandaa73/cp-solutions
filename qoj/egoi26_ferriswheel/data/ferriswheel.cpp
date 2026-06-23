#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    string S;
    cin >> S;

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
