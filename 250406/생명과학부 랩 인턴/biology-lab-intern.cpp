#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
#include <cstdio>

using namespace std;

const int MAX = 100;

struct virus {
	int s;
	int d;
	int b;
};

int N, M, K;
virus board[MAX][MAX];

void solve();
void move(int x, int y, virus cur);
void display(const virus arr[MAX][MAX]);

int main(int argc, char** argv)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	//cin >> T;
	T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(board, 0, sizeof(board));
		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			int x, y, s, d, b;
			cin >> x >> y >> s >> d >> b;
			board[x - 1][y - 1] = { s, d - 1, b };
		}

		int ans = 0;
		for (int j = 0; j < M; j++) {
			// 1. 탐색
			for (int i = 0; i < N; i++) {
				if (board[i][j].b > 0) {
					ans += (board[i][j].b);
					board[i][j] = { 0, 0, 0 };
					break;
				}
			}
			
			// 2. 바이러스 움직이기
			solve();
		}

		cout << ans;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

// 위, 아래, 오, 왼
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
virus nxt[MAX][MAX];

void move(int x, int y, virus cur) {
	int d = cur.d, s = cur.s, b = cur.b;
	int nx = x + (dx[d] * s), ny = y + (dy[d] * s);
	
	if (nx < 0) {
		d ^= 1;
		nx = abs(nx);
	}
	if (ny < 0) {
		d ^= 1;
		ny = abs(ny);
	}
	if (nx > N - 1) {
		if ((nx / (N - 1)) % 2 == 1) {
			d ^= 1;
			nx = N - 1 - (nx % (N - 1));
		}
		else {
			nx = nx % (N - 1);
		}
	}
	if (ny > M - 1) {
		if ((ny / (M - 1)) % 2 == 1) {
			d ^= 1;
			ny = M - 1 - (ny % (M - 1));
		}
		else {
			ny = ny % (M - 1);
		}
	}


	if (nxt[nx][ny].b < b) {	
		nxt[nx][ny] = { s, d, b };
	}
}

void solve() {
	memset(nxt, 0, sizeof(nxt));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j].b > 0) {
				move(i, j, board[i][j]);
			}
		}
	}

	memcpy(board, nxt, sizeof(board));
}

void display(const virus arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[i][j].b << " ";
		}
		cout << "\n";
	}
}