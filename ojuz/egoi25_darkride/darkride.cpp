#include <bits/stdc++.h>

using namespace std;

int query(const string& switches) {
    cout << "? " << switches << endl;
    int num_screams;
    cin >> num_screams;
    return num_screams;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < 30; ++i) {
        int num_screams = query(string(N, '0'));
    }

    int A = 0;
    int B = 0;

    cout << "! " << A << ' ' << B << endl;

    return 0;
}
