#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 52;

int N, M, t;
int board[MAX][MAX];

vector<pair<int, int>> wind;

void doDirt();
void doWind();
void display(const int arr[MAX][MAX]);

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	//cin >> T;
	T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M >> t;
		
		memset(board, 0, sizeof(board));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> board[i][j];
				if (board[i][j] == -1) {
					wind.push_back({ i, j });
				}
			}
		}

		int sum = 0;

		while (t--) {
			// 먼지 확산
			doDirt();
			//display(board);
			// 시공의 돌풍 청소
			//cout << "\n";
			//display(board);
			//cout << "\n";
			doWind();
			//display(board);

			// 먼지의 총합
			sum = 0;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (board[i][j] == -1) continue;
					sum += board[i][j];
				}
			}
		}
		cout << sum << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int dp[MAX][MAX]; // 더할 양 (+) 뺄 양 (-)
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

void dfs(int x, int y) {
	int cnt = 0;
	int amount = board[x][y] / 5;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
		if (board[nx][ny] == -1) continue;
		dp[nx][ny] += amount;
		cnt++;
	}
	dp[x][y] -= (amount * cnt);
}

void doDirt() {
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == -1) continue;
			dfs(i, j);
		}
	}

	// dp[x][y]
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == -1) continue;
			board[i][j] += dp[i][j];
		}
	}
}

void doWind() {
	// 위쪽 반시계방향
	int x = wind[0].first, y = wind[0].second;
	for (int i = x - 1; i >= 0; i--) {
		board[i + 1][y] = board[i][y];
	}
	for (int j = 1; j < M; j++) {
		board[0][j - 1] = board[0][j];
	}
	for (int i = 1; i <= x; i++) {
		board[i - 1][M - 1] = board[i][M - 1];
	}
	for (int j = M - 2; j > 0; j--) {
		board[x][j + 1] = board[x][j];
	}
	board[x][y + 1] = 0;
	board[x][y] = -1;

	// 아래쪽 시계방향
	x = wind[1].first;
	y = wind[1].second;
	for (int i = x + 1; i < N; i++) { // 3
		board[i - 1][0] = board[i][0];
	}
	for (int j = 1; j < M; j++) { // 2
		board[N - 1][j - 1] = board[N - 1][j];
	}
	for (int i = N - 1; i > x; i--) { // 1
		board[i][M - 1] = board[i - 1][M - 1];
	}
	for (int j = M - 2; j > 0; j--) { // 4
		board[x][j + 1] = board[x][j];
	}
	board[x][y + 1] = 0;
	board[x][y] = -1;

}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}