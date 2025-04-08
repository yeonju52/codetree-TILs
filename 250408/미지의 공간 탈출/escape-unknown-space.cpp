#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
//#include<iomanip>
using namespace std;

const int MAX = 20;
const int MAX3 = 10;

struct pos {
	int sx, sy, ex, ey, ed;
};

struct dpos {
	int d, x, y;
};

struct rcdv {
	int r, c, d, v;
};

int N, M, F;
int board[MAX][MAX];
int cube[5][MAX3][MAX3];
int backup[5][MAX3][MAX3];
int wall[MAX][MAX]; // 이상현상 체크
int dist[5][MAX3][MAX3];
int vis[MAX][MAX];

// 동서남북
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int bfs(int sx, int sy, int ex, int ey, int t1);
int bfs_3d(int sx, int sy, int ex, int ey, int ed);
void move(int T, vector<rcdv> &wind); // 레퍼런스로 받기
void display(const int arr[MAX][MAX]);
void display_3d(int k);
void display_3d(const int arr[5][MAX3][MAX3]);

int main(int argc, char** argv)
{
	int test_case;
	int T;

	ios::sync_with_stdio(0);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);
	//cin >> T;
	T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(board, 0, sizeof(board));
		memset(cube, 0, sizeof(cube));
		memset(wall, 0, sizeof(wall));

		// 입구 출구 찾기, 3차원 2차원 각각 sx, sy, ex ,ey
		pos pos3;
		pos pos2;
		pos base = { -1, };

		cin >> N >> M >> F;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				if (board[i][j] == 4) { pos2.ex = i, pos2.ey = j; }
				if (board[i][j] == 3 && base.sx < 0) { base = { i, j, i + M, j + M }; }
			}
		}

		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < M; j++) {
					cin >> cube[k][i][j];
				}
			}
		}

		// 단면도 이므로, 윗면을 기준으로 실제 공간에서 위쪽이 (0, 0)이므로 좌표 변화 필요
		// k = 01234 -> 위동서남북
		memcpy(backup, cube, sizeof(backup));
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				cube[0][i][j] = backup[0][j][M - 1 - i];
				cube[1][i][j] = backup[1][M - 1 - j][i];
				cube[3][i][j] = backup[3][M - 1 - i][M - 1 - j];
			}
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (cube[4][i][j] == 2) { pos3.sx = i, pos3.sy = j; }
			}
		}

		// 2차원 입구 찾기 pos2.sx sy
		bool found = false;
		int base_sx = base.sx, base_sy = base.sy, base_ex = base.ex, base_ey = base.ey;
		for (int x = base_sx; x < base_ex && !found; x++) {
			for (int y = base_sy; y < base_ey && !found; y++) {
				for (int i = 0; i < 4; i++) {
					int nx = x + dx[i], ny = y + dy[i];
					if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
					if (board[nx][ny] == 0) {
						pos2.sx = nx, pos2.sy = ny;
						// pos3 끝좌표
						pos3.ed = i;
						if (i == 0) pos3.ex = x - base.sx, pos3.ey = M - 1;
						else if (i == 1) pos3.ex = x - base.sx, pos3.ey = 0;
						else if (i == 2) pos3.ex = M - 1, pos3.ey = y - base.sy;
						else if (i == 3) pos3.ex = 0, pos3.ey = y - base.sy;
						found = true;
						break;
					}
				}
			}
		}

		vector<rcdv> wind; // 각 시간 이산현상의 마지막 위치 저장
		for (int i = 0; i < F; i++) {
			int r, c, d, v;
			cin >> r >> c >> d >> v;
			wind.push_back({ r, c, d, v });
			wall[r][c] = 1; // 0 이상으로 체크
		}

		// 3차원 탐색
		int t1, t2;
		t1 = bfs_3d(pos3.sx, pos3.sy, pos3.ex, pos3.ey, pos3.ed);
		if (t1 == -1) {
			cout << -1 << "\n";
			return 0;
		}
		// 시간이상현상
		move(400 * 6, wind); // 레퍼런스로 받기
		// 2차원 탐색
		t2 = bfs(pos2.sx, pos2.sy, pos2.ex, pos2.ey, t1);
		if (t2 == -1) {
			cout << -1 << "\n";
			return 0;
		}
		cout << t2 << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}


