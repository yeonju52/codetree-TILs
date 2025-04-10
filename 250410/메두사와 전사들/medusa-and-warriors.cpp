#define _CRT_SECURE_NO_WARNINGS
#define first X
#define second Y

#include<iostream>
#include <cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int MAX = 50;
int N, M;

struct pos {
	int x, y, status;
};

pair<int, int> st, ed;

int board[MAX][MAX];
int area[MAX][MAX];
int rlen;
pair<int, int> route[MAX * MAX];

// 상하좌우
int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dy[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };

bool bfs();
int get_dir(int x, int y, int ex, int ey, int mode);
void view(int x, int y, int val, const vector<int> &dir);
void display(int arr[MAX][MAX]);

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
		vector<pos> warrior;

		cin >> N >> M;
		cin >> st.X >> st.Y >> ed.X >> ed.Y;

		for (int w = 0; w < M; w++) {
			int x, y;
			cin >> x >> y;
			warrior.push_back({ x, y, 0 });
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
			}
		}

		// 만약 메두사가 도착 못하는 경우, -1
		if (!bfs()) {
			cout << -1 << "\n";
			break;
		}

		int t = 0, moveCnt = 0, rockCnt = 0, attackCnt = 0;
		int x, y;
		while (true) {
			// 1. 메두사 이동
			rlen--;
			x = route[rlen].X, y = route[rlen].Y;

			if (x == ed.X && y == ed.Y) {
				cout << "0" << "\n";
				break;
			}

			// 전사가 있으면 공격
			vector<pos>::iterator war = warrior.begin();
			while(war != warrior.end()) {
				if (war->x == x && war->y == y) warrior.erase(war);
				else { ++war; }
			}

			// 2. 메두사의 시선
			// 상: {0, 5, 4}, 하: {1, 6, 7}, 좌: {2, 6, 4}, 우: {3, 5, 7 }
			// | \(기울기 음수) /(기울기 양수)
			vector<vector<int>> dir = { {0, 5, 4}, {1, 6, 7}, {2, 6, 4}, {3, 5, 7} };

			int cnt = 0, find_d = 0;
			rockCnt = 0;
			bool real = false;
			for (int i = 0; i < 5; i++) { // 4 + 1(정한 find_d로)
				memset(area, 0, sizeof(area)); // 메두사 영역 초기화

				if (i == 4) {
					i = find_d; real = true;
				}
				// 1) area: 메두사 그림자 영역 1 체크
				view(x, y, 1, dir[i]);
				// 2) area: 전사 그림자 영역 3 체크
				for (pos &war : warrior) {
					if (area[war.x][war.y] != 1) continue; // 1일 때만 신경 써야
					if (war.status) continue;
					double diffx = x - war.x, diffy = y - war.y;
					if (diffx == 0 || diffy == 0) view(war.x, war.y, 3, { dir[i][0] });
					else if (diffx / diffy < 0) view(war.x, war.y, 3, { dir[i][0], dir[i][1] });
					else view(war.x, war.y, 3, { dir[i][0], dir[i][2] });
				}
				if (!real) {
					cnt = 0;
					for (pos &war : warrior) {
						if (!war.status && area[war.x][war.y] == 1) cnt++;
					}
					if (rockCnt < cnt) {
						rockCnt = cnt;
						find_d = i;
					}
				}
				else { // 실제 find_d로 전사 돌 만들기
					for (pos &war : warrior) {
						if (!war.status && area[war.x][war.y] == 1) war.status = 1;
					}
					break;
				}
			}

			// 3. 전사들의 이동
			moveCnt = 0; // 이동횟수
			attackCnt = 0;
			for (pos &war : warrior) {
				for (int k = 0; k < 2; k++) {
					if (war.status || area[war.x][war.y] == 1) break; // war.status (1:돌, -1:죽음) 일 때
					int i = get_dir(war.x, war.y, x, y, k * 2); // 전사들 모드 (0, 1 상관없이 모두 지나감)
					if (i == -1) break;
					war.x += dx[i], war.y += dy[i];
					moveCnt++;
					if (war.x == x && war.y == y) {
						attackCnt++;
						war.status = -1;
						break;
					}
				}
			}

			cout << moveCnt << " " << rockCnt << " " << attackCnt << "\n";
			for (pos &war : warrior) {
				if (war.status == 1) war.status = 0;
			}
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int get_dir(int x, int y, int ex, int ey, int base) {
	int dir = -1;
	int minval = N * N;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[(base + i) % 4], ny = y + dy[(base + i) % 4];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		if (area[nx][ny] == 1) continue;
		int val = abs(nx - ex) + abs(ny - ey);
		if (val >= abs(x - ex) + abs(y - ey)) continue;
		if (minval > val) {
			minval = val;
			dir = (base + i) % 4;
		}
	}
	return dir;
}

void view(int x, int y, int val, const vector<int> &dir) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	//area[x][y] = val; // 체킹하면 안됨

	int len = dir.size();
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		x = cur.X, y = cur.Y;
		for (int i = 0; i < len; i++) {
			int nx = x + dx[dir[i]], ny = y + dy[dir[i]];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (area[nx][ny] != val) {
				q.push({ nx, ny });
				area[nx][ny] = val;
			}
		}
	}
}

pair<int, int> before[MAX][MAX];
bool bfs() {
	queue<pair<int, int>> q;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			before[i][j] = { -1, -1 };
		}
	}

	//fill(before[0], before[MAX], -1);

	int x = st.X, y = st.Y;
	before[x][y] = { x, y };
	q.push({ x, y });

	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		x = cur.X, y = cur.Y;
		if (x == ed.X && y == ed.Y) {
			pair<int, int> prev = cur;
			while (!(prev.X == st.X && prev.Y == st.Y)) {
				route[rlen++] = prev;
				prev = before[prev.X][prev.Y];
			}
			return true;
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (board[nx][ny] == 1) continue;
			if (before[nx][ny].X > -1) continue;
			before[nx][ny] = { x, y };
			q.push({ nx, ny });
		}
	}
	return false;
}

void display(int arr[MAX][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}
