#include <iostream>
#include <vector>

using namespace std;

constexpr int k = 1000;

string abbreviate(string s) {
	if (s.size() <= 20) return s;
	return s.substr(0, 20) + "...";
}

int main(int argc, char **argv) {
    FILE* from_user_a = fdopen(atoi(argv[2]), "r");
    FILE* to_user_a = fdopen(atoi(argv[3]), "w");
    FILE* from_user_b = fdopen(atoi(argv[4]), "r");
    FILE* to_user_b = fdopen(atoi(argv[5]), "w");

    if (from_user_a == NULL || to_user_a == NULL || from_user_b == NULL || to_user_b == NULL) {
        cout << "Error: Cannot open file descriptor!" << endl;
        return 1;
    }

	int k;
	cin >> k;

    int n;
	cin >> n;

	string message;
    cin >> message;

	vector<int> row_permutation(k), column_permutation(k);

	for (int i = 0; i < k; ++i) {
		cin >> row_permutation[i];
		row_permutation[i]--;
	}
	for (int i = 0; i < k; ++i) {
		cin >> column_permutation[i];
		column_permutation[i]--;
	}

	fprintf(to_user_a, "%d\n", k);
	fprintf(to_user_a, "encoder\n");
	fprintf(to_user_a, "%d\n", n);
	fprintf(to_user_a, "%s\n", message.c_str());
	fflush(to_user_a);

    vector<vector<bool>> matrix(k, vector<bool>(k));

	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < k; ++j) {
			char c;
			int v = fscanf(from_user_a, " %c", &c);
			if (v != 1) {
				cout << "Niepoprawny format wyjścia encodera" << endl;
				return 0;
			}
			matrix[i][j] = c - '0';
		}
	}

	vector<vector<bool>> shuffledMatrix(k, vector<bool>(k));

	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < k; ++j) {
			shuffledMatrix[i][j] = matrix[row_permutation[i]][column_permutation[j]];
		}
	}

	fprintf(to_user_b, "%d\n", k);
	fprintf(to_user_b, "decoder\n");
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < k; ++j) {
			if (shuffledMatrix[i][j])
				fprintf(to_user_b, "1");
			else
				fprintf(to_user_b, "0");
		}
		fprintf(to_user_b, "\n");
	}
	fflush(to_user_b);

	char user_answer[200'000];
	int v = fscanf(from_user_b, "%s", user_answer) == 1;
	if (v != 1) {
		cout << "Niepoprawny format wyjścia decodera" << endl;
		return 0;
	}

    string user_answer_str = string(user_answer);

	if (message == user_answer_str)
		cout << "Poprawna odpowiedz" << endl;
	else
		cout << "Zla odpowiedz.\nOczekiwano: " + abbreviate(message) + "\nOtrzymano: " + abbreviate(user_answer) << endl;

    return 0;
}
