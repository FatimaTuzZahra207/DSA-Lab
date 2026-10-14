#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Eight possible knight moves offsets
int cx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int cy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool solveKTUtil(int x, int y, int movei, vector<vector<int>>& board, int N) {
	if (movei == N * N)
		return true;

	for (int k = 0; k < 8; k++) {
		int next_x = x + cx[k];
		int next_y = y + cy[k];

		if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N && board[next_x][next_y] == -1) {
			board[next_x][next_y] = movei;
			if (solveKTUtil(next_x, next_y, movei + 1, board, N))
				return true;
			else
				board[next_x][next_y] = -1; // Backtrack
		}
	}
	return false;
}

int main() {
	cout << "--- Task 4: Knight's Tour ---" << endl;
	int N;
	cout << "Enter board size N (e.g., 5): ";
	cin >> N;

	vector<vector<int>> board(N, vector<int>(N, -1));

	int start_x, start_y;
	cout << "Enter starting row and col (0 to " << N - 1 << "): ";
	cin >> start_x >> start_y;

	board[start_x][start_y] = 0;

	if (solveKTUtil(start_x, start_y, 1, board, N)) {
		cout << "Knight's Tour Successful!\nGrid representation:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << setw(4) << board[i][j];
			}
			cout << endl;
		}
	}
	else {
		cout << "No valid tour found for the specified starting position.\n";
	}

	return 0;
}