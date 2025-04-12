#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

const int MAX = 30;

struct group {
	int num, cnt;
};

int N;
int board[MAX][MAX];
int vis[MAX][MAX];
int backup[MAX][MAX];
group conc[MAX * MAX]; // i 번째 라벨의 값 (1번부터)

int dfs(int x, int y, int label);
void display(const int arr[MAX][MAX]);
int get_score(int g1, int g2);
void ccwrotate();
void rotate(int sx, int sy);

int main(int argc, char** argv)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int test_case;
	int T;
	//cin >> T;
	T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(board, 0, sizeof(board));

		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
			}
		}

		int step = 4;
		int ans = 0;
		while (step--) {
			// 1단계: cc 찾기
			memset(vis, 0, sizeof(vis));
			memset(conc, 0, sizeof(conc));
			int label = 1;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (vis[i][j]) continue;
					conc[label].num = board[i][j];
					conc[label].cnt = dfs(i, j, label);
					label++;
				}
			}
			int gcnt = label - 1;
			if (gcnt < 2) {
				break; // ans == 0;
			}
			//display(vis);

			// 2단계: 모든 조합찾기 gcnt C 2
			vector<int> brute(gcnt, 0);
			if (gcnt < 2) continue;
			fill(brute.end() - 2, brute.end(), 1);
			do {
				int gidx[2]; int idx = 0;
				for (int i = 0; i < gcnt; i++) {
					if (brute[i] == 1) {
						gidx[idx++] = i + 1;
					}
				}
				// 두 개의 조합을 가지고, get_score
				ans += get_score(gidx[0], gidx[1]);
			} while (next_permutation(brute.begin(), brute.end()));

			if (step == 0) break;
			// 3: 회전
			int halfNplus = N / 2 + 1;
			memcpy(backup, board, sizeof(backup));
			ccwrotate(); // 반시계 회전
			rotate(0, 0); // 좌상
			rotate(halfNplus, 0); // 좌하
			rotate(0, halfNplus); // 우상
			rotate(halfNplus, halfNplus); // 우하
			//display(board);
		}
		cout << ans << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

void rotate(int sx, int sy) {
	int halfN = N / 2;
	for (int x = 0; x < halfN; x++) {
		for (int y = 0; y < halfN; y++) {
			board[sx + x][sy + y] = backup[sx + halfN - 1 - y][sy + x];
		}
	}
	return;
}

void ccwrotate() {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (x != N / 2 && y != N / 2) continue;
			board[x][y] = backup[y][N - 1 - x];
		}
	}
	return;
}

int get_score(int g1, int g2) {
	//cout << (conc[g1].cnt) << "," << conc[g2].cnt << "," << conc[g1].num << "," << conc[g2].num << "\n";
	int side = 0;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (vis[x][y] != g1) continue;
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (vis[nx][ny] == g2) side++;
			}
		}
	}
	return (conc[g1].cnt + conc[g2].cnt) * conc[g1].num * conc[g2].num * side;
}

int dfs(int x, int y, int label) {
	vis[x][y] = label;
	int cnt = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		if (vis[nx][ny] || board[nx][ny] != conc[label].num) continue;
		cnt += dfs(nx, ny, label);
	}
	return cnt;
}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}