int bfs(int sx, int sy, int ex, int ey, int t1) {
	memset(vis, 0, sizeof(vis));
	queue<pair<int, int>> q;

	q.push({ sx, sy });
	vis[sx][sy] = t1;

	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int x = cur.first, y = cur.second;
		if (x == ex && y == ey) return vis[x][y];
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (board[nx][ny] != 0 && board[nx][ny] != 4) continue;
			if (vis[nx][ny] > 0) continue;
			if (wall[nx][ny] > 0 && wall[nx][ny] <= vis[x][y] + 1) continue;
			q.push({ nx, ny });
			vis[nx][ny] = vis[x][y] + 1;
		}
	}
	return -1;
}

void move(int T, vector<rcdv> &wind) {
	// r, c 위치에, d방향의 v 배수일 때
	for (int t = 1; t <= T; t++) {
		for (auto& w : wind) {
			if (t % w.v == 0) {
				int nr = w.r + dx[w.d], nc = w.c + dy[w.d];
				if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
				if (board[nr][nc] != 0) continue;
				wall[nr][nc] = t;
				w.r = nr, w.c = nc; // 참조로 실제 값도 수정
			}
		}
	}
}


int bfs_3d(int sx, int sy, int ex, int ey, int ed) {
	memset(dist, 0, sizeof(dist));
	queue<dpos> q;

	q.push({ 4, sx, sy });
	dist[4][sx][sy] = 1;

	while (!q.empty()) {
		dpos cur = q.front(); q.pop();
		int d = cur.d, x = cur.x, y = cur.y;
		if (d == ed && x == ex && y == ey) return dist[d][x][y];
		for (int i = 0; i < 4; i++) {
			int nd = d, nx = x + dx[i], ny = y + dy[i];
			if (nx < 0) { // 위로 나갈 때
				if (d == 2) nd = 4, nx = M - 1, ny = y;
				else if (d == 4) nd = 3, nx = M - 1, ny = y;
				else if (d == 1) nd = 3, nx = y, ny = 0;
				else if (d == 0) nd = 3, nx = M - 1 - y, ny = M - 1;
				else continue;
			}
			else if (nx >= M) { // 아래
				if (d == 3) nd = 4, nx = 0, ny = y;
				else if (d == 4) nd = 2, nx = 0, ny = y;
				else if (d == 1) nd = 2, nx = M - 1 - y, ny = 0;
				else if (d == 0) nd = 2, nx = y, ny = M - 1;
				else continue;
			}
			else if (ny < 0) { // 왼
				if (d == 4) nd = 1, nx = x, ny = M - 1;
				else if (d == 0) nd = 4, nx = x, ny = M - 1;
				else if (d == 2) nd = 1, nx = M - 1, ny = M - 1 - x;
				else if (d == 3) nd = 1, nx = 0, ny = x;
				else continue;
			}
			else if (ny >= M) { // 오
				if (d == 1) nd = 4, nx = x, ny = 0;
				else if (d == 2) nd = 0, nx = M - 1, ny = x;
				else if (d == 3) nd = 0, nx = 0, ny = M - 1 - x;
				else if (d == 4) nd = 0, nx = x, ny = 0;
				else continue;
			}
			if (cube[nd][nx][ny] == 1 || dist[nd][nx][ny] > 0) continue;
			q.push({ nd, nx, ny });
			dist[nd][nx][ny] = dist[d][x][y] + 1;
		}
	}
	return -1;
}

void display(const int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}

void display_3d(int k) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			cout << cube[k][i][j];
		}
		cout << "\n";
	}
}

void display_3d(const int arr[5][MAX3][MAX3]) {
	for (int k = 0; k < 5; k++) {
		cout << k << "\n";
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				cout << arr[k][i][j] << " "; //  << setw(3)
			}
			cout << "\n";
		}
	}
}
