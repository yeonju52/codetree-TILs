#include<iostream>
#include<queue>
#include<cstring>
#include<unordered_set>
using namespace std;

const int MAXL = 40;
const int MAXN = 31;

struct info {
	int x, y, h, w, k;
};

int L, N, Q;
int ans;

int board[MAXL][MAXL];
int area[MAXL][MAXL];
info knight[MAXN];
int origin[MAXN];

bool solve(int idx, int d);

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	//cin >> T;
	T = 1;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		ios::sync_with_stdio(0);
		cin.tie(0);
		
		memset(board, 0, sizeof(board));
		memset(knight, 0, sizeof(knight));
		memset(origin, 0, sizeof(origin));
		ans = 0;

		cin >> L >> N >> Q;
		for (int i = 0; i < L; i++)
			for (int j = 0; j < L; j++)
				cin >> board[i][j];

		for (int i = 1; i <= N; i++) {
			int r, c, h, w, k;
			cin >> r >> c >> h >> w >> k;
			knight[i] = { r - 1, c - 1, h, w, k };
			origin[i] = k;
		}
		
		while (Q--) {
			int idx, d;
			cin >> idx >> d;
			solve(idx, d);
		}

		for (int i = 1; i <= N; i++) {
			if (knight[i].k <= 0) continue;
			ans += (origin[i] - knight[i].k);
		}
		cout << ans << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

// 위 오 아 왼
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool solve(int idx, int d) {
	if (knight[idx].k <= 0) return false; // 없어진 기사

	// 1. 기사의 이동
	memset(area, 0, sizeof(area));
	for (int m = 1; m <= N; m++) {
		int sx = knight[m].x, sy = knight[m].y, ex = sx + knight[m].h, ey = sy + knight[m].w;
		for (int i = sx; i < ex; i++) {
			for (int j = sy; j < ey; j++) {
				area[i][j] = m;
			}
		}
	}
	queue<int> q;
	unordered_set<int> real;
	q.push(idx); // k는 1부터
	real.insert(idx);

	while (!q.empty()) {
		int nidx = q.front(); q.pop();
		info &men = knight[nidx];
		int x = men.x + dx[d], y = men.y + dy[d];
		for (int nx = x; nx < x + men.h; nx++) {
			for (int ny = y; ny < y + men.w; ny++) {
				if (nx < 0 || nx >= L || ny < 0 || ny >= L) return false;
				if (board[nx][ny] == 2) return false;
				int nxt = area[nx][ny];
				if (knight[nxt].k <= 0) continue; // 없어진 기사
				if (nxt) {
					if (real.find(nxt) != real.end()) continue;
					q.push(nxt);
					real.insert(nxt);
				}
			}
		}
	}

	// 실제 이동
	for (auto &nidx : real) knight[nidx].x += dx[d], knight[nidx].y += dy[d];
	
	// 대결 이미지 (자기자신 빼고)
	for (auto &nidx : real) {
		if (nidx == idx) continue; // 자기자신 제외
		info &men = knight[nidx];

		if (men.k <= 0) continue; // 없어진 기사
		int x = men.x, y = men.y;
		for (int nx = x; nx < x + men.h; nx++) {
			for (int ny = y; ny < y + men.w; ny++) {
				if (board[nx][ny] != 1) continue;
				men.k -= 1;
			}
		}
	}
	return true;
}

void display(int arr[MAXL][MAXL]) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
}