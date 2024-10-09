#define _CRT_SECURE_NO_DEPRECATE
// #define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

#define X first
#define Y second

int R, C, K;
// 0: 북, 1: 동, 2: 남, 3: 서
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int vis[74][72];
int esc[74][72]; // 탈출구 따로 체크
int bvis[74][72];
pair<int, int> robot;

// R(x): 1 -> 3 (+2) (3 <= x <= R + 2)
// C(y): 1 -> 1 (+0)(1 <= y <= C)
int isRest(int x, int y) { // 1 <= x, y <= R, C
	// 주차 실패: return 0;
	// 주차 성공: return 1;
	return x > 3 && x < R + 2 && y > 1 && y < C;
}

void reset() {
	memset(vis, 0, sizeof(vis));
	memset(esc, 0, sizeof(esc));
}

void printVis() {
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= C; j++) {
			cout << vis[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 3; i <= R + 2; i++) {
		for (int j = 1; j <= C; j++) {
			cout << vis[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool isDown(int x, int y) {
	int nx = x, ny = y;
	if (!(nx < R + 2 && ny > 1 && ny < C)) return false;

	for (int i = 0; i < 4; i++) {
		nx = x + dx[i], ny = y + dy[i];
		if (vis[nx][ny]) return false;
	}
	return true;
}

bool down(int id, int r, int c, int dir) { // 다 내려가면 vis, esc 표시 // esc = { dx[dir], dy[dir] }
	// 쭈욱 내려간다
	if (isDown(r + 1, c)) down(id, r + 1, c, dir);
	// 내려가다 안되면 반시계(왼)
	else if (isDown(r, c - 1) && isDown(r + 1, c - 1)) {
		down(id, r + 1, c - 1, (dir + 3) % 4);
	}
	// 내려가다 안되면 반시계(오)
	else if (isDown(r, c + 1) && isDown(r + 1, c + 1)) {
		down(id, r + 1, c + 1, (dir + 1) % 4);
	}
	else {
		// 초기화 조건이라면?
		if (!isRest(r, c)) {
			reset();
			return 0;
		}
		// 방문 표시
		vis[r][c] = id;
		robot.X = r, robot.Y = c;
		for (int i = 0; i < 4; i++) {
			vis[r + dx[i]][c + dy[i]] = id;
		}
		esc[r + dx[dir]][c + dy[dir]] = id;
		return 1;
	}
}

int bfs() {
	// 골룸 이동 // return max 열 // 골룸의 위치: 실제 위치 - 2;
	//if (cur.X< 3 || cur.X > R + 2 || cur.Y < 1 || cur.Y > C) return 0;
	int x, y, id;
	memset(bvis, 0, sizeof(bvis));
	queue<pair<int, int>> Q; // 로봇 bfs 확인, 초기화
	Q.push(robot);
	int maxr = robot.X;
	bvis[robot.X][robot.Y] = 1;

	while (!Q.empty()) {
		pair<int, int> cur = Q.front(); Q.pop();
		x = cur.X, y = cur.Y;
		id = vis[x][y];
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 3 || nx > R + 2 || ny < 1 || ny > C) continue;
			if (bvis[nx][ny]) continue;
			if (vis[nx][ny] == id || (vis[nx][ny] > 0 && esc[x][y] != 0)) {
				Q.push({ nx, ny });
				bvis[nx][ny] = 1;
				maxr = max(nx, maxr);
			}
		}
	}
	return maxr - 2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("input.txt", "r", stdin);
	// 초기화
	reset();

	cin >> R >> C >> K;
	int sum = 0;
	for (int i = 0; i < K; i++) {
		int ci, di;
		cin >> ci >> di;
		robot = { 0, 0 };
		//robot.X = 0, robot.Y = 0;
		if (down(i + 1, 1, ci, di)) {
			sum += bfs();
		}
		//printVis();
	}
	cout << sum;
	return 0;
